/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PKT_MOD_SCRIPT_H__
#define __PIF_PKT_MOD_SCRIPT_H__
#include <nfp.h>

/* Generated C source defining pkt_modifier script related bits and bobs  */
/* Warning: your edits to this file may be lost */

/* This is the minimum allowable offset for packet to start (pkt_offset). */
#define PIF_PKT_MIN_NBI_TX_OFFSET  40

/* This is the maximum allowable offset for packet to start (pkt_offset). */
#define PIF_PKT_MAX_NBI_TX_OFFSET  248

typedef union packet_modifier_struct_t
{
    struct
    {
        /*
        * First longword
        */
            uint32_t direct             : 1;
            uint32_t unused             : 4;
            uint32_t offset_len         : 3;
            uint32_t opcode_index       : 8;
            uint32_t rdata_index        : 8;
            uint32_t rdata_location     : 2;
            uint32_t rdata_length       : 6;

            /*
            * Second longword
            */
            uint32_t offset_0           : 8;
            uint32_t offset_1           : 8;
            uint32_t offset_2           : 8;
            uint32_t offset_3           : 8;

            /*
             * Third longword
            */
            uint32_t offset_4           : 8;
            uint32_t offset_5           : 8;
            uint32_t offset_6           : 8;
            uint32_t offset_7           : 8;

            /*
             * Fourth longword
             */
            uint32_t valid              : 1;
            uint32_t reserved           : 20;
            uint32_t prepend_len0       : 3;
            uint32_t prepend_offset     : 8;
        };
    uint32_t value[4];
} packet_modifier_struct_t;

__intrinsic struct pkt_ms_info pif_pkt_msd_write(__addr40 void *pbuf, unsigned char off);
#endif /* __PIF_PKT_MOD_SCRIPT_H__ */
