/*********************************************************************
 *                     openNetVM
 *              https://sdnfv.github.io
 *
 *   BSD LICENSE
 *
 *   Copyright(c)
 *            2015-2019 George Washington University
 *            2015-2019 University of California Riverside
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * The name of the author may not be used to endorse or promote
 *       products derived from this software without specific prior
 *       written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ********************************************************************/

#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <rte_common.h>
#include <rte_ip.h>
#include <rte_mbuf.h>
#include <rte_gtp.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

#include "gtp.h"
#include "upf_context.h"

#include "onvm_nflib.h"
#include "onvm_pkt_helper.h"

#define NF_TAG "upf_u"

#if 0
#define SELF_IP RTE_IPV4(10, 100, 200, 3)
#else
#define SELF_IP 63464458
#endif

#define SRC_INTF_ACCESS     0
#define SRC_INTF_CORE       1
#define SRC_INTF_SGI_LAN    2
#define SRC_INTF_CP         3
#define SRC_INTF_NUM        (SRC_INTF_CP + 1)

static struct rte_ether_addr dn_eth;
static struct rte_ether_addr cn_dn_eth;
static struct rte_ether_addr cn_ue_eth;


#define MAX_OF_BUFFER_PACKET_SIZE 1600
struct rte_mbuf *buffer[MAX_OF_BUFFER_PACKET_SIZE];
uint32_t buffer_length = 0;


static inline uint8_t SourceInterfaceToPort (uint8_t interface) {
    switch (interface) {
        case SRC_INTF_ACCESS:
            return 0;
        case SRC_INTF_CORE:
        case SRC_INTF_SGI_LAN:
            return 1;
        case SRC_INTF_CP:
            return -1;
        default:
            return -1;
    }
}

uint64_t seid = 0;
uint16_t pdrId = 0;

UPDK_PDR *GetPdrByUeIpAddress(struct rte_mbuf *pkt, uint32_t ue_ip) {
    UpfSession *session = UpfSessionFindByUeIP(ue_ip);
    UTLT_Assert(session, return NULL, "session not found error");
    UTLT_Assert(session->pdr_list, return NULL, "PDR list not initialized");
    UTLT_Assert(session->pdr_list->len, return NULL, "PDR list contains 0 rules");

    list_node_t *node = session->pdr_list->head;
    UpfPDR *pdr = NULL;
    while (node) {
        pdr = (UpfPDR *) node->val;
        node = node->next;
        if (pdr->flags.pdi) {
            if (pdr->pdi.flags.sourceInterface) {
                if (SourceInterfaceToPort(pdr->pdi.sourceInterface) != pkt->port) {
                    continue;
                }
            }
            break;
        }
    }
    if (pdr) {
        seid = session->smfSeid;
        pdrId = pdr->pdrId;
    }
    return pdr;
}

UPDK_PDR *GetPdrByTeid(struct rte_mbuf *pkt, uint32_t td) {
    UpfSession *session = UpfSessionFindByTeid(td);
    UTLT_Assert(session, return NULL, "session not found error");
    UTLT_Assert(session->pdr_list, return NULL, "PDR list not initialized");
    UTLT_Assert(session->pdr_list->len, return NULL, "PDR list contains 0 rules");

    list_node_t *node = session->pdr_list->head;
    UpfPDR *pdr = NULL;
    while (node) {
        pdr = (UpfPDR *) node->val;
        node = node->next;
        if (pdr->flags.pdi) {
            if (pdr->pdi.flags.sourceInterface) {
                if (SourceInterfaceToPort(pdr->pdi.sourceInterface) != pkt->port) {
                    continue;
                }
            }
            break;
        }
    }
    if (pdr) {
        seid = session->smfSeid;
        pdrId = pdr->pdrId;
    }
    return pdr;
}

