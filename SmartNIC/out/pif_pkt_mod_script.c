/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <stdint.h>
#include <nfp.h>
#include <nfp/me.h>
#include <nfp/cls.h>
#include <pkt/pkt.h>
#include <std/reg_utils.h>
#include <nfp/mem_bulk.h>
#include "pif_pkt_mod_script.h"

/* Generated C source defining pkt_modifier_script related bits and bobs  */
/* Warning: your edits to this file may be lost */

#if (__REVISION_MIN < __REVISION_B0) 
    #error "Unsupported chip revision"
#elif (__REVISION_MIN < __REVISION_C0) 
    /* supported */
#else
    #error "Unsupported chip revision"
#endif


#define PKT_MOD_SCRIPT_ENTRIES     209
    /*
    * Packet modifier CSRs are configured using the supported script offsets and the valid packet offsets.
    * The number of delete opcodes plus padding and/or NOPs are configured in the CSRs. 
    * A table in CLS is used to lookup the applicable indirect script values.
    * This table is indexed on the packet offset (minus the minimum packet offset), and contains:
    * - the packet modifier script which is either two or four words in length (CSR idx and offsets - see packet_modifier_struct_t)
    * - the offset in the packet at which the script should be written
    * - the length to use when writing to the packet (two or four words)
    *
    * Short packet padding up to 60B is configured.
    *
    * The supported script offsets (B0) plus valid packet offsets are listed in table below:
    *
    * Script Offset     Packet Offsets
    * --------------    --------------
    * 3=32              40, 41, .. 46
    * 4=40              48, 49, .. 54
    * 5=48              56, 57, .. 62
    * 6=56              64, 65, .. 70, .. 102
    * 11=96             104, 105, .. 110
    * 12=104            112, 113, .. 118
    * 13=112            120, 121, .. 126
    * 14=120            128, 129, .. 137, 138 .. 248
    */

