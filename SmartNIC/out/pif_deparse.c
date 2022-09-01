/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp.h>
#include <nfp/me.h>
#include <pkt/pkt.h>
#include <pif_counters.h>
#ifdef PIF_USE_GRO
#include <gro.h>
#endif
#include "nfd_user_cfg.h"
#include "pif_common.h"
#include "pif_pkt_mod_script.h"

__forceinline static int handle_tier_1(__lmem uint32_t *parrep, PIF_PKT_INFO_TYPE struct pif_pkt_info *pktinfo, int *pkt_byteoff, uint32_t pkt_min_off)
{
    __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
    uint32_t orig_len = PIF_PARREP_T1_ORIG_LEN(ctldata);
    uint32_t curr_len = 0;

    if (!PIF_PARREP_T1_DIRTY(ctldata)) {
        *pkt_byteoff -= orig_len;
        if (*pkt_byteoff < 0)
            return -1;

        return 0;
    }

    if (PIF_PARREP_T1_VALID(ctldata)) {
        curr_len = PIF_PARREP_ethernet_LEN_B;
    }

    if (curr_len) {
        *pkt_byteoff -= curr_len;
        if (*pkt_byteoff < 0)
            return -1;

        pif_pkt_write_header(*pkt_byteoff,
                             parrep,
                             PIF_PARREP_T1_OFF_LW,
                             curr_len);
    }

    return 0;
}

__forceinline static int handle_tier_2(__lmem uint32_t *parrep, PIF_PKT_INFO_TYPE struct pif_pkt_info *pktinfo, int *pkt_byteoff, uint32_t pkt_min_off)
{
    __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
    uint32_t orig_len = PIF_PARREP_T2_ORIG_LEN(ctldata);
    uint32_t curr_len = 0;

    if (!PIF_PARREP_T2_DIRTY(ctldata)) {
        *pkt_byteoff -= orig_len;
        if (*pkt_byteoff < 0)
            return -1;

        return 0;
    }

    if (PIF_PARREP_T2_VALID(ctldata)) {
        curr_len = PIF_PARREP_ipv4_LEN_B;
    }

    if (curr_len) {
        *pkt_byteoff -= curr_len;
        if (*pkt_byteoff < 0)
            return -1;

        pif_pkt_write_header(*pkt_byteoff,
                             parrep,
                             PIF_PARREP_T2_OFF_LW,
                             curr_len);
    }

    return 0;
}

__forceinline static int handle_tier_3(__lmem uint32_t *parrep, PIF_PKT_INFO_TYPE struct pif_pkt_info *pktinfo, int *pkt_byteoff, uint32_t pkt_min_off)
{
    __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
    uint32_t orig_len = PIF_PARREP_T3_ORIG_LEN(ctldata);
    uint32_t curr_len = 0;

    if (!PIF_PARREP_T3_DIRTY(ctldata)) {
        *pkt_byteoff -= orig_len;
        if (*pkt_byteoff < 0)
            return -1;

        return 0;
    }

    if (PIF_PARREP_T3_VALID(ctldata)) {
        switch (PIF_PARREP_T3_TYPE(ctldata)) {
            case PIF_PARREP_TYPE_parse_tcp: {
                curr_len = PIF_PARREP_tcp_LEN_B;
                break;
            }
            case PIF_PARREP_TYPE_parse_udp: {
                curr_len = PIF_PARREP_udp_LEN_B;
                break;
            }
        }
    }

    if (curr_len < orig_len) {
        unsigned int delta = orig_len - curr_len;

        /*
         * Remove header space ending at *pkt_byteoff of length 'delta'.
         * Adjust pkt_byteoff to make provision for change in pkt_buf (buffer pointer)
         * because pkt_byteoff is relative to start of pkt_buf
         */
        *pkt_byteoff -= delta;
        if (*pkt_byteoff < 0)
            return -1;

        pif_pkt_remove_header(*pkt_byteoff, delta);

        pktinfo->pkt_pl_off -= delta;
    } else if (curr_len > orig_len) {
        unsigned int delta = curr_len - orig_len;
        unsigned int num_bytes;
        int space_needed;

        num_bytes = PIF_PKT_SOP(pktinfo->pkt_buf, pktinfo->pkt_num);
        space_needed = pkt_min_off + delta;
        /*
         * Insert header space of length 'delta' up to current *pkt_byteoff.
         * Then increase *pkt_byteoff to make provision for change in pkt_buf (buffer pointer)
         * because pkt_byteoff is relative to start of pkt_buf
         */
        if (num_bytes >= space_needed) {
            pif_pkt_insert_header(*pkt_byteoff, delta);
        } else {
            pif_pkt_make_space(*pkt_byteoff, delta);
        }

        *pkt_byteoff += delta;
        pktinfo->pkt_pl_off += delta;
    }

    if (curr_len) {
        *pkt_byteoff -= curr_len;
        if (*pkt_byteoff < 0)
            return -1;

        pif_pkt_write_header(*pkt_byteoff,
                             parrep,
                             PIF_PARREP_T3_OFF_LW,
                             curr_len);
    }

    return 0;
}

