/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/mem_atomic.h>
#include <nfp/mem_ring.h>
#include <nfp/me.h>
#include <nfp/cls.h>
#include "pif_common.h"
#include "pkt_clone.h"

#ifdef PIF_DEBUG
    __export __emem_n(0) uint64_t pif_act_stats[PIF_ACTION_ID_MAX + 1];
#endif

#define BITRANGE(var, width, offset) \
    (((var) >> (offset)) & ((1 << (width)) - 1))


static int pif_action_exec_forward(__lmem uint32_t *parrep, __xread uint32_t *actdatabuf, unsigned debug)
{
    __xread struct pif_action_actiondata_forward *_actdata = (__xread struct pif_action_actiondata_forward *)actdatabuf;
    __lmem struct pif_header_standard_metadata *standard_metadata;

#ifdef PIF_DEBUG
    if (debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _actdata->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _actdata->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_forward");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_forward");
#endif
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (parrep + PIF_PARREP_standard_metadata_OFF_LW);

    /* modify_field(standard_metadata.egress_spec,port) */
    standard_metadata->egress_spec = _actdata->port;

    return 0;
}

static int pif_action_exec__drop(__lmem uint32_t *parrep, __xread uint32_t *actdatabuf, unsigned debug)
{
    __xread struct pif_action_actiondata__drop *_actdata = (__xread struct pif_action_actiondata__drop *)actdatabuf;

#ifdef PIF_DEBUG
    if (debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _actdata->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _actdata->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit__drop");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state__drop");
#endif
    return 1;
}

static int pif_action_exec_gtpu_decap_v4(__lmem uint32_t *parrep, __xread uint32_t *actdatabuf, unsigned debug)
{
    __xread struct pif_action_actiondata_gtpu_decap_v4 *_actdata = (__xread struct pif_action_actiondata_gtpu_decap_v4 *)actdatabuf;
    __lmem struct pif_header_gtpu_ipv4 *gtpu_ipv4;
    __lmem struct pif_header_gtpu *gtpu;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_udp *udp;
    __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);

#ifdef PIF_DEBUG
    if (debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _actdata->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _actdata->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_gtpu_decap_v4");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_gtpu_decap_v4");
#endif
    gtpu_ipv4 = (__lmem struct pif_header_gtpu_ipv4 *) (parrep + PIF_PARREP_gtpu_ipv4_OFF_LW);
    gtpu = (__lmem struct pif_header_gtpu *) (parrep + PIF_PARREP_gtpu_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (parrep + PIF_PARREP_ipv4_OFF_LW);
    udp = (__lmem struct pif_header_udp *) (parrep + PIF_PARREP_udp_OFF_LW);

    /* copy_header(ipv4,gtpu_ipv4) */
    {
        int i;
        for (i = 0; i < PIF_PARREP_ipv4_LEN_LW; i++)
            ((__lmem uint32_t *)ipv4)[i] = ((__lmem uint32_t *)gtpu_ipv4)[i];
    }
    /* remove_header(udp) */
    {
        volatile __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
        PIF_PARREP_CLEAR_udp_VALID(ctldata);
    }
    /* remove_header(gtpu) */
    {
        volatile __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
        PIF_PARREP_CLEAR_gtpu_VALID(ctldata);
    }
    /* remove_header(gtpu_ipv4) */
    {
        volatile __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
        PIF_PARREP_CLEAR_gtpu_ipv4_VALID(ctldata);
    }
    PIF_PARREP_SET_udp_DIRTY(ctldata);

    PIF_PARREP_SET_gtpu_DIRTY(ctldata);

    PIF_PARREP_SET_gtpu_ipv4_DIRTY(ctldata);

    PIF_PARREP_SET_ipv4_DIRTY(ctldata);

    return 0;
}

