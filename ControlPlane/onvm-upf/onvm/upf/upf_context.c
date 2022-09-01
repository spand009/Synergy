#define TRACE_MODULE _upf_context

#include "upf_context.h"

#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netinet/in.h>
#include <net/if.h>

#include <rte_byteorder.h>

#include "utlt_debug.h"
#include "utlt_pool.h"
#include "utlt_index.h"
#include "utlt_hash.h"
#include "utlt_network.h"
#include "utlt_netheader.h"

#include "pfcp_message.h"
#include "pfcp_types.h"
#include "pfcp_xact.h"

#include "updk/env.h"
#include "updk/init.h"
#include "updk/rule.h"

#define MAX_NUM_OF_SUBNET       16

static UpfContext self;
static _Bool upfContextInitialized = 0;
static uint64_t g_sessionIdPool = 1;

UpfContext *Self() {
    return &self;
}

Status UpfContextInit() {
    UTLT_Assert(upfContextInitialized == 0, return STATUS_ERROR,
                "UPF context has been initialized!");

    memset(&self, 0, sizeof(UpfContext));

    // TODO : Add GTPv1 init here
    self.envParams = AllocEnvParams();
    UTLT_Assert(self.envParams, return STATUS_ERROR,
        "EnvParams alloc failed");

    self.upSock.fd = -1;
    SockSetEpollMode(&self.upSock, EPOLLIN);

    // TODO : Add PFCP init here
    ListHeadInit(&self.pfcpIPList);

    ListHeadInit(&self.ranS1uList);
    ListHeadInit(&self.upfN4List);
    ListHeadInit(&self.dnnList);

    self.recoveryTime = htonl(time((time_t *)NULL));

    // Set Default Value
    self.gtpDevNamePrefix = "upfgtp";
    // defined in utlt_3gpptypes instead of GTP_V1_PORT defined in GTP_PATH;
    self.gtpv1Port = GTPV1_U_UDP_PORT;
    self.pfcpPort = PFCP_UDP_PORT;
    strcpy(self.envParams->virtualDevice->deviceID, self.gtpDevNamePrefix);

    // Init Resource
    UpfSessionPoolInit();
    UeIpToUpfSessionMapInit();
    TeidToUpfSessionMapInit();

    PfcpNodeInit(); // init pfcp node for upfN4List (it will used pfcp node)
    TimerListInit(&self.timerServiceList);

    upfContextInitialized = 1;

    return STATUS_OK;
}

// TODO : Need to Remove List Members iterativelyatively
Status UpfContextTerminate() {
    UTLT_Assert(upfContextInitialized == 1, return STATUS_ERROR,
                "UPF context has been terminated!");

    Status status = STATUS_OK;

    // Terminate resource
    // TODO(vivek)
    // IndexTerminate(&upfSessionPool);

    PfcpRemoveAllNodes(&self.upfN4List);
    PfcpNodeTerminate();

    SockNodeListFree(&self.pfcpIPList);
    FreeVirtualDevice(self.envParams->virtualDevice);

    upfContextInitialized = 0;

    return status;
}

Status UpfPDRDeregisterToSessionByID(UpfSession *session, uint16_t id) {
    UTLT_Assert(session, return STATUS_ERROR, "session not found error");
    UTLT_Assert(session->pdr_list, return STATUS_ERROR, "PDR list not initialized");

    list_node_t *node = NULL;
    list_iterator_t *it;
    it = list_iterator_new(session->pdr_list, LIST_HEAD);
    while ((node = list_iterator_next(it))) {
        UpfPDR *pdr_i = (UpfPDR *) node->val;
        if (pdr_i->pdrId == id) {
            break;
        }
    }
    list_iterator_destroy(it);
    UTLT_Assert(node, return STATUS_ERROR, "PDR ID[%u] does NOT exist in UPF Context", id);
    list_remove(session->pdr_list, node);
    return STATUS_OK;
}