#ifdef MASTERME
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 0xe1e1c10f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 0xe1e1c10f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 0xe1e1c111 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 0xe1e1c111 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 0xe1e1c113 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 0xe1e1c113 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 0xe1e1c115 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 0xe1e1c115 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 0xe1e1c117 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 0xe1e1c117 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 0xe1e1c119 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 0xe1e1c119 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 0xe1e1c11b 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 0xe1e1c11b 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 0xe1e1c11d 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 0xe1e1c11d 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 0xe1e1c11f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 0xe1e1c11f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 0xe1c1011f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 0xe1c1011f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 0xe1c1031f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 0xe1c1031f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 0xe1c1051f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 0xe1c1051f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 0xe1c1071f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 0xe1c1071f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 0xe1c1091f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 0xe1c1091f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 0xe1c10b1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 0xe1c10b1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 0xe1c10d1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 0xe1c10d1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 0xe1c10f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 0xe1c10f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 0xe1c1111f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 0xe1c1111f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 0xe1c1131f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 0xe1c1131f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 0xe1c1151f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 0xe1c1151f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 0xe1c1171f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 0xe1c1171f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 0xe1c1191f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 0xe1c1191f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 0xe1c11b1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 0xe1c11b1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 0xe1c11d1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 0xe1c11d1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 0xe1c11f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 0xe1c11f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 0xc1011f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 0xc1011f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 0xc1031f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 0xc1031f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 0xc1051f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 0xc1051f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 0xc1071f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 0xc1071f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 0xc1091f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 0xc1091f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 0xc10b1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 0xc10b1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 0xc10d1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 0xc10d1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 0xe1e1e1c1 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 0xe1e1c101 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 0xe1e1c103 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 0xe1e1c105 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 0xe1e1c107 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 0xe1e1c109 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 0xe1e1c10b 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 0xe1e1c10d 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 0xe1e1c10f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 0xe1e1c10f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 0xe1e1c111 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 0xe1e1c111 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 0xe1e1c113 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 0xe1e1c113 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 0xe1e1c115 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 0xe1e1c115 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 0xe1e1c117 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 0xe1e1c117 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 0xe1e1c119 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 0xe1e1c119 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 0xe1e1c11b 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 0xe1e1c11b 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 0xe1e1c11d 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 0xe1e1c11d 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 0xe1e1c11f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 0xe1e1c11f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 0xe1c1011f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 0xe1c1011f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 0xe1c1031f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 0xe1c1031f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 0xe1c1051f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 0xe1c1051f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 0xe1c1071f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 0xe1c1071f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 0xe1c1091f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 0xe1c1091f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 0xe1c10b1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 0xe1c10b1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 0xe1c10d1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 0xe1c10d1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 0xe1c10f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 0xe1c10f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 0xe1c1111f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 0xe1c1111f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 0xe1c1131f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 0xe1c1131f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 0xe1c1151f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 0xe1c1151f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 0xe1c1171f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 0xe1c1171f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 0xe1c1191f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 0xe1c1191f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 0xe1c11b1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 0xe1c11b1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 0xe1c11d1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 0xe1c11d1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 0xe1c11f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 0xe1c11f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 0xc1011f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 0xc1011f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 0xc1031f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 0xc1031f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 0xc1051f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 0xc1051f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 0xc1071f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 0xc1071f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 0xc1091f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 0xc1091f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 0xc10b1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 0xc10b1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 0xc10d1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 0xc10d1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_48 0xc10f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_48 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_48 0xc10f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_48 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_49 0xc1111f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_49 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_49 0xc1111f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_49 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_50 0xc1131f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_50 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_50 0xc1131f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_50 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_51 0xc1151f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_51 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_51 0xc1151f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_51 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_52 0xc1171f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_52 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_52 0xc1171f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_52 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_53 0xc1191f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_53 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_53 0xc1191f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_53 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_54 0xc11b1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_54 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_54 0xc11b1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_54 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_55 0xc11d1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_55 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_55 0xc11d1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_55 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_56 0xc11f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_56 0xe1e1e1e1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_56 0xc11f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_56 0xe1e1e1e1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_57 0x111f0f0f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_57 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_57 0x111f0f0f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_57 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_58 0x131f0f0f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_58 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_58 0x131f0f0f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_58 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_59 0x151f0f0f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_59 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_59 0x151f0f0f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_59 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_60 0x171f0f0f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_60 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_60 0x171f0f0f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_60 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_61 0x191f0f0f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_61 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_61 0x191f0f0f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_61 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_62 0x1b1f0f0f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_62 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_62 0x1b1f0f0f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_62 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_63 0x1d1f0f0f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_63 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_63 0x1d1f0f0f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_63 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_64 0x1f1f0f0f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_64 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_64 0x1f1f0f0f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_64 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_65 0x11f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_65 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_65 0x11f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_65 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_66 0x31f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_66 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_66 0x31f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_66 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_67 0x51f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_67 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_67 0x51f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_67 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_68 0x71f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_68 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_68 0x71f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_68 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_69 0x91f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_69 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_69 0x91f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_69 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_70 0xb1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_70 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_70 0xb1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_70 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_71 0xd1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_71 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_71 0xd1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_71 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_72 0xf1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_72 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_72 0xf1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_72 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_73 0x111f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_73 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_73 0x111f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_73 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_74 0x131f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_74 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_74 0x131f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_74 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_75 0x151f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_75 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_75 0x151f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_75 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_76 0x171f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_76 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_76 0x171f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_76 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_77 0x191f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_77 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_77 0x191f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_77 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_78 0x1b1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_78 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_78 0x1b1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_78 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_79 0x1d1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_79 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_79 0x1d1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_79 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_80 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_80 0xe1e1e1c1 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_80 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_80 0xe1e1e1c1 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_81 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_81 0xe1e1c101 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_81 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_81 0xe1e1c101 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_82 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_82 0xe1e1c103 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_82 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_82 0xe1e1c103 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_83 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_83 0xe1e1c105 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_83 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_83 0xe1e1c105 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_84 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_84 0xe1e1c107 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_84 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_84 0xe1e1c107 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_85 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_85 0xe1e1c109 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_85 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_85 0xe1e1c109 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_86 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_86 0xe1e1c10b 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_86 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_86 0xe1e1c10b 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_87 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_87 0xe1e1c10d 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_87 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_87 0xe1e1c10d 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_88 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_88 0xe1e1c10f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_88 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_88 0xe1e1c10f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_89 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_89 0xe1e1c111 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_89 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_89 0xe1e1c111 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_90 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_90 0xe1e1c113 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_90 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_90 0xe1e1c113 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_91 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_91 0xe1e1c115 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_91 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_91 0xe1e1c115 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_92 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_92 0xe1e1c117 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_92 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_92 0xe1e1c117 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_93 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_93 0xe1e1c119 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_93 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_93 0xe1e1c119 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_94 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_94 0xe1e1c11b 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_94 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_94 0xe1e1c11b 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_95 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_95 0xe1e1c11d 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_95 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_95 0xe1e1c11d 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_96 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_96 0xe1e1c11f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_96 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_96 0xe1e1c11f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_97 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_97 0xe1c1011f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_97 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_97 0xe1c1011f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_98 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_98 0xe1c1031f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_98 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_98 0xe1c1031f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_99 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_99 0xe1c1051f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_99 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_99 0xe1c1051f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_100 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_100 0xe1c1071f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_100 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_100 0xe1c1071f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_101 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_101 0xe1c1091f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_101 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_101 0xe1c1091f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_102 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_102 0xe1c10b1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_102 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_102 0xe1c10b1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_103 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_103 0xe1c10d1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_103 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_103 0xe1c10d1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_104 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_104 0xe1c10f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_104 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_104 0xe1c10f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_105 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_105 0xe1c1111f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_105 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_105 0xe1c1111f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_106 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_106 0xe1c1131f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_106 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_106 0xe1c1131f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_107 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_107 0xe1c1151f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_107 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_107 0xe1c1151f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_108 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_108 0xe1c1171f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_108 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_108 0xe1c1171f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_109 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_109 0xe1c1191f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_109 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_109 0xe1c1191f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_110 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_110 0xe1c11b1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_110 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_110 0xe1c11b1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_111 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_111 0xe1c11d1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_111 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_111 0xe1c11d1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_112 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_112 0xe1c11f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_112 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_112 0xe1c11f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_113 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_113 0xc1011f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_113 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_113 0xc1011f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_114 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_114 0xc1031f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_114 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_114 0xc1031f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_115 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_115 0xc1051f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_115 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_115 0xc1051f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_116 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_116 0xc1071f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_116 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_116 0xc1071f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_117 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_117 0xc1091f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_117 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_117 0xc1091f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_118 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_118 0xc10b1f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_118 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_118 0xc10b1f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_119 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_119 0xc10d1f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_119 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_119 0xc10d1f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_120 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_120 0xc10f1f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_120 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_120 0xc10f1f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_121 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_121 0xc1111f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_121 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_121 0xc1111f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_122 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_122 0xc1131f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_122 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_122 0xc1131f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_123 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_123 0xc1151f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_123 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_123 0xc1151f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_124 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_124 0xc1171f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_124 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_124 0xc1171f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_125 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_125 0xc1191f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_125 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_125 0xc1191f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_126 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_126 0xc11b1f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_126 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_126 0xc11b1f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_127 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_127 0xc11d1f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_127 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_127 0xc11d1f1f 
    #endif
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_128 0x1f1f1f1f 
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_128 0xc11f1f1f 
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_128 0x1f1f1f1f 
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_128 0xc11f1f1f 
    #endif
