/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <pif_common.h>

/* Table related defines */

/* Table 0 : fwd */
#define PIF_TABLE_ACTIONDATA_SIZE_0 16
#define PIF_TABLE_MAX_ENTRIES_0 65536
#define PIF_TABLE_SHIFT_0 4

/* Table 1 : gtpu_decap_table */
#define PIF_TABLE_ACTIONDATA_SIZE_1 16
#define PIF_TABLE_MAX_ENTRIES_1 65536
#define PIF_TABLE_SHIFT_1 4

/* Table 2 : gtpu_encap_table */
#define PIF_TABLE_ACTIONDATA_SIZE_2 32
#define PIF_TABLE_MAX_ENTRIES_2 65536
#define PIF_TABLE_SHIFT_2 5

/* DCFL related table storage */
__export __emem __align256K uint32_t dcfl_ct_0[DCFL_TABLE_SIZE / 4];
__export __emem __align256K uint32_t dcfl_ct_1[DCFL_TABLE_SIZE / 4];
__export __emem __align256K uint32_t dcfl_ct_2[DCFL_TABLE_SIZE / 4];

/* PIF related table storage */
__export __emem uint32_t pif_actiondata_table_0_fwd[2 * PIF_TABLE_MAX_ENTRIES_0 * (PIF_TABLE_ACTIONDATA_SIZE_0 / 4)];
__export __emem uint32_t pif_actiondata_table_1_gtpu_decap_table[2 * PIF_TABLE_MAX_ENTRIES_1 * (PIF_TABLE_ACTIONDATA_SIZE_1 / 4)];
__export __emem uint32_t pif_actiondata_table_2_gtpu_encap_table[2 * PIF_TABLE_MAX_ENTRIES_2 * (PIF_TABLE_ACTIONDATA_SIZE_2 / 4)];

__export __emem struct pif_actiondata_table_desc pif_actiondata_table_descs[PIF_TABLE_COUNT] = {
        {
            /* .table_address = */ 0,
            /* .rule_count = */ 0,
            /* .reserved = */ 0,
            /* .record_shift = */  PIF_TABLE_SHIFT_0,
            /* .flags = */ 0,
        },
        {
            /* .table_address = */ 0,
            /* .rule_count = */ 0,
            /* .reserved = */ 0,
            /* .record_shift = */  PIF_TABLE_SHIFT_1,
            /* .flags = */ 0,
        },
        {
            /* .table_address = */ 0,
            /* .rule_count = */ 0,
            /* .reserved = */ 0,
            /* .record_shift = */  PIF_TABLE_SHIFT_2,
            /* .flags = */ 0,
        },
    };
