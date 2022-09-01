/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_GTPU_H__
#define __PIF_PLUGIN_GTPU_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* gtpu (8B) */
struct pif_plugin_gtpu {
    unsigned int flags:8;
    unsigned int type_:8;
    unsigned int length_:16;
    unsigned int teid:32;
};

/* gtpu field accessor macros */
#define PIF_HEADER_GET_gtpu___flags(_hdr_p) (((_hdr_p)->flags)) /* gtpu.flags [8;0] */

#define PIF_HEADER_SET_gtpu___flags(_hdr_p, _val) \
    do { \
        (_hdr_p)->flags = (unsigned)(((_val))); \
    } while (0) /* gtpu.flags[8;0] */

#define PIF_HEADER_GET_gtpu___type_(_hdr_p) (((_hdr_p)->type_)) /* gtpu.type_ [8;0] */

#define PIF_HEADER_SET_gtpu___type_(_hdr_p, _val) \
    do { \
        (_hdr_p)->type_ = (unsigned)(((_val))); \
    } while (0) /* gtpu.type_[8;0] */

#define PIF_HEADER_GET_gtpu___length_(_hdr_p) (((_hdr_p)->length_)) /* gtpu.length_ [16;0] */

#define PIF_HEADER_SET_gtpu___length_(_hdr_p, _val) \
    do { \
        (_hdr_p)->length_ = (unsigned)(((_val))); \
    } while (0) /* gtpu.length_[16;0] */

#define PIF_HEADER_GET_gtpu___teid(_hdr_p) (((_hdr_p)->teid)) /* gtpu.teid [32;0] */

#define PIF_HEADER_SET_gtpu___teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->teid = (unsigned)(((_val))); \
    } while (0) /* gtpu.teid[32;0] */



#define PIF_PLUGIN_gtpu_T __lmem struct pif_plugin_gtpu

/*
 * Access function prototypes
 */

int pif_plugin_hdr_gtpu_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_gtpu_T *pif_plugin_hdr_get_gtpu(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_gtpu_T *pif_plugin_hdr_readonly_get_gtpu(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_gtpu_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_gtpu_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

int pif_plugin_hdr_gtpu_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_gtpu_VALID(_ctl);
}

PIF_PLUGIN_gtpu_T *pif_plugin_hdr_get_gtpu(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_gtpu_DIRTY(_ctl);
    return (PIF_PLUGIN_gtpu_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_gtpu_OFF_LW);
}

PIF_PLUGIN_gtpu_T *pif_plugin_hdr_readonly_get_gtpu(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_gtpu_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_gtpu_OFF_LW);
}

int pif_plugin_hdr_gtpu_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T4_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_gtpu_VALID(_ctl);
    return 0;
}

int pif_plugin_hdr_gtpu_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_gtpu_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_gtpu_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_GTPU_H__ */
