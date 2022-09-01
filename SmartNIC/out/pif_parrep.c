/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/me.h>
#include <hashmap.h>
#include "pif_common.h"


static __inline __gpr int handle_node_start(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktdataoff, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len, int *pstate)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    __gpr int hdrsz = 0;
#ifdef PIF_DEBUG
    __debug_label("pif_parrep_state_start");
#endif

    *(pstate) = PIF_PARREP_STATE_parse_ethernet;

    return hdrsz;
}


static __inline __gpr int handle_node_parse_ethernet(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktdataoff, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len, int *pstate)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    __gpr int hdrsz = 0;
    __lmem struct pif_header_ethernet *ethernet;
    __gpr int select_value[1] = {0};

#ifdef PIF_DEBUG
    __debug_label("pif_parrep_state_parse_ethernet");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (lm_ptr + PIF_PARREP_ethernet_OFF_LW);

    mem2lmem_copy(pktdata + (pktdataoff + hdrsz),
                  lm_ptr,
                  PIF_PARREP_ethernet_OFF_LW,
                  PIF_PARREP_ethernet_LEN_LW);
    hdrsz += PIF_PARREP_ethernet_LEN_B;

    select_value[0] |= ethernet->etherType << 0;

    if (((select_value[0]) == (0x800))) {
        *(pstate) = PIF_PARREP_STATE_parse_ipv4;
    } else {
        *(pstate) = PIF_PARREP_STATE_fwd;
    }

    PIF_PARREP_SET_ethernet_VALID(prdata);
    PIF_PARREP_SET_ethernet_ORIG_LEN(prdata, hdrsz);

    return hdrsz;
}


static __inline __gpr int handle_node_parse_ipv4(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktdataoff, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len, int *pstate)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    __gpr int hdrsz = 0;
    __lmem struct pif_header_ipv4 *ipv4;
    __gpr int select_value[1] = {0};

#ifdef PIF_DEBUG
    __debug_label("pif_parrep_state_parse_ipv4");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (lm_ptr + PIF_PARREP_ipv4_OFF_LW);

    mem2lmem_copy(pktdata + (pktdataoff + hdrsz),
                  lm_ptr,
                  PIF_PARREP_ipv4_OFF_LW,
                  PIF_PARREP_ipv4_LEN_LW);
    hdrsz += PIF_PARREP_ipv4_LEN_B;

#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
    {
        __lmem struct pif_global_flowkey_parse_ipv4 *fk = (__lmem struct pif_global_flowkey_parse_ipv4 *)fk_ptr;
        fk->ipv4__srcAddr = ipv4->srcAddr;
        fk->ipv4__dstAddr = ipv4->dstAddr;
        (*fk_len) += 2;
    }
#endif
    select_value[0] |= ipv4->protocol << 0;

    if (((select_value[0]) == (0x6))) {
        *(pstate) = PIF_PARREP_STATE_parse_tcp;
    } else if (((select_value[0]) == (0x11))) {
        *(pstate) = PIF_PARREP_STATE_parse_udp;
    } else {
        *(pstate) = PIF_PARREP_STATE_fwd;
    }

    PIF_PARREP_SET_ipv4_VALID(prdata);
    PIF_PARREP_SET_ipv4_ORIG_LEN(prdata, hdrsz);

    return hdrsz;
}


static __inline __gpr int handle_node_parse_tcp(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktdataoff, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len, int *pstate)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    __gpr int hdrsz = 0;
    __lmem struct pif_header_tcp *tcp;

#ifdef PIF_DEBUG
    __debug_label("pif_parrep_state_parse_tcp");
#endif

    tcp = (__lmem struct pif_header_tcp *) (lm_ptr + PIF_PARREP_tcp_OFF_LW);

    mem2lmem_copy(pktdata + (pktdataoff + hdrsz),
                  lm_ptr,
                  PIF_PARREP_tcp_OFF_LW,
                  PIF_PARREP_tcp_LEN_LW);
    hdrsz += PIF_PARREP_tcp_LEN_B;

    *(pstate) = PIF_PARREP_STATE_fwd;

    PIF_PARREP_SET_tcp_VALID(prdata);
    PIF_PARREP_SET_tcp_ORIG_LEN(prdata, hdrsz);

    return hdrsz;
}


