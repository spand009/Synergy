/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_CTLFLOW_H__
#define __PIF_CTLFLOW_H__

/* Defines for checking flow presence */
#define PIF_CTLFLOW_HAS_ingress_flow

/* Control state nodes for ingress_flow */
#define PIF_CTLFLOW_STATE_ingress_flow_DONE -1
#define PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow -1
#define PIF_CTLFLOW_STATE_ingress_flow 0

#define PIF_CTLFLOW_STATE_ingress_flow_gtpu_decap_table 0
#define PIF_CTLFLOW_STATE_ingress_flow_gtpu_encap_table 1
#define PIF_CTLFLOW_STATE_ingress_flow__condition_0 2
#define PIF_CTLFLOW_STATE_ingress_flow_fwd 3

/* Unified control state numbers */
#define PIF_CTLFLOW_STATE_gtpu_decap_table 0
#define PIF_CTLFLOW_STATE_gtpu_encap_table 1
#define PIF_CTLFLOW_STATE__condition_0 2
#define PIF_CTLFLOW_STATE_fwd 3

/* Control flow entry points  */
int pif_ctlflow_ingress_flow(int *start_state, __lmem uint32_t *parrep, __mem uint32_t *actbuf);
int pif_ctlflow_egress_flow(int *start_state, __lmem uint32_t *parrep, __mem uint32_t *actbuf);

#endif /* __PIF_CTLFLOW_H__ */