Status UpfFARDeregisterToSessionByID(UpfSession *session, uint16_t id) {
    UTLT_Assert(session, return STATUS_ERROR, "session not found error");
    UTLT_Assert(session->far_list, return STATUS_ERROR, "FAR list not initialized");

    list_node_t *node = NULL;
    list_iterator_t *it;
    it = list_iterator_new(session->far_list, LIST_HEAD);
    while ((node = list_iterator_next(it))) {
        UpfFAR *far = (UpfFAR *) node->val;
        if (far->farId == id) {
            break;
        }
    }
    UTLT_Assert(node, return STATUS_ERROR, "FAR ID[%u] does NOT exist in UPF Context", id);
    list_remove(session->far_list, node);
    return STATUS_OK;
}

Status UpfQERDeregisterToSessionByID(UpfSession *session, uint16_t id) {
    UTLT_Assert(session, return STATUS_ERROR, "session not found error");
    UTLT_Assert(session->qer_list, return STATUS_ERROR, "QER list not initialized");

    list_node_t *node = NULL;
    list_iterator_t *it;
    it = list_iterator_new(session->qer_list, LIST_HEAD);
    while ((node = list_iterator_next(it))) {
        UpfQER *qer = (UpfQER *) node->val;
        if (qer->qerId == id) {
            break;
        }
    }
    UTLT_Assert(node, return STATUS_ERROR, "QER ID[%u] does NOT exist in UPF Context", id);
    list_remove(session->qer_list, node);
    return STATUS_OK;
}

Status UpfPDRRegisterToSession(UpfSession *session, UpfPDR *pdr) {
    UTLT_Assert(session, return STATUS_ERROR, "session not found error");
    UTLT_Assert(session->pdr_list, return STATUS_ERROR, "PDR list not initialized");

    list_rpush(session->pdr_list, list_node_new(pdr));
}

Status UpfFARRegisterToSession(UpfSession *session, UpfFAR * far) {
    UTLT_Assert(session, return STATUS_ERROR, "session not found error");
    UTLT_Assert(session->far_list, return STATUS_ERROR, "FAR list not initialized");

    list_rpush(session->far_list, list_node_new(far));
}

Status UpfQERRegisterToSession(UpfSession *session, UpfQER *qer){
    UTLT_Assert(session, return STATUS_ERROR, "session not found error");
    UTLT_Assert(session->qer_list, return STATUS_ERROR, "QER list not initialized");

    list_rpush(session->qer_list, list_node_new(qer));
}

UpfPDR *UpfPDRFindByID(UpfSession *session, uint16_t id) {
    UTLT_Assert(session, return NULL, "session not found error");
    UTLT_Assert(session->pdr_list, return NULL, "PDR list not initialized");

    list_node_t *node;
    list_iterator_t *it;
    it = list_iterator_new(session->pdr_list, LIST_HEAD);
    while ((node = list_iterator_next(it))) {
        UpfPDR *pdr = (UpfPDR *) node->val;
        if (pdr->pdrId == id) {
            list_iterator_destroy(it);
            return pdr;
        }
    }
    list_iterator_destroy(it);
    return NULL;
}

UpfFAR *UpfFARFindByID(UpfSession *session, uint16_t id) {
    UTLT_Assert(session, return NULL, "session not found error");
    UTLT_Assert(session->far_list, return NULL, "FAR list not initialized");

    list_node_t *node;
    list_iterator_t *it;
    it = list_iterator_new(session->far_list, LIST_HEAD);
    while ((node = list_iterator_next(it))) {
        UpfFAR *far = (UpfFAR *) node->val;
        if (far->farId == id) {
            list_iterator_destroy(it);
            return far;
        }
    }
    list_iterator_destroy(it);
    return NULL;
}

UpfQER *UpfQERFindByID(UpfSession *session, uint16_t id){
    UTLT_Assert(session, return NULL, "session not found error");
    UTLT_Assert(session->qer_list, return NULL, "QER list not initialized");

    list_node_t *node;
    list_iterator_t *it;
    it = list_iterator_new(session->qer_list, LIST_HEAD);
    while ((node = list_iterator_next(it))) {
        UpfQER *qer = (UpfQER *) node->val;
        if (qer->qerId == id) {
            list_iterator_destroy(it);
            return qer;
        }
    }
    list_iterator_destroy(it);
    return NULL;
}