static __inline __gpr int handle_node_parse_udp(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktdataoff, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len, int *pstate)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    __gpr int hdrsz = 0;
    __lmem struct pif_header_udp *udp;
    __gpr int select_value[1] = {0};

#ifdef PIF_DEBUG
    __debug_label("pif_parrep_state_parse_udp");
#endif

    udp = (__lmem struct pif_header_udp *) (lm_ptr + PIF_PARREP_udp_OFF_LW);

    mem2lmem_copy(pktdata + (pktdataoff + hdrsz),
                  lm_ptr,
                  PIF_PARREP_udp_OFF_LW,
                  PIF_PARREP_udp_LEN_LW);
    hdrsz += PIF_PARREP_udp_LEN_B;

    select_value[0] |= udp->dstPort << 0;

    if (((select_value[0]) == (0x868))) {
        *(pstate) = PIF_PARREP_STATE_parse_gtpu;
    } else {
        *(pstate) = PIF_PARREP_STATE_fwd;
    }

    PIF_PARREP_SET_udp_VALID(prdata);
    PIF_PARREP_SET_udp_ORIG_LEN(prdata, hdrsz);

    return hdrsz;
}


static __inline __gpr int handle_node_parse_gtpu(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktdataoff, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len, int *pstate)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    __gpr int hdrsz = 0;
    __lmem struct pif_header_gtpu *gtpu;

#ifdef PIF_DEBUG
    __debug_label("pif_parrep_state_parse_gtpu");
#endif

    gtpu = (__lmem struct pif_header_gtpu *) (lm_ptr + PIF_PARREP_gtpu_OFF_LW);

    mem2lmem_copy(pktdata + (pktdataoff + hdrsz),
                  lm_ptr,
                  PIF_PARREP_gtpu_OFF_LW,
                  PIF_PARREP_gtpu_LEN_LW);
    hdrsz += PIF_PARREP_gtpu_LEN_B;

#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
    {
        __lmem struct pif_global_flowkey_parse_gtpu *fk = (__lmem struct pif_global_flowkey_parse_gtpu *)fk_ptr;
        fk->gtpu__teid = gtpu->teid;
        (*fk_len) += 1;
    }
#endif
    *(pstate) = PIF_PARREP_STATE_parse_gtpu_ipv4;

    PIF_PARREP_SET_gtpu_VALID(prdata);
    PIF_PARREP_SET_gtpu_ORIG_LEN(prdata, hdrsz);

    return hdrsz;
}


static __inline __gpr int handle_node_parse_gtpu_ipv4(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktdataoff, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len, int *pstate)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    __gpr int hdrsz = 0;
    __lmem struct pif_header_gtpu_ipv4 *gtpu_ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_parrep_state_parse_gtpu_ipv4");
#endif

    gtpu_ipv4 = (__lmem struct pif_header_gtpu_ipv4 *) (lm_ptr + PIF_PARREP_gtpu_ipv4_OFF_LW);

    mem2lmem_copy(pktdata + (pktdataoff + hdrsz),
                  lm_ptr,
                  PIF_PARREP_gtpu_ipv4_OFF_LW,
                  PIF_PARREP_gtpu_ipv4_LEN_LW);
    hdrsz += PIF_PARREP_gtpu_ipv4_LEN_B;

#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
    {
        __lmem struct pif_global_flowkey_parse_gtpu_ipv4 *fk = (__lmem struct pif_global_flowkey_parse_gtpu_ipv4 *)fk_ptr;
        fk->gtpu_ipv4__dstAddr = gtpu_ipv4->dstAddr;
        fk->gtpu_ipv4__srcAddr = gtpu_ipv4->srcAddr;
        fk->gtpu_ipv4__diffserv = gtpu_ipv4->diffserv;
        fk->__padding = 0;
        (*fk_len) += 3;
    }
#endif
    *(pstate) = PIF_PARREP_STATE_fwd;

    PIF_PARREP_SET_gtpu_ipv4_VALID(prdata);
    PIF_PARREP_SET_gtpu_ipv4_ORIG_LEN(prdata, hdrsz);

    return hdrsz;
}

