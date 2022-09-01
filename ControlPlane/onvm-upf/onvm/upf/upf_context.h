#ifndef __UPF_CONTEXT_H__
#define __UPF_CONTEXT_H__

#include <stdint.h>
#include <netinet/in.h>
#include <net/if.h>
#include <pthread.h>

#include "utlt_list.h"
#include "utlt_buff.h"
#include "utlt_event.h"
#include "utlt_thread.h"
#include "utlt_network.h"
#include "utlt_hash.h"
#include "utlt_3gppTypes.h"
#include "utlt_timer.h"

#include "pfcp_node.h"
#include "pfcp_message.h"

#include "updk/env.h"
#include "updk/init.h"
#include "updk/rule_pdr.h"
#include "updk/rule_far.h"
#include "updk/rule_qer.h"

#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _UpfUeIp      UpfUeIp;

// Rule structure dependent on UPDK
typedef UPDK_PDR UpfPDR;
typedef UPDK_FAR UpfFAR;
typedef UPDK_QER UpfQER;

typedef enum _UpfEvent {

    UPF_EVENT_N4_MESSAGE,
    UPF_EVENT_SESSION_REPORT,
    UPF_EVENT_N4_T3_RESPONSE,
    UPF_EVENT_N4_T3_HOLDING,

    UPF_EVENT_TOP,

} UpfEvent;

struct ReportMsg {
    uint64_t seid;
    uint16_t pdrId;
};

typedef struct {
    uint8_t         role;                // UpfRole
    const char      *gtpDevNamePrefix;   // Default : "upfgtp"

    ListHead        gtpInterfaceList;    // name of interface (char*)
    // Add context related to GTP-U here
    uint16_t        gtpv1Port;           // Default : GTP_V1_PORT
    EnvParams       *envParams;          // EnvParams parsing from UPF Config
    Sock            upSock;              // User Plane Socket builds from Gtpv1EnvInit()

    // Add context related to PFCP here
    uint16_t        pfcpPort;            // Default : PFCP_PORT
    ListHead        pfcpIPList;          // PFCP IPv4 Server List (SockNode)
    ListHead        pfcpIPv6List;        // PFCP IPv6 Server List (SockNode)
    Sock            *pfcpSock;           // IPv4 Socket
    Sock            *pfcpSock6;          // IPv6 Socket
    SockAddr        *pfcpAddr;           // IPv4 Address
    SockAddr        *pfcpAddr6;          // IPv6 Address

    /* Use Array or Hash for better performance
     * Because max size of the list is 65536 due to the max of PDR ID
     * We can use array for O(1) search instead of O(N) search in list
     * Trade off of speed and memory size
     */
    //ListNode        bufPacketList;       // save pdrId and buffer here

    // DNS
#define MAX_NUM_OF_DNS          2
    const char      *dns[MAX_NUM_OF_DNS];
    const char      *dns6[MAX_NUM_OF_DNS];

    // Add other context here
    ListHead        ranS1uList;         // RAN List connected to UPF
    ListHead        upfN4List;          // UPF PFCP Node List
    ListHead        dnnList;

    // Different list of policy rule
    // TODO: if implementing QER in kernel, remove these list
    ListHead        qerList;
    ListHead        urrList;

    uint32_t        recoveryTime;       // UTC time
    TimerList       timerServiceList;

    // Add some self library structure here
    int             epfd;               // Epoll fd
    EvtQId          eventQ;             // Event queue communicate between UP and CP
    ThreadID        pktRecvThread;      // Receive packet thread

    // Session : hash(IMSI+DNN)
    Hash            *sessionHash;

    // Config file
    const char      *configFilePath;
} UpfContext;

typedef struct _UpfUeIp {
    union {
        struct in_addr addr4;
        struct in6_addr addr6;
    };
} UpfUeIp;

typedef struct _UpfSession {
    int             index;
    uint32_t        hashKey;

    uint64_t        upfSeid;
    uint64_t        smfSeid;

    /* DNN Config */
    Pdn             pdn;
    UpfUeIp         ueIpv4;
    UpfUeIp         ueIpv6;
    uint32_t        teid;

    /* User location */
    Tai             tai;

    /* GTP, PFCP context */
    PfcpNode        *pfcpNode;

    list_t          *pdr_list;
    list_t          *far_list;
    list_t          *qer_list;

    bool srr_flag;
} UpfSession;

UpfContext *Self();
Status UpfContextInit();
Status UpfContextTerminate();

// Session
int UpfSessionPoolInit(void);
int UeIpToUpfSessionMapInit(void);
int TeidToUpfSessionMapInit(void);

// Create Session APIs
UpfSession *UpfSessionAlloc(uint64_t seid);
UpfSession *UpfSessionAddByMessage(PfcpMessage *message);
Status InsertUEIPtoSessionMap(const uint32_t ue_ip, UpfSession *session);
Status InsertTEIDtoSessionMap(const uint32_t teid, UpfSession *session);

// Delete Session APIs
void UpfSessionFree(UpfSession *);
Status UpfSessionRemove(UpfSession *session);
void TeidToUpfSessionMapFree(uint32_t teid);
void UeIpToUpfSessionMapFree(uint32_t ueip);

// Find Session APIs
UpfSession *UpfSessionFindBySeid(uint64_t seid);
UpfSession *UpfSessionFindByTeid(uint32_t teid);
UpfSession *UpfSessionFindByUeIP(uint32_t ueip);

Status UpfPDRRegisterToSession(UpfSession *session, UpfPDR *pdr);
Status UpfFARRegisterToSession(UpfSession *session, UpfFAR *far);
Status UpfQERRegisterToSession(UpfSession *session, UpfQER *qer);//implement//upf_context.c//V

UpfPDR *UpfPDRFindByID(UpfSession *session, uint16_t id);
UpfFAR *UpfFARFindByID(UpfSession *session, uint16_t id);
UpfQER *UpfQERFindByID(UpfSession *session, uint16_t id);//implement//V

Status UpfPDRDeregisterToSessionByID(UpfSession *session, uint16_t id);
Status UpfFARDeregisterToSessionByID(UpfSession *session, uint16_t id);
Status UpfQERDeregisterToSessionByID(UpfSession *session, uint16_t id);//implement//V

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __UPF_CONTEXT_H__ */