#endif


__cls __addr32 __export __shared __declspec(scope(island)) uint32_t pkt_mod_script_tbl[PKT_MOD_SCRIPT_ENTRIES][sizeof(packet_modifier_struct_t)>>2] = { 
    {0x80040, 0x0, 0x0, 0x80000220 }, 
    {0x1090040, 0x10000, 0x0, 0x80000220 }, 
    {0x10a0040, 0x20000, 0x0, 0x80000220 }, 
    {0x10b0040, 0x30000, 0x0, 0x80000220 }, 
    {0x10c0040, 0x40000, 0x0, 0x80000220 }, 
    {0x10d0040, 0x50000, 0x0, 0x80000220 }, 
    {0x10e0040, 0x60000, 0x0, 0x80000220 }, 
    {0x10f0040, 0x70000, 0x0, 0x80000220 }, 
    {0x80040, 0x0, 0x0, 0x80000228 }, 
    {0x1090040, 0x10000, 0x0, 0x80000228 }, 
    {0x10a0040, 0x20000, 0x0, 0x80000228 }, 
    {0x10b0040, 0x30000, 0x0, 0x80000228 }, 
    {0x10c0040, 0x40000, 0x0, 0x80000228 }, 
    {0x10d0040, 0x50000, 0x0, 0x80000228 }, 
    {0x10e0040, 0x60000, 0x0, 0x80000228 }, 
    {0x10f0040, 0x70000, 0x0, 0x80000228 }, 
    {0x80040, 0x0, 0x0, 0x80000230 }, 
    {0x1090040, 0x10000, 0x0, 0x80000230 }, 
    {0x10a0040, 0x20000, 0x0, 0x80000230 }, 
    {0x10b0040, 0x30000, 0x0, 0x80000230 }, 
    {0x10c0040, 0x40000, 0x0, 0x80000230 }, 
    {0x10d0040, 0x50000, 0x0, 0x80000230 }, 
    {0x10e0040, 0x60000, 0x0, 0x80000230 }, 
    {0x10f0040, 0x70000, 0x0, 0x80000230 }, 
    {0x80040, 0x0, 0x0, 0x80000238 }, 
    {0x1090040, 0x10000, 0x0, 0x80000238 }, 
    {0x10a0040, 0x20000, 0x0, 0x80000238 }, 
    {0x10b0040, 0x30000, 0x0, 0x80000238 }, 
    {0x10c0040, 0x40000, 0x0, 0x80000238 }, 
    {0x10d0040, 0x50000, 0x0, 0x80000238 }, 
    {0x10e0040, 0x60000, 0x0, 0x80000238 }, 
    {0x10f0040, 0x70000, 0x0, 0x80000238 }, 
    {0x1100040, 0x80000, 0x0, 0x80000238 }, 
    {0x1110040, 0x90000, 0x0, 0x80000238 }, 
    {0x1120040, 0xa0000, 0x0, 0x80000238 }, 
    {0x1130040, 0xb0000, 0x0, 0x80000238 }, 
    {0x1140040, 0xc0000, 0x0, 0x80000238 }, 
    {0x1150040, 0xd0000, 0x0, 0x80000238 }, 
    {0x1160040, 0xe0000, 0x0, 0x80000238 }, 
    {0x1170040, 0xf0000, 0x0, 0x80000238 }, 
    {0x1180040, 0x100000, 0x0, 0x80000238 }, 
    {0x2190040, 0x101100, 0x0, 0x80000238 }, 
    {0x21a0040, 0x101200, 0x0, 0x80000238 }, 
    {0x21b0040, 0x101300, 0x0, 0x80000238 }, 
    {0x21c0040, 0x101400, 0x0, 0x80000238 }, 
    {0x21d0040, 0x101500, 0x0, 0x80000238 }, 
    {0x21e0040, 0x101600, 0x0, 0x80000238 }, 
    {0x21f0040, 0x101700, 0x0, 0x80000238 }, 
    {0x2200040, 0x101800, 0x0, 0x80000238 }, 
    {0x2210040, 0x101900, 0x0, 0x80000238 }, 
    {0x2220040, 0x101a00, 0x0, 0x80000238 }, 
    {0x2230040, 0x101b00, 0x0, 0x80000238 }, 
    {0x2240040, 0x101c00, 0x0, 0x80000238 }, 
    {0x2250040, 0x101d00, 0x0, 0x80000238 }, 
    {0x2260040, 0x101e00, 0x0, 0x80000238 }, 
    {0x2270040, 0x101f00, 0x0, 0x80000238 }, 
    {0x2280040, 0x102000, 0x0, 0x80000238 }, 
    {0x3290040, 0x102021, 0x0, 0x80000238 }, 
    {0x32a0040, 0x102022, 0x0, 0x80000238 }, 
    {0x32b0040, 0x102023, 0x0, 0x80000238 }, 
    {0x32c0040, 0x102024, 0x0, 0x80000238 }, 
    {0x32d0040, 0x102025, 0x0, 0x80000238 }, 
    {0x32e0040, 0x102026, 0x0, 0x80000238 }, 
    {0x32f0040, 0x102027, 0x0, 0x80000238 }, 
    {0x80040, 0x0, 0x0, 0x80000260 }, 
    {0x1090040, 0x10000, 0x0, 0x80000260 }, 
    {0x10a0040, 0x20000, 0x0, 0x80000260 }, 
    {0x10b0040, 0x30000, 0x0, 0x80000260 }, 
    {0x10c0040, 0x40000, 0x0, 0x80000260 }, 
    {0x10d0040, 0x50000, 0x0, 0x80000260 }, 
    {0x10e0040, 0x60000, 0x0, 0x80000260 }, 
    {0x10f0040, 0x70000, 0x0, 0x80000260 }, 
    {0x80040, 0x0, 0x0, 0x80000268 }, 
    {0x1090040, 0x10000, 0x0, 0x80000268 }, 
    {0x10a0040, 0x20000, 0x0, 0x80000268 }, 
    {0x10b0040, 0x30000, 0x0, 0x80000268 }, 
    {0x10c0040, 0x40000, 0x0, 0x80000268 }, 
    {0x10d0040, 0x50000, 0x0, 0x80000268 }, 
    {0x10e0040, 0x60000, 0x0, 0x80000268 }, 
    {0x10f0040, 0x70000, 0x0, 0x80000268 }, 
    {0x80040, 0x0, 0x0, 0x80000270 }, 
    {0x1090040, 0x10000, 0x0, 0x80000270 }, 
    {0x10a0040, 0x20000, 0x0, 0x80000270 }, 
    {0x10b0040, 0x30000, 0x0, 0x80000270 }, 
    {0x10c0040, 0x40000, 0x0, 0x80000270 }, 
    {0x10d0040, 0x50000, 0x0, 0x80000270 }, 
    {0x10e0040, 0x60000, 0x0, 0x80000270 }, 
    {0x10f0040, 0x70000, 0x0, 0x80000270 }, 
    {0x80040, 0x0, 0x0, 0x80000278 }, 
    {0x1090040, 0x10000, 0x0, 0x80000278 }, 
    {0x10a0040, 0x20000, 0x0, 0x80000278 }, 
    {0x10b0040, 0x30000, 0x0, 0x80000278 }, 
    {0x10c0040, 0x40000, 0x0, 0x80000278 }, 
    {0x10d0040, 0x50000, 0x0, 0x80000278 }, 
    {0x10e0040, 0x60000, 0x0, 0x80000278 }, 
    {0x10f0040, 0x70000, 0x0, 0x80000278 }, 
    {0x1100040, 0x80000, 0x0, 0x80000278 }, 
    {0x1110040, 0x90000, 0x0, 0x80000278 }, 
    {0x1120040, 0xa0000, 0x0, 0x80000278 }, 
    {0x1130040, 0xb0000, 0x0, 0x80000278 }, 
    {0x1140040, 0xc0000, 0x0, 0x80000278 }, 
    {0x1150040, 0xd0000, 0x0, 0x80000278 }, 
    {0x1160040, 0xe0000, 0x0, 0x80000278 }, 
    {0x1170040, 0xf0000, 0x0, 0x80000278 }, 
    {0x1180040, 0x100000, 0x0, 0x80000278 }, 
    {0x2190040, 0x101100, 0x0, 0x80000278 }, 
    {0x21a0040, 0x101200, 0x0, 0x80000278 }, 
    {0x21b0040, 0x101300, 0x0, 0x80000278 }, 
    {0x21c0040, 0x101400, 0x0, 0x80000278 }, 
    {0x21d0040, 0x101500, 0x0, 0x80000278 }, 
    {0x21e0040, 0x101600, 0x0, 0x80000278 }, 
    {0x21f0040, 0x101700, 0x0, 0x80000278 }, 
    {0x2200040, 0x101800, 0x0, 0x80000278 }, 
    {0x2210040, 0x101900, 0x0, 0x80000278 }, 
    {0x2220040, 0x101a00, 0x0, 0x80000278 }, 
    {0x2230040, 0x101b00, 0x0, 0x80000278 }, 
    {0x2240040, 0x101c00, 0x0, 0x80000278 }, 
    {0x2250040, 0x101d00, 0x0, 0x80000278 }, 
    {0x2260040, 0x101e00, 0x0, 0x80000278 }, 
    {0x2270040, 0x101f00, 0x0, 0x80000278 }, 
    {0x2280040, 0x102000, 0x0, 0x80000278 }, 
    {0x3290040, 0x102021, 0x0, 0x80000278 }, 
    {0x32a0040, 0x102022, 0x0, 0x80000278 }, 
    {0x32b0040, 0x102023, 0x0, 0x80000278 }, 
    {0x32c0040, 0x102024, 0x0, 0x80000278 }, 
    {0x32d0040, 0x102025, 0x0, 0x80000278 }, 
    {0x32e0040, 0x102026, 0x0, 0x80000278 }, 
    {0x32f0040, 0x102027, 0x0, 0x80000278 }, 
    {0x3300040, 0x102028, 0x0, 0x80000278 }, 
    {0x3310040, 0x102029, 0x0, 0x80000278 }, 
    {0x3320040, 0x10202a, 0x0, 0x80000278 }, 
    {0x3330040, 0x10202b, 0x0, 0x80000278 }, 
    {0x3340040, 0x10202c, 0x0, 0x80000278 }, 
    {0x3350040, 0x10202d, 0x0, 0x80000278 }, 
    {0x3360040, 0x10202e, 0x0, 0x80000278 }, 
    {0x3370040, 0x10202f, 0x0, 0x80000278 }, 
    {0x3380040, 0x102030, 0x0, 0x80000278 }, 
    {0x4390040, 0x81020, 0x29000000, 0x80000478 }, 
    {0x43a0040, 0x81020, 0x2a000000, 0x80000478 }, 
    {0x43b0040, 0x81020, 0x2b000000, 0x80000478 }, 
    {0x43c0040, 0x81020, 0x2c000000, 0x80000478 }, 
    {0x43d0040, 0x81020, 0x2d000000, 0x80000478 }, 
    {0x43e0040, 0x81020, 0x2e000000, 0x80000478 }, 
    {0x43f0040, 0x81020, 0x2f000000, 0x80000478 }, 
    {0x4400040, 0x81020, 0x30000000, 0x80000478 }, 
    {0x4410040, 0x102030, 0x31000000, 0x80000478 }, 
    {0x4420040, 0x102030, 0x32000000, 0x80000478 }, 
    {0x4430040, 0x102030, 0x33000000, 0x80000478 }, 
    {0x4440040, 0x102030, 0x34000000, 0x80000478 }, 
    {0x4450040, 0x102030, 0x35000000, 0x80000478 }, 
    {0x4460040, 0x102030, 0x36000000, 0x80000478 }, 
    {0x4470040, 0x102030, 0x37000000, 0x80000478 }, 
    {0x4480040, 0x102030, 0x38000000, 0x80000478 }, 
    {0x4490040, 0x102030, 0x39000000, 0x80000478 }, 
    {0x44a0040, 0x102030, 0x3a000000, 0x80000478 }, 
    {0x44b0040, 0x102030, 0x3b000000, 0x80000478 }, 
    {0x44c0040, 0x102030, 0x3c000000, 0x80000478 }, 
    {0x44d0040, 0x102030, 0x3d000000, 0x80000478 }, 
    {0x44e0040, 0x102030, 0x3e000000, 0x80000478 }, 
    {0x44f0040, 0x102030, 0x3f000000, 0x80000478 }, 
    {0x4500040, 0x102030, 0x40000000, 0x80000478 }, 
    {0x5510040, 0x102030, 0x40410000, 0x80000478 }, 
    {0x5520040, 0x102030, 0x40420000, 0x80000478 }, 
    {0x5530040, 0x102030, 0x40430000, 0x80000478 }, 
    {0x5540040, 0x102030, 0x40440000, 0x80000478 }, 
    {0x5550040, 0x102030, 0x40450000, 0x80000478 }, 
    {0x5560040, 0x102030, 0x40460000, 0x80000478 }, 
    {0x5570040, 0x102030, 0x40470000, 0x80000478 }, 
    {0x5580040, 0x102030, 0x40480000, 0x80000478 }, 
    {0x5590040, 0x102030, 0x40490000, 0x80000478 }, 
    {0x55a0040, 0x102030, 0x404a0000, 0x80000478 }, 
    {0x55b0040, 0x102030, 0x404b0000, 0x80000478 }, 
    {0x55c0040, 0x102030, 0x404c0000, 0x80000478 }, 
    {0x55d0040, 0x102030, 0x404d0000, 0x80000478 }, 
    {0x55e0040, 0x102030, 0x404e0000, 0x80000478 }, 
    {0x55f0040, 0x102030, 0x404f0000, 0x80000478 }, 
    {0x5600040, 0x102030, 0x40500000, 0x80000478 }, 
    {0x6610040, 0x102030, 0x40505100, 0x80000478 }, 
    {0x6620040, 0x102030, 0x40505200, 0x80000478 }, 
    {0x6630040, 0x102030, 0x40505300, 0x80000478 }, 
    {0x6640040, 0x102030, 0x40505400, 0x80000478 }, 
    {0x6650040, 0x102030, 0x40505500, 0x80000478 }, 
    {0x6660040, 0x102030, 0x40505600, 0x80000478 }, 
    {0x6670040, 0x102030, 0x40505700, 0x80000478 }, 
    {0x6680040, 0x102030, 0x40505800, 0x80000478 }, 
    {0x6690040, 0x102030, 0x40505900, 0x80000478 }, 
    {0x66a0040, 0x102030, 0x40505a00, 0x80000478 }, 
    {0x66b0040, 0x102030, 0x40505b00, 0x80000478 }, 
    {0x66c0040, 0x102030, 0x40505c00, 0x80000478 }, 
    {0x66d0040, 0x102030, 0x40505d00, 0x80000478 }, 
    {0x66e0040, 0x102030, 0x40505e00, 0x80000478 }, 
    {0x66f0040, 0x102030, 0x40505f00, 0x80000478 }, 
    {0x6700040, 0x102030, 0x40506000, 0x80000478 }, 
    {0x7710040, 0x102030, 0x40506061, 0x80000478 }, 
    {0x7720040, 0x102030, 0x40506062, 0x80000478 }, 
    {0x7730040, 0x102030, 0x40506063, 0x80000478 }, 
    {0x7740040, 0x102030, 0x40506064, 0x80000478 }, 
    {0x7750040, 0x102030, 0x40506065, 0x80000478 }, 
    {0x7760040, 0x102030, 0x40506066, 0x80000478 }, 
    {0x7770040, 0x102030, 0x40506067, 0x80000478 }, 
    {0x7780040, 0x102030, 0x40506068, 0x80000478 }, 
    {0x7790040, 0x102030, 0x40506069, 0x80000478 }, 
    {0x77a0040, 0x102030, 0x4050606a, 0x80000478 }, 
    {0x77b0040, 0x102030, 0x4050606b, 0x80000478 }, 
    {0x77c0040, 0x102030, 0x4050606c, 0x80000478 }, 
    {0x77d0040, 0x102030, 0x4050606d, 0x80000478 }, 
    {0x77e0040, 0x102030, 0x4050606e, 0x80000478 }, 
    {0x77f0040, 0x102030, 0x4050606f, 0x80000478 }, 
    {0x7800040, 0x102030, 0x40506070, 0x80000478 }
}; 
__intrinsic struct pkt_ms_info pif_pkt_msd_write(__addr40 void *pbuf, unsigned char off)
{
    __gpr struct pkt_ms_info msi;
    SIGNAL wr_sig,  rd_sig;
    __xread packet_modifier_struct_t rd_xfer;
    __xwrite packet_modifier_struct_t wr_xfer;
    __gpr uint32_t script_idx = off - PIF_PKT_MIN_NBI_TX_OFFSET;

    script_idx = script_idx/1;

    msi.off_enc = 0;
    if (script_idx < PKT_MOD_SCRIPT_ENTRIES) {
        cls_read(&rd_xfer, (__cls void *)&pkt_mod_script_tbl[script_idx][0], sizeof(packet_modifier_struct_t));

        reg_cp(&wr_xfer.value[0], &rd_xfer.value[0], sizeof(wr_xfer));

        {
            __addr40 unsigned char *mem_ptr = (__addr40 unsigned char *)pbuf + rd_xfer.prepend_offset;

            __mem_write32(&wr_xfer.value[0], mem_ptr, rd_xfer.prepend_len0 << 2, 4 << 2, sig_done, &wr_sig);
            __mem_read32(&rd_xfer.value[0], mem_ptr, 1 << 2, 1 << 2, sig_done, &rd_sig);

            // Set the length adjustment to point to the start of packet.
            msi.len_adj = off;

            // Set the encoding: 3=32, 4=40, 5=48, 6=56, 11=96, 12=104, 13=112, 14=120
            msi.off_enc = (rd_xfer.prepend_offset >> 3) - 1;
            wait_for_all(&wr_sig, &rd_sig);
        }
    }
    return msi;
}
