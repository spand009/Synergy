#ifndef __N4_ONVM_PFCP_PATH_H__
#define __N4_ONVM_PFCP_PATH_H__

#include <rte_mbuf.h>

#include "utlt_debug.h"

#include "onvm_nflib.h"
#include "onvm_pkt_helper.h"

void msg_handler(void *msg_data, struct onvm_nf_local_ctx *nf_local_ctx);
int packet_handler(struct rte_mbuf *pkt, struct onvm_pkt_meta *meta, struct onvm_nf_local_ctx *nf_local_ctx);

Status PfcpServerInit();
Status PfcpServerTerminate();

#endif /* __N4_PFCP_PATH_H__ */