__forceinline static int handle_tier_4(__lmem uint32_t *parrep, PIF_PKT_INFO_TYPE struct pif_pkt_info *pktinfo, int *pkt_byteoff, uint32_t pkt_min_off)
{
    __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
    uint32_t orig_len = PIF_PARREP_T4_ORIG_LEN(ctldata);
    uint32_t curr_len = 0;

    if (!PIF_PARREP_T4_DIRTY(ctldata)) {
        *pkt_byteoff -= orig_len;
        if (*pkt_byteoff < 0)
            return -1;

        return 0;
    }

    if (PIF_PARREP_T4_VALID(ctldata)) {
        curr_len = PIF_PARREP_gtpu_LEN_B;
    }

    if (curr_len < orig_len) {
        unsigned int delta = orig_len - curr_len;

        /*
         * Remove header space ending at *pkt_byteoff of length 'delta'.
         * Adjust pkt_byteoff to make provision for change in pkt_buf (buffer pointer)
         * because pkt_byteoff is relative to start of pkt_buf
         */
        *pkt_byteoff -= delta;
        if (*pkt_byteoff < 0)
            return -1;

        pif_pkt_remove_header(*pkt_byteoff, delta);

        pktinfo->pkt_pl_off -= delta;
    } else if (curr_len > orig_len) {
        unsigned int delta = curr_len - orig_len;
        unsigned int num_bytes;
        int space_needed;

        num_bytes = PIF_PKT_SOP(pktinfo->pkt_buf, pktinfo->pkt_num);
        space_needed = pkt_min_off + delta;
        /*
         * Insert header space of length 'delta' up to current *pkt_byteoff.
         * Then increase *pkt_byteoff to make provision for change in pkt_buf (buffer pointer)
         * because pkt_byteoff is relative to start of pkt_buf
         */
        if (num_bytes >= space_needed) {
            pif_pkt_insert_header(*pkt_byteoff, delta);
        } else {
            pif_pkt_make_space(*pkt_byteoff, delta);
        }

        *pkt_byteoff += delta;
        pktinfo->pkt_pl_off += delta;
    }

    if (curr_len) {
        *pkt_byteoff -= curr_len;
        if (*pkt_byteoff < 0)
            return -1;

        pif_pkt_write_header(*pkt_byteoff,
                             parrep,
                             PIF_PARREP_T4_OFF_LW,
                             curr_len);
    }

    return 0;
}