void Encap(struct rte_mbuf *pkt, UPDK_FAR *far, UPDK_QER *qer) {
    UPDK_OuterHeaderCreation *outerHeaderCreation = &(far->forwardingParameters.outerHeaderCreation);
    uint16_t outerHeaderLen = 0;
    uint16_t payloadLen = pkt->data_len;
    if (qer) {
        outerHeaderLen = sizeof(struct rte_ipv4_hdr) +
            sizeof(struct rte_udp_hdr) +
            sizeof(gtpv1_t) +
            sizeof(gtpv1_hdr_opt_t) +
            sizeof(pdu_sess_container_hdr_t);
        payloadLen += sizeof(gtpv1_hdr_opt_t) + sizeof(pdu_sess_container_hdr_t);

    } else {
        outerHeaderLen = sizeof(struct rte_ipv4_hdr) +
            sizeof(struct rte_udp_hdr) +
            sizeof(gtpv1_t);
    }

    gtpv1_t *gtp_hdr = (gtpv1_t *)rte_pktmbuf_prepend(pkt, outerHeaderLen);
    gtp_hdr = rte_pktmbuf_mtod_offset(pkt, gtpv1_t *, sizeof(struct rte_ipv4_hdr) + sizeof(struct rte_udp_hdr));
    gtpv1_set_header(gtp_hdr, payloadLen , outerHeaderCreation->teid);

    if (qer) {
        gtp_hdr->flags |= GTP1_F_EXTHDR;//enable extension header
        gtpv1_hdr_opt_t *gtp_opt_hdr = rte_pktmbuf_mtod_offset(pkt, gtpv1_hdr_opt_t *, sizeof(struct rte_ipv4_hdr) + sizeof(struct rte_udp_hdr) + sizeof(gtpv1_t));
        gtp_opt_hdr->seq_number = 0;
        gtp_opt_hdr->NPDU = 0;
        gtp_opt_hdr->next_ehdr_type = GTPV1_NEXT_EXT_HDR_TYPE_85;

        pdu_sess_container_hdr_t *pdu_ss_ctr = rte_pktmbuf_mtod_offset(pkt, pdu_sess_container_hdr_t *, sizeof(struct rte_ipv4_hdr) + sizeof(struct rte_udp_hdr) + sizeof(gtpv1_t) + sizeof(gtpv1_hdr_opt_t));
        pdu_ss_ctr->length = 0x01;
        pdu_ss_ctr->pdu_sess_ctr = rte_cpu_to_be_16(QERGetQFI(qer));
        pdu_ss_ctr->next_hdr = 0x00;
    }

    struct rte_udp_hdr *udp_hdr = rte_pktmbuf_mtod_offset(pkt, struct rte_udp_hdr *, sizeof(struct rte_ipv4_hdr));
    onvm_pkt_fill_udp(udp_hdr, UDP_PORT_FOR_GTP, UDP_PORT_FOR_GTP, payloadLen + sizeof(gtpv1_t));//pktdatalen-outerheaderlen=rawpacket_len, but here, udppayloadlen should be raw + gtp header 

    struct rte_ipv4_hdr *ipv4_hdr = rte_pktmbuf_mtod_offset(pkt, struct rte_ipv4_hdr *, 0);
    onvm_pkt_fill_ipv4(ipv4_hdr, rte_cpu_to_be_32(SELF_IP), rte_cpu_to_be_32(outerHeaderCreation->ipv4.s_addr), IPPROTO_UDP);
    ipv4_hdr->total_length = rte_cpu_to_be_16(payloadLen + sizeof(gtpv1_t) + sizeof(struct rte_udp_hdr) +sizeof(struct rte_ipv4_hdr)); //raw+gtp8+udp8+ip20
    ipv4_hdr->hdr_checksum = rte_ipv4_cksum(ipv4_hdr);
}