static int pif_action_exec_gtpu_encap_v4(__lmem uint32_t *parrep, __xread uint32_t *actdatabuf, unsigned debug)
{
    __xread struct pif_action_actiondata_gtpu_encap_v4 *_actdata = (__xread struct pif_action_actiondata_gtpu_encap_v4 *)actdatabuf;
    __lmem struct pif_header_gtpu_ipv4 *gtpu_ipv4;
    __lmem struct pif_header_gtpu *gtpu;
    __lmem struct pif_header_ipv4 *ipv4;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_udp *udp;
    __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
    unsigned int pif_expression__expression_gtpu_encap_v4_0_register_0;

#ifdef PIF_DEBUG
    if (debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _actdata->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _actdata->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit_gtpu_encap_v4");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state_gtpu_encap_v4");
#endif
    gtpu_ipv4 = (__lmem struct pif_header_gtpu_ipv4 *) (parrep + PIF_PARREP_gtpu_ipv4_OFF_LW);
    gtpu = (__lmem struct pif_header_gtpu *) (parrep + PIF_PARREP_gtpu_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (parrep + PIF_PARREP_ipv4_OFF_LW);
    standard_metadata = (__lmem struct pif_header_standard_metadata *) (parrep + PIF_PARREP_standard_metadata_OFF_LW);
    udp = (__lmem struct pif_header_udp *) (parrep + PIF_PARREP_udp_OFF_LW);

    /* add_header(udp) */
    {
        volatile __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
        PIF_PARREP_SET_udp_VALID(ctldata);
    }
    /* add_header(gtpu) */
    {
        volatile __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
        PIF_PARREP_SET_gtpu_VALID(ctldata);
    }
    /* add_header(gtpu_ipv4) */
    {
        volatile __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
        PIF_PARREP_SET_gtpu_ipv4_VALID(ctldata);
    }
    /* copy_header(gtpu_ipv4,ipv4) */
    {
        int i;
        for (i = 0; i < PIF_PARREP_gtpu_ipv4_LEN_LW; i++)
            ((__lmem uint32_t *)gtpu_ipv4)[i] = ((__lmem uint32_t *)ipv4)[i];
    }
    /* modify_field(ipv4.protocol,0x11) */
    ipv4->protocol = 0x11;

    /* modify_field(ipv4.srcAddr,srcAddr) */
    ipv4->srcAddr = _actdata->srcAddr;

    /* modify_field(ipv4.dstAddr,dstAddr) */
    ipv4->dstAddr = _actdata->dstAddr;

    /* modify_field(udp.srcPort,srcPort) */
    udp->srcPort = _actdata->srcPort;

    /* modify_field(udp.dstPort,dstPort) */
    udp->dstPort = _actdata->dstPort;

    /* modify_field(gtpu.flags,0x30) */
    gtpu->flags = 0x30;

    /* modify_field(gtpu.type_,type_) */
    gtpu->type_ = _actdata->type_;

    /* modify_field(gtpu.length_,_expression_gtpu_encap_v4_0) */
    //expression _expression_gtpu_encap_v4_0: (udp.length_) - (16)
    {
    unsigned int pif_expression__expression_gtpu_encap_v4_0_register_1;
    unsigned int pif_expression__expression_gtpu_encap_v4_0_register_2;
    //subexpression 0: (udp.length_)-(16)
    pif_expression__expression_gtpu_encap_v4_0_register_1 = udp->length_;
    pif_expression__expression_gtpu_encap_v4_0_register_2 = 0x10;
    pif_expression__expression_gtpu_encap_v4_0_register_0 = pif_expression__expression_gtpu_encap_v4_0_register_1 - pif_expression__expression_gtpu_encap_v4_0_register_2;
    pif_expression__expression_gtpu_encap_v4_0_register_0 &= 0xffff;
    }
    gtpu->length_ = pif_expression__expression_gtpu_encap_v4_0_register_0;

    /* modify_field(gtpu.teid,teid) */
    gtpu->teid = _actdata->teid;

    /* modify_field(standard_metadata.egress_spec,port) */
    standard_metadata->egress_spec = _actdata->port;

    PIF_PARREP_SET_udp_DIRTY(ctldata);

    PIF_PARREP_SET_gtpu_DIRTY(ctldata);

    PIF_PARREP_SET_gtpu_ipv4_DIRTY(ctldata);

    PIF_PARREP_SET_ipv4_DIRTY(ctldata);

    return 0;
}

static int pif_action_exec__nop(__lmem uint32_t *parrep, __xread uint32_t *actdatabuf, unsigned debug)
{
    __xread struct pif_action_actiondata__nop *_actdata = (__xread struct pif_action_actiondata__nop *)actdatabuf;

#ifdef PIF_DEBUG
    if (debug & PIF_ACTION_OPDATA_DBGFLAG_BREAK) {
        /* copy the table number and rule number into mailboxes */
        unsigned int temp0, temp1;
        temp0 = local_csr_read(local_csr_mailbox_2);
        temp1 = local_csr_read(local_csr_mailbox_3);
        local_csr_write(local_csr_mailbox_2, _actdata->__pif_rule_no);
        local_csr_write(local_csr_mailbox_3, _actdata->__pif_table_no);
#if SIMULATION == 1
        __asm { /* add nops so mailboxes have time to propagate */
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        nop;
        }
#endif
        __debug_label("pif_table_hit__nop");
        local_csr_write(local_csr_mailbox_2, temp0);
        local_csr_write(local_csr_mailbox_3, temp1);
    }
#endif
#ifdef PIF_DEBUG
    __debug_label("pif_action_state__nop");
#endif
    return 0;
}

extern __forceinline int pif_action_exec_op(__lmem uint32_t *parrep, __xread uint32_t *_actdata)
{
    __xread union pif_action_opdata *opdata = (__xread union pif_action_opdata *) _actdata;
    int ret = -1;

    if (opdata->action_id > PIF_ACTION_ID_MAX) {
        /* FIXME: TODO: account for bad action id */
        return -1;
    }

    PIF_DEBUG_SET_STATE(PIF_DEBUG_STATE_ACTION, opdata->action_id);
    switch (opdata->action_id) {
    case PIF_ACTION_ID_forward:
        ret = pif_action_exec_forward(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID__drop:
        ret = pif_action_exec__drop(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_gtpu_decap_v4:
        ret = pif_action_exec_gtpu_decap_v4(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID_gtpu_encap_v4:
        ret = pif_action_exec_gtpu_encap_v4(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    case PIF_ACTION_ID__nop:
        ret = pif_action_exec__nop(parrep, _actdata + PIF_ACTION_OPDATA_LW, opdata->dbg_flags);
        break;
    }
#ifdef PIF_DEBUG
        mem_incr64((__mem uint64_t *)(pif_act_stats + opdata->action_id));
#endif

    return ret;
}