__forceinline static int handle_tier_5(__lmem uint32_t *parrep, PIF_PKT_INFO_TYPE struct pif_pkt_info *pktinfo, int *pkt_byteoff, uint32_t pkt_min_off)
{
    __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
    uint32_t orig_len = PIF_PARREP_T5_ORIG_LEN(ctldata);
    uint32_t curr_len = 0;

    if (!PIF_PARREP_T5_DIRTY(ctldata)) {
        *pkt_byteoff -= orig_len;
        if (*pkt_byteoff < 0)
            return -1;

        return 0;
    }

    if (PIF_PARREP_T5_VALID(ctldata)) {
        curr_len = PIF_PARREP_gtpu_ipv4_LEN_B;
    }

    if (curr_len < orig_len) {
        unsigned int delta = orig_len - curr_len;

        /*
         * Remove header space ending at *pkt_byteoff of length 'delta'.
         * Adjust pkt_byteoff to make provision for change in pkt_buf (buffer pointer)
         * because pkt_byteoff is relative to start of pkt_buf
         */
        *pkt_byteoff -= delta;
        if (*pkt_byteoff < 0)
            return -1;

        pif_pkt_remove_header(*pkt_byteoff, delta);

        pktinfo->pkt_pl_off -= delta;
    } else if (curr_len > orig_len) {
        unsigned int delta = curr_len - orig_len;
        unsigned int num_bytes;
        int space_needed;

        num_bytes = PIF_PKT_SOP(pktinfo->pkt_buf, pktinfo->pkt_num);
        space_needed = pkt_min_off + delta;
        /*
         * Insert header space of length 'delta' up to current *pkt_byteoff.
         * Then increase *pkt_byteoff to make provision for change in pkt_buf (buffer pointer)
         * because pkt_byteoff is relative to start of pkt_buf
         */
        if (num_bytes >= space_needed) {
            pif_pkt_insert_header(*pkt_byteoff, delta);
        } else {
            pif_pkt_make_space(*pkt_byteoff, delta);
        }

        *pkt_byteoff += delta;
        pktinfo->pkt_pl_off += delta;
    }

    if (curr_len) {
        *pkt_byteoff -= curr_len;
        if (*pkt_byteoff < 0)
            return -1;

        pif_pkt_write_header(*pkt_byteoff,
                             parrep,
                             PIF_PARREP_T5_OFF_LW,
                             curr_len);
    }

    return 0;
}

__forceinline extern int pif_deparse(__lmem uint32_t *parrep, PIF_PKT_INFO_TYPE struct pif_pkt_info *pktinfo)
{
    __gpr uint32_t pkt_byteoff = pktinfo->pkt_pl_off;
    __gpr uint32_t pkt_min_off;

    /* Packet minimum offset depends on packet destination - NBI/PCIe */
    pkt_min_off = PIF_PKT_MIN_NBI_TX_OFFSET; /* apply the nbi min to nfd too */
    if (handle_tier_5(parrep, pktinfo, (uint32_t *)&pkt_byteoff, pkt_min_off) < 0)
        return -1;
    if (handle_tier_4(parrep, pktinfo, (uint32_t *)&pkt_byteoff, pkt_min_off) < 0)
        return -1;
    if (handle_tier_3(parrep, pktinfo, (uint32_t *)&pkt_byteoff, pkt_min_off) < 0)
        return -1;
    if (handle_tier_2(parrep, pktinfo, (uint32_t *)&pkt_byteoff, pkt_min_off) < 0)
        return -1;
    if (handle_tier_1(parrep, pktinfo, (uint32_t *)&pkt_byteoff, pkt_min_off) < 0)
        return -1;

    pkt_byteoff = PIF_PKT_SOP(pktinfo->pkt_buf, pktinfo->pkt_num);

    /* If packet offset more than maximum allowed for NBI, return error */
    if (pif_pkt_info_global.eg_port.type == PIF_PKT_SRC_NBI) {
        if (pkt_byteoff > PIF_PKT_MAX_NBI_TX_OFFSET) {
            uint32_t move_len = pkt_byteoff - PIF_PKT_MAX_NBI_TX_OFFSET;
            pif_pkt_move_pkt_up(move_len);
            pkt_byteoff -= move_len;
            pktinfo->pkt_pl_off -= move_len;
            PIF_COUNT(OFFSET_TOO_LARGE_SHIFT);

        }
    } else {
#ifdef PIF_USE_GRO
        if (pkt_byteoff > GRO_NFD_MAX_OFFSET) {
            uint32_t move_len = pkt_byteoff - GRO_NFD_MAX_OFFSET;
            pif_pkt_move_pkt_up(move_len);
            pkt_byteoff -= move_len;
            pktinfo->pkt_pl_off -= move_len;
            PIF_COUNT(OFFSET_TOO_LARGE_SHIFT);

        }
#endif
    }
    if (pif_pkt_info_global.trunc_len != 0 && pif_pkt_info_global.trunc_len < pif_pkt_info_global.pkt_len)
        pif_pkt_info_global.pkt_len = pif_pkt_info_global.trunc_len;

    return pkt_byteoff;
}
