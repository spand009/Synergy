/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_ETHERNET_H__
#define __PIF_PLUGIN_ETHERNET_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* ethernet (14B) */
struct pif_plugin_ethernet {
    /* dstAddr [32;16] */
    unsigned int __dstAddr_0:32;
    /* dstAddr [16;0] */
    unsigned int __dstAddr_1:16;
    /* srcAddr [16;32] */
    unsigned int __srcAddr_0:16;
    /* srcAddr [32;0] */
    unsigned int __srcAddr_1:32;
    unsigned int etherType:16;
};

/* ethernet field accessor macros */
#define PIF_HEADER_GET_ethernet___dstAddr___0(_hdr_p) ((((_hdr_p)->__dstAddr_0 & 0xffff) << 16) | ((_hdr_p)->__dstAddr_1)) /* ethernet.dstAddr [32;0] */

#define PIF_HEADER_SET_ethernet___dstAddr___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__dstAddr_0 &= (unsigned)(0xffff0000); \
        (_hdr_p)->__dstAddr_0 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__dstAddr_1 = (unsigned)(((_val))); \
    } while (0) /* ethernet.dstAddr[32;0] */

#define PIF_HEADER_GET_ethernet___dstAddr___1(_hdr_p) ((((_hdr_p)->__dstAddr_0 >> 16) & 0xffff)) /* ethernet.dstAddr [16;32] */

#define PIF_HEADER_SET_ethernet___dstAddr___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->__dstAddr_0 &= (unsigned)(0xffff); \
        (_hdr_p)->__dstAddr_0 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* ethernet.dstAddr[16;32] */

#define PIF_HEADER_GET_ethernet___srcAddr___0(_hdr_p) (((_hdr_p)->__srcAddr_1)) /* ethernet.srcAddr [32;0] */

#define PIF_HEADER_SET_ethernet___srcAddr___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__srcAddr_1 = (unsigned)(((_val))); \
    } while (0) /* ethernet.srcAddr[32;0] */

#define PIF_HEADER_GET_ethernet___srcAddr___1(_hdr_p) (((_hdr_p)->__srcAddr_0)) /* ethernet.srcAddr [16;32] */

#define PIF_HEADER_SET_ethernet___srcAddr___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->__srcAddr_0 = (unsigned)(((_val))); \
    } while (0) /* ethernet.srcAddr[16;32] */

#define PIF_HEADER_GET_ethernet___etherType(_hdr_p) (((_hdr_p)->etherType)) /* ethernet.etherType [16;0] */

#define PIF_HEADER_SET_ethernet___etherType(_hdr_p, _val) \
    do { \
        (_hdr_p)->etherType = (unsigned)(((_val))); \
    } while (0) /* ethernet.etherType[16;0] */



#define PIF_PLUGIN_ethernet_T __lmem struct pif_plugin_ethernet

/*
 * Access function prototypes
 */

int pif_plugin_hdr_ethernet_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_ethernet_T *pif_plugin_hdr_get_ethernet(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_ethernet_T *pif_plugin_hdr_readonly_get_ethernet(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_ethernet_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_ethernet_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

int pif_plugin_hdr_ethernet_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_ethernet_VALID(_ctl);
}

PIF_PLUGIN_ethernet_T *pif_plugin_hdr_get_ethernet(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_ethernet_DIRTY(_ctl);
    return (PIF_PLUGIN_ethernet_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_ethernet_OFF_LW);
}

PIF_PLUGIN_ethernet_T *pif_plugin_hdr_readonly_get_ethernet(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_ethernet_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_ethernet_OFF_LW);
}

int pif_plugin_hdr_ethernet_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    return -1; /* this header is not addable in the P4 design */
}

int pif_plugin_hdr_ethernet_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    return -1; /* this header is not removable in the P4 design */
}

#endif /* __PIF_PLUGIN_ETHERNET_H__ */