extern __forceinline
pif_parrep_extract(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktlen, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    PIF_PKT_INFO_TYPE struct pif_pkt_info *pkt_info = &pif_pkt_info_global;
    __gpr int exit_node = 0;
    __gpr int pif_parrep_state;
    __gpr int ret;
    __gpr int off = 0;
    int i;

    /* set state to graph entry node */
    pif_parrep_state = PIF_PARREP_STATE_start;

    /* First zero the parsed representation control data fields */
    for (i = 0; i < PIF_PARREP_CTLDATA_LEN_LW; i++)
        lm_ptr[PIF_PARREP_CTLDATA_OFF_LW + i] = 0;

    /* run through the states extracting as we go */
    while (pif_parrep_state != PIF_PARREP_STATE_DONE) {
        PIF_DEBUG_SET_STATE(PIF_DEBUG_STATE_PARSER, pif_parrep_state);
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state");
#endif
        switch (pif_parrep_state) {
        case PIF_PARREP_STATE_start:
            ret = handle_node_start(lm_ptr, pktdata, off, fk_ptr + *fk_len, fk_len, (int *) &pif_parrep_state);
            break;
        case PIF_PARREP_STATE_parse_ethernet:
            ret = handle_node_parse_ethernet(lm_ptr, pktdata, off, fk_ptr + *fk_len, fk_len, (int *) &pif_parrep_state);
            break;
        case PIF_PARREP_STATE_parse_ipv4:
            ret = handle_node_parse_ipv4(lm_ptr, pktdata, off, fk_ptr + *fk_len, fk_len, (int *) &pif_parrep_state);
            break;
        case PIF_PARREP_STATE_parse_tcp:
            ret = handle_node_parse_tcp(lm_ptr, pktdata, off, fk_ptr + *fk_len, fk_len, (int *) &pif_parrep_state);
            break;
        case PIF_PARREP_STATE_parse_udp:
            ret = handle_node_parse_udp(lm_ptr, pktdata, off, fk_ptr + *fk_len, fk_len, (int *) &pif_parrep_state);
            break;
        case PIF_PARREP_STATE_parse_gtpu:
            ret = handle_node_parse_gtpu(lm_ptr, pktdata, off, fk_ptr + *fk_len, fk_len, (int *) &pif_parrep_state);
            break;
        case PIF_PARREP_STATE_parse_gtpu_ipv4:
            ret = handle_node_parse_gtpu_ipv4(lm_ptr, pktdata, off, fk_ptr + *fk_len, fk_len, (int *) &pif_parrep_state);
            break;
        }
        if (ret < 0) {
            pkt_info->pkt_pl_off = off;
            return ret;
        }
        off += ret;
        if (off > pktlen) {
            pkt_info->pkt_pl_off = off;
            return -PIF_PARSE_ERROR_OUT_OF_PACKET;
        }
    }

#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
    {
        __lmem struct pif_header_standard_metadata *standard_metadata = (__lmem struct pif_header_standard_metadata *)(lm_ptr + PIF_PARREP_standard_metadata_OFF_LW);
        __lmem struct pif_global_flowkey_metadata *fk = (__lmem struct pif_global_flowkey_metadata *)(fk_ptr + *fk_len);
        fk->standard_metadata__ingress_port = standard_metadata->ingress_port;
        fk->__padding = 0;
        *fk_len += 1;
    }
    fk_ptr[(*fk_len) + 0] = lm_ptr[PIF_PARREP_CTLDATA_OFF_LW + 0] & 0xc9812000;
    *fk_len += PIF_PARREP_CTLDATA_LEN_LW;
#endif /* !PIF_GLOBAL_FLOWCACHE_DISABLED */

    if (off > 1023) {
        pkt_info->pkt_pl_off = off;
        return -PIF_PARSE_ERROR_HEADER_TOO_LONG;
    }

    pkt_info->pkt_pl_off = off;
    PIF_PARREP_SET_VALID(prdata);
    return exit_node;
}

extern __forceinline int
pif_parrep_exceptions(__lmem uint32_t *parrep, int result)
{
    return -1; /* no exceptions, always fail */
}
