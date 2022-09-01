#define TRACE_MODULE _pfcp_path

#include <errno.h>

#include "utlt_debug.h"
#include "utlt_3gppTypes.h"
#include "utlt_network.h"
#include "utlt_buff.h"

#include "pfcp_node.h"

#include "pfcp_path.h"

#include "onvm_nflib.h"

struct onvm_nf_local_ctx *ctx;

void OnvmSetNfContext(struct onvm_nf_local_ctx *nf_ctx) {
    ctx = nf_ctx;
}

Status PfcpServer(SockNode *snode, SockHandler handler) {
    Status status;

    UTLT_Assert(snode, return STATUS_ERROR, "socket node error");

    // TODO: config - check if snode->ip is already set when parsing config
    snode->sock = UdpServerCreate(AF_INET, snode->ip, 8805);
    status = SockRegister(snode->sock, handler, NULL);
    UTLT_Assert(status == STATUS_OK, return STATUS_ERROR, "Handler register error");

    UTLT_Trace("PfcpServer() [%s]:%d\n", GetIP(&snode->sock->localAddr), 8805);

    return STATUS_OK;
}

Status PfcpServerList(ListHead *list, SockHandler handler, int epfd) {
    Status status;
    SockNode *node, *nextNode = NULL;

    UTLT_Assert(list, return STATUS_ERROR, "Server list error");
    UTLT_Assert(handler, return STATUS_ERROR, "handler error");

    ListForEachSafe(node, nextNode, list) {
        node->sock = SocketAlloc();
        node->sock->localAddr._family = AF_INET;
        status = UdpSockSetAddr(&node->sock->localAddr, AF_INET, node->ip, 8805);
        UTLT_Assert(status == STATUS_OK, return STATUS_ERROR, "Unable to set node->ip");
    }

    return STATUS_OK;
}

Sock *PfcpLocalSockFirst(ListHead *list) {
    SockNode *node, *nextNode = NULL;
    Sock *sock = NULL;

    UTLT_Assert(list, return NULL, "list error");

    ListForEachSafe(node, nextNode, list) {
        sock = node->sock;
        if (sock) {
            return sock;
        }
    }

    return NULL;
}

SockAddr *PfcpLocalAddrFirst(ListHead *list) {
    SockNode *node, *nextNode = NULL;
    SockAddr *addr = NULL;

    UTLT_Assert(list, return NULL, "list error");

    ListForEachSafe(node, nextNode, list) {
        addr = &node->sock->localAddr;
        if (addr) {
            return addr;
        }
    }

    return NULL;
}

Status PfcpSend(PfcpNode *node, Bufblk *bufBlk) {
    Sock *sock = NULL;
    SockAddr *addr = NULL;

    UTLT_Assert(node, return STATUS_ERROR, "No PfcpNode");
    UTLT_Assert(bufBlk, return STATUS_ERROR, "No Bufblk");
    sock = node->sock;
    UTLT_Assert(sock, return STATUS_ERROR, "No sock of node");

#if 1
    uint32_t bufferLength = bufBlk->len;
    uint32_t i;
    struct rte_mempool *pktmbuf_pool;

    pktmbuf_pool = rte_mempool_lookup(PKTMBUF_POOL_NAME);
    if (pktmbuf_pool == NULL) {
        return STATUS_ERROR;
    }

    struct onvm_pkt_meta *pmeta;
    struct rte_ether_hdr *ethHdr;
    struct rte_udp_hdr *udphdr;
    struct rte_ipv4_hdr *ipv4Hdr;

    struct rte_mbuf *pkt = rte_pktmbuf_alloc(pktmbuf_pool);
    if (pkt == NULL) {
        return STATUS_ERROR;
    }

    rte_pktmbuf_prepend(pkt, bufferLength);
    rte_memcpy(rte_pktmbuf_mtod(pkt, char *), bufBlk->buf, bufferLength);

    // Prepending UDP Header
    udphdr = (struct rte_udp_hdr *)rte_pktmbuf_prepend(
            pkt, sizeof(struct rte_udp_hdr));
    udphdr->src_port = sock->localAddr._port;
    udphdr->dst_port = sock->remoteAddr._port;
    udphdr->dgram_len = rte_cpu_to_be_16(bufferLength + sizeof(struct rte_udp_hdr));

    // Prepending IPv4 Header
    ipv4Hdr = (struct rte_ipv4_hdr *)rte_pktmbuf_prepend(
            pkt, sizeof(struct rte_ipv4_hdr));
    ipv4Hdr->version_ihl =
        IPVERSION << 4 | sizeof(struct rte_ipv4_hdr) / RTE_IPV4_IHL_MULTIPLIER;
    ipv4Hdr->time_to_live = IPDEFTTL;
    ipv4Hdr->next_proto_id = 17;
    ipv4Hdr->src_addr = sock->localAddr.s4.sin_addr.s_addr;
    ipv4Hdr->dst_addr = sock->remoteAddr.s4.sin_addr.s_addr;
    ipv4Hdr->total_length = rte_cpu_to_be_32(
            bufferLength + sizeof(struct rte_ipv4_hdr) + sizeof(struct rte_udp_hdr));

    // Prepending IPv4 Header
    ethHdr = (struct rte_ether_hdr *)rte_pktmbuf_prepend(pkt, RTE_ETHER_HDR_LEN);

    if (onvm_get_macaddr(0, &ethHdr->s_addr) == -1) {
        onvm_get_fake_macaddr(&ethHdr->s_addr);
    }

    for (i = 0; i < RTE_ETHER_ADDR_LEN; ++i) {
        ethHdr->d_addr.addr_bytes[i] = i;
    }

    ethHdr->ether_type = rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4);

    // Fill out the meta data of the packet
    pmeta = onvm_get_pkt_meta(pkt);
    pmeta->destination = 3; // serviceId;
    pmeta->action = ONVM_NF_ACTION_TONF;
    pkt->pkt_len = bufferLength + sizeof(struct rte_ether_hdr) + 20 + sizeof(struct rte_udp_hdr);  //???
    pkt->data_len = bufferLength + sizeof(struct rte_ether_hdr) + 20 + sizeof(struct rte_udp_hdr);  //???
    /* Copy the packet into the rte_mbuf data section */

    // send out the generated packet
    int s = onvm_nflib_return_pkt(ctx->nf, pkt);
    if (s < 0) {
        return STATUS_ERROR;
    }

    return STATUS_OK;
#else
    Sock *sock = NULL;
    SockAddr *addr = NULL;

    UTLT_Assert(node, return STATUS_ERROR, "No PfcpNode");
    UTLT_Assert(bufBlk, return STATUS_ERROR, "No Bufblk");
    sock = node->sock;
    UTLT_Assert(sock, return STATUS_ERROR, "No sock of node");

    /* New Interface */
    addr = &(sock->remoteAddr);
    UTLT_Assert(addr, return STATUS_ERROR, "remote addr error");
    UTLT_Assert(bufBlk, , "buff NULL");
    UTLT_Assert(bufBlk->buf, , "buff buff NULL");

    Status status = SockSendTo(sock, bufBlk->buf, bufBlk->len);
    UTLT_Assert(status == STATUS_OK, return STATUS_ERROR,
            "Sent [%s]:%d failed(%d:%s)", GetIP(addr), GetPort(addr), errno, strerror(errno));

    return STATUS_OK;
#endif
}
