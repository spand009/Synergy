/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_FLCALC_H__
#define __PIF_FLCALC_H__

/* Generated C source defining pkt_recurse related bits and bobs  */
/* Warning: your edits to this file may be lost */

int pif_flcalc_verify(__lmem uint32_t *parrep);

void pif_flcalc_update(__lmem uint32_t *parrep);

#define PIF_FLCALC_UPD_INCR(idx) (pif_pkt_info_global.calc_fld_bmsk & (1<<idx))
#define PIF_FLCALC_UPD_INCR_SET(idx) \
    do { \
        pif_pkt_info_global.calc_fld_bmsk |= (1<<idx); \
    } while(0);
#define PIF_FLCALC_UPD_INCR_CLEAR(idx) \
    do { \
        pif_pkt_info_global.calc_fld_bmsk &= ~(1<<idx); \
    } while(0);

#endif /* __PIF_FLCALC_H__ */