static int HandlePacketWithFar(struct rte_mbuf *pkt, UPDK_FAR *far, UPDK_QER *qer, struct onvm_pkt_meta *meta) {
    int buff = 0;
#define FAR_ACTION_MASK   0x07
    if (far->flags.applyAction) {
        switch (far->applyAction & FAR_ACTION_MASK) {
            case UPDK_FAR_APPLY_ACTION_DROP:
                meta->action = ONVM_NF_ACTION_DROP;
                break;
            case UPDK_FAR_APPLY_ACTION_FORW:
                if (far->flags.forwardingParameters) {
                    if (far->forwardingParameters.flags.outerHeaderCreation) {
                        UPDK_OuterHeaderCreation *outerHeaderCreation = &(far->forwardingParameters.outerHeaderCreation);
                        switch (outerHeaderCreation->description) {
                            case UPDK_OUTER_HEADER_CREATION_DESCRIPTION_GTPU_UDP_IPV4: {
                                Encap(pkt, far, qer);
                            }   break;
                            case UPDK_OUTER_HEADER_CREATION_DESCRIPTION_GTPU_UDP_IPV6:
                            case UPDK_OUTER_HEADER_CREATION_DESCRIPTION_UDP_IPV4:
                            case UPDK_OUTER_HEADER_CREATION_DESCRIPTION_UDP_IPV6:
                            default:
                                UTLT_Error("Unknown outer header creation info");
                        }
                    }
                }
                meta->destination = pkt->port ^ 1;
                meta->action = ONVM_NF_ACTION_OUT;
                break;
            case UPDK_FAR_APPLY_ACTION_BUFF:
                meta->destination = pkt->port ^ 1;
                meta->action = ONVM_NF_ACTION_DROP;
                if (buffer_length < MAX_OF_BUFFER_PACKET_SIZE) {
                    Encap(pkt, far, qer);
                    buffer[buffer_length++] = pkt;
                    meta->action = ONVM_NF_ACTION_OUT;
                    buff = 1;
                }
                break;
            default:
                UTLT_Error("Unspec apply action[%u] in FAR[%u]",
                           far->applyAction,
                           far->farId);
        }
        //TODO(vivek): Complete these actions:
        if (far->applyAction & UPDK_FAR_APPLY_ACTION_NOCP) {
            // Send message to UPF-C
            Event *msg= (Event *) rte_calloc(NULL, 1, sizeof(Event), 0);
            msg->type = UPF_EVENT_SESSION_REPORT;
            msg->arg0 = seid;
            msg->arg1 = pdrId;
            /*
            struct ReportMsg *msg= (struct ReportMsg *) rte_calloc(NULL, 1, sizeof(struct ReportMsg), 0);
            msg->seid = seid;
            msg->pdrId = pdrId;
            */
            onvm_nflib_send_msg_to_nf(2, msg);
        }
        if (far->applyAction & UPDK_FAR_APPLY_ACTION_DUPL) {
            UTLT_Error("Duplicate Apply action: %u not supported, dropping the packet", far->applyAction);
        }
    }
    return buff;
}

static inline void AttachL2Header(struct rte_mbuf *pkt, bool is_dl) {
    // Prepend ethernet header
    struct rte_ether_hdr *eth_hdr =
        (struct rte_ether_hdr *)rte_pktmbuf_prepend(
                pkt, (uint16_t)sizeof(struct rte_ether_hdr));

    //next hop's mac address
    if (is_dl == true) {
        rte_ether_addr_copy(&cn_ue_eth, &eth_hdr->s_addr);
        eth_hdr->d_addr.addr_bytes[0] = 0x3c;
        eth_hdr->d_addr.addr_bytes[1] = 0xfd;
        eth_hdr->d_addr.addr_bytes[2] = 0xfe;
        eth_hdr->d_addr.addr_bytes[3] = 0x73;
        eth_hdr->d_addr.addr_bytes[4] = 0x82;
        eth_hdr->d_addr.addr_bytes[5] = 0xa0;

    } else { 
        rte_ether_addr_copy(&cn_dn_eth, &eth_hdr->s_addr);
        rte_ether_addr_copy(&dn_eth, &eth_hdr->d_addr);
    }

    eth_hdr->ether_type = rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4);
}