UpfSession *UpfSessionAdd(PfcpUeIpAddr *ueIp,
                          PfcpFTeid *teid,
                          uint8_t *dnn,
                          uint8_t pdnType) {
    UTLT_Assert(teid, return NULL, "teid is null");
    UTLT_Assert(ueIp, return NULL, "ueIp");
    UpfSession *session = NULL;

    session = UpfSessionAlloc(g_sessionIdPool);
    UTLT_Assert(session, return NULL, "session alloc error");

    strncpy((char*)session->pdn.dnn, (char*)dnn, MAX_DNN_LEN + 1);

    session->pdr_list = list_new();
    session->far_list = list_new();
    session->qer_list = list_new();
    //use to check srr flag
    session->srr_flag = false;

    session->teid = rte_cpu_to_be_32(teid->teid);
    session->pdn.paa.pdnType = pdnType;
    if (pdnType == PFCP_PDN_TYPE_IPV4) {
        session->ueIpv4.addr4.s_addr = rte_cpu_to_be_32(ueIp->addr4.s_addr);
    } else {
        UpfSessionRemove(session);
        UTLT_Assert(0, return NULL, "UnSupported PDN Type(%d)", pdnType);
    }

    UTLT_Assert(InsertTEIDtoSessionMap(session->teid, session) == STATUS_OK,
                UpfSessionRemove(session); return NULL, "Unable to create Uplink data for TEID (%u)", session->teid);
    UTLT_Assert(InsertUEIPtoSessionMap(session->ueIpv4.addr4.s_addr, session) == STATUS_OK,
                UpfSessionRemove(session); return NULL, "Unable to create Downlink data for UE IP (%u)", ueIp->addr4.s_addr);

    g_sessionIdPool++;
    return session;
}

Status UpfSessionRemove(UpfSession *session) {
    UTLT_Assert(session, return STATUS_ERROR, "session error");

    if (!session->far_list) {
        list_destroy(session->far_list);
    }

    if (!session->pdr_list) {
        list_destroy(session->pdr_list);
    }
    UeIpToUpfSessionMapFree(session->ueIpv4.addr4.s_addr);
    TeidToUpfSessionMapFree(session->teid);
    UpfSessionFree(session);
    return STATUS_OK;
}

UpfSession *UpfSessionAddByMessage(PfcpMessage *message) {
    UpfSession *session;

    PFCPSessionEstablishmentRequest *request =
      &message->pFCPSessionEstablishmentRequest;

    if (!request->nodeID.presence) {
        UTLT_Error("no NodeID");
        return NULL;
    }
    if (!request->cPFSEID.presence) {
        UTLT_Error("No cp F-SEID");
        return NULL;
    }
    if (!request->createPDR[0].presence) {
        UTLT_Error("No PDR");
        return NULL;
    }
    if (!request->createFAR[0].presence) {
        UTLT_Error("No FAR");
        return NULL;
    }
    if (!request->pDNType.presence) {
        UTLT_Error("No PDN Type");
        return NULL;
    }
    if (!request->createPDR[0].pDI.presence) {
        UTLT_Error("PDR PDI error");
        return NULL;
    }
    if (!request->createPDR[0].pDI.uEIPAddress.presence) {
        UTLT_Error("UE IP Address error");
        return NULL;
    }
    if (!request->createPDR[0].pDI.networkInstance.presence) {
        UTLT_Error("Interface error");
        return NULL;
    }

    if (!request->createPDR[0].pDI.localFTEID.presence) {
        UTLT_Error("TEID error");
        return NULL;
    }

    session = UpfSessionAdd((PfcpUeIpAddr *)
                            request->createPDR[0].pDI.uEIPAddress.value,
                            (PfcpFTeid *) request->createPDR[0].pDI.localFTEID.value,
                            request->createPDR[0].pDI.networkInstance.value,
                            ((int8_t *)request->pDNType.value)[0]);
    UTLT_Assert(session, return NULL, "session add error");

    session->smfSeid = *(uint64_t*)request->cPFSEID.value;
    UTLT_Trace("UPF Establishment UPF SEID: %lu", session->upfSeid);

    return session;
}
