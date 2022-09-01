/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/me.h>
#include "pif_common.h"

/****************************************
 * ingress_flow                         *
 ****************************************/

/* State transition functions */

static int handle_ingress_flow_gtpu_decap_table(__lmem uint32_t *parrep, __mem uint32_t *actbuf, unsigned int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_gtpu_decap_table");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_gtpu_decap_table, parrep, actbuf);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow; /* always */

    if (*actlen > 0) {
        ret = pif_action_execute(parrep, actbuf, *actlen);
        if (ret < 0)
            return -1;
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_gtpu_encap_table(__lmem uint32_t *parrep, __mem uint32_t *actbuf, unsigned int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_gtpu_encap_table");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_gtpu_encap_table, parrep, actbuf);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow; /* always */

    if (*actlen > 0) {
        ret = pif_action_execute(parrep, actbuf, *actlen);
        if (ret < 0)
            return -1;
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow__condition_0(__lmem uint32_t *parrep)
{
    unsigned int pif_expression__condition_0_register_0;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_0");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_0: (ipv4.dstAddr) == (2130706433)
    {
    unsigned int pif_expression__condition_0_register_1;
    unsigned int pif_expression__condition_0_register_2;
    unsigned int pif_expression__condition_0_register_3;
    //subexpression 0: (ipv4.dstAddr)==(2130706433)
    pif_expression__condition_0_register_1 = ipv4->dstAddr;
    pif_expression__condition_0_register_2 = 0x7f000001;
    /* implicit cast 31 -> 32 */
    pif_expression__condition_0_register_3 = pif_expression__condition_0_register_2 & 0x7fffffff;
    pif_expression__condition_0_register_0 = (pif_expression__condition_0_register_1 == pif_expression__condition_0_register_3);
    }

    if (pif_expression__condition_0_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_gtpu_decap_table;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_gtpu_encap_table;
}

static int handle_ingress_flow_fwd(__lmem uint32_t *parrep, __mem uint32_t *actbuf, unsigned int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_fwd");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_fwd, parrep, actbuf);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_0; /* always */

    if (*actlen > 0) {
        ret = pif_action_execute(parrep, actbuf, *actlen);
        if (ret < 0)
            return -1;
    }

    *state = next_state;
    return 0;
}

/* Control flow entry point */

int pif_ctlflow_ingress_flow(int *start_state, __lmem uint32_t *parrep, __mem uint32_t *actbuf)
{
    __gpr unsigned int actlen, totlen = 0;
    __gpr int ret;
    int pif_ctlflow_state_ingress_flow = PIF_CTLFLOW_STATE_ingress_flow_fwd;

    while (pif_ctlflow_state_ingress_flow != PIF_CTLFLOW_STATE_ingress_flow_DONE) {
        PIF_DEBUG_SET_STATE(PIF_DEBUG_STATE_CONTROL, ((0 << 16) + pif_ctlflow_state_ingress_flow));
#ifdef PIF_DEBUG
        __debug_label("pif_ctlflow_state_ingress_flow");
#endif
        switch (pif_ctlflow_state_ingress_flow) {
        case PIF_CTLFLOW_STATE_ingress_flow_gtpu_decap_table:
            ret = handle_ingress_flow_gtpu_decap_table(parrep, actbuf + totlen, (unsigned int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_gtpu_encap_table:
            ret = handle_ingress_flow_gtpu_encap_table(parrep, actbuf + totlen, (unsigned int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_0:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_0(parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_fwd:
            ret = handle_ingress_flow_fwd(parrep, actbuf + totlen, (unsigned int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        }
        totlen += actlen;
        if (ret < 0)
            return -totlen;
    }

    return totlen;
}

/* Empty control flow */
int pif_ctlflow_egress_flow(int *start_state, __lmem uint32_t *parrep, __mem uint32_t *actbuf)
{
    return 0;
}