static int packet_handler(struct rte_mbuf *pkt,
                          struct onvm_pkt_meta *meta,
                          struct onvm_nf_local_ctx *nf_local_ctx) {
    bool is_dl = false;
    meta->action = ONVM_NF_ACTION_DROP;
    struct rte_ipv4_hdr *iph = onvm_pkt_ipv4_hdr(pkt);

    if (iph == NULL) {
        return 0;
    }

    UPDK_PDR *pdr = NULL;
    // Step 1: Identify if it is a uplink packet or downlink packet
    if (iph->dst_addr == SELF_IP) {  //
        struct rte_udp_hdr *udp_header = onvm_pkt_udp_hdr(pkt);
        if (udp_header == NULL) {
            return 0;
        }
        // invariant(dst_port == GTPV1_PORT);
        // extract TEID from
        // Step 2: Get PDR rule
        uint32_t teid = get_teid_gtp_packet(pkt, udp_header);
        pdr = GetPdrByTeid(pkt, teid);
    } else {
        // Step 2: Get PDR rule
        pdr = GetPdrByUeIpAddress(pkt, rte_cpu_to_be_32(iph->dst_addr));
        is_dl = true;
    }

    if (!pdr) {
        printf("no PDR found for %pI4, skip\n", &iph->dst_addr);
        // TODO(vivek): what to do?
        return 0;
    }
    rte_pktmbuf_adj(pkt, sizeof(struct rte_ether_hdr));

    UPDK_FAR *far;
    far = pdr->far;
    if (!far) {
        printf("There is no FAR related to PDR[%u]\n", pdr->pdrId);
        meta->action = ONVM_NF_ACTION_DROP;
        return 0;
    }

    if (pdr->flags.outerHeaderRemoval) {
        uint16_t outerHeaderLen = 0;
        switch (pdr->outerHeaderRemoval) {
            case OUTER_HEADER_REMOVAL_GTP_IP4: {
                outerHeaderLen = sizeof(struct rte_ipv4_hdr) +
                                 sizeof(struct rte_udp_hdr);

                //get gtp_header length  
                uint16_t gtp_length = get_gtpu_header_len(pkt);
                outerHeaderLen += gtp_length;

                rte_pktmbuf_adj(pkt, outerHeaderLen);
            } break;
            case OUTER_HEADER_REMOVAL_GTP_IP6:
            case OUTER_HEADER_REMOVAL_UDP_IP4:
            case OUTER_HEADER_REMOVAL_UDP_IP6:
            case OUTER_HEADER_REMOVAL_IP4:
            case OUTER_HEADER_REMOVAL_IP6:
            case OUTER_HEADER_REMOVAL_GTP:
            case OUTER_HEADER_REMOVAL_S_TAG:
            case OUTER_HEADER_REMOVAL_S_C_TAG:
            default:
                printf("unknown\n");
        }
    }

    int status = 0;
    status = HandlePacketWithFar(pkt, far, pdr->qer, meta);
    AttachL2Header(pkt, is_dl);
    return status;
}

void
msg_handler(void *msg_data, struct onvm_nf_local_ctx *nf_local_ctx) {
    struct onvm_nf *nf;
    nf = nf_local_ctx->nf;
    onvm_pkt_process_tx_batch(nf->nf_tx_mgr, buffer, buffer_length, nf);
    onvm_pkt_flush_all_nfs(nf->nf_tx_mgr, nf);
    printf("Sending out %u packets\n", buffer_length);
    buffer_length = 0;
}


int main(int argc, char *argv[]) {
    int arg_offset;
    struct onvm_nf_local_ctx *nf_local_ctx;
    struct onvm_nf_function_table *nf_function_table;

    nf_local_ctx = onvm_nflib_init_nf_local_ctx();
    onvm_nflib_start_signal_handler(nf_local_ctx, NULL);
    nf_function_table = onvm_nflib_init_nf_function_table();
    nf_function_table->pkt_handler = &packet_handler;
    nf_function_table->msg_handler = &msg_handler;

    if ((arg_offset = onvm_nflib_init(argc, argv, NF_TAG, nf_local_ctx,
                    nf_function_table)) < 0) {
        onvm_nflib_stop(nf_local_ctx);
        if (arg_offset == ONVM_SIGNAL_TERMINATION) {
            printf("Exiting due to user termination\n");
            return 0;
        } else {
            rte_exit(EXIT_FAILURE, "Failed ONVM init\n");
        }
    }

    int ret;
    ret = rte_eth_macaddr_get(0, &cn_ue_eth);
    // Panda removed the clause below.
    //if (ret < 0)
    //    rte_exit(EXIT_FAILURE, "Cannot get MAC address: err=%d, port=%u\n", ret, 0);
    ret = rte_eth_macaddr_get(1, &cn_dn_eth);
    // Panda removed the clause below.
    //if (ret < 0)
    //    rte_exit(EXIT_FAILURE, "Cannot get MAC address: err=%d, port=%u\n", ret, 1);

    // 8c:dc:d4:ac:6c:7d
    dn_eth.addr_bytes[0] = 0x8c;
    dn_eth.addr_bytes[1] = 0xdc;
    dn_eth.addr_bytes[2] = 0xd4;
    dn_eth.addr_bytes[3] = 0xac;
    dn_eth.addr_bytes[4] = 0x6c;
    dn_eth.addr_bytes[5] = 0x7d;

    UpfSessionPoolInit ();
    UeIpToUpfSessionMapInit();
    TeidToUpfSessionMapInit();

    onvm_nflib_run(nf_local_ctx);

    onvm_nflib_stop(nf_local_ctx);
    printf("If we reach here, program is ending\n");
    return 0;
}
