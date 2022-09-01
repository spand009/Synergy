/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_ACTIONS_H__
#define __PIF_ACTIONS_H__

/* Warning: generated file - your edits to this file may be lost */

/* Action operation IDs */

#define PIF_ACTION_ID_forward 0
#define PIF_ACTION_ID__drop 1
#define PIF_ACTION_ID_gtpu_decap_v4 2
#define PIF_ACTION_ID_gtpu_encap_v4 3
#define PIF_ACTION_ID__nop 4
#define PIF_ACTION_ID_MAX 4

/* Match action data structure */

__packed struct pif_action_actiondata_forward {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
    uint8_t __pif_padding[2]; /* padding */
    uint16_t port;
};

__packed struct pif_action_actiondata__drop {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_gtpu_decap_v4 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_gtpu_encap_v4 {
    uint32_t srcAddr;
    uint32_t dstAddr;
    uint32_t teid;
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
    uint16_t dstPort;
    uint16_t srcPort;
    uint8_t __pif_padding; /* padding */
    uint8_t type_;
    uint16_t port;
};

__packed struct pif_action_actiondata__nop {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

#endif /* __PIF_ACTIONS_H__ */
