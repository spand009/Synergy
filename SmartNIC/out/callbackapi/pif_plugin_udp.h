/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_UDP_H__
#define __PIF_PLUGIN_UDP_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* udp (8B) */
struct pif_plugin_udp {
    unsigned int srcPort:16;
    unsigned int dstPort:16;
    unsigned int length_:16;
    unsigned int checksum:16;
};

/* udp field accessor macros */
#define PIF_HEADER_GET_udp___srcPort(_hdr_p) (((_hdr_p)->srcPort)) /* udp.srcPort [16;0] */

#define PIF_HEADER_SET_udp___srcPort(_hdr_p, _val) \
    do { \
        (_hdr_p)->srcPort = (unsigned)(((_val))); \
    } while (0) /* udp.srcPort[16;0] */

#define PIF_HEADER_GET_udp___dstPort(_hdr_p) (((_hdr_p)->dstPort)) /* udp.dstPort [16;0] */

#define PIF_HEADER_SET_udp___dstPort(_hdr_p, _val) \
    do { \
        (_hdr_p)->dstPort = (unsigned)(((_val))); \
    } while (0) /* udp.dstPort[16;0] */

#define PIF_HEADER_GET_udp___length_(_hdr_p) (((_hdr_p)->length_)) /* udp.length_ [16;0] */

#define PIF_HEADER_SET_udp___length_(_hdr_p, _val) \
    do { \
        (_hdr_p)->length_ = (unsigned)(((_val))); \
    } while (0) /* udp.length_[16;0] */

#define PIF_HEADER_GET_udp___checksum(_hdr_p) (((_hdr_p)->checksum)) /* udp.checksum [16;0] */

#define PIF_HEADER_SET_udp___checksum(_hdr_p, _val) \
    do { \
        (_hdr_p)->checksum = (unsigned)(((_val))); \
    } while (0) /* udp.checksum[16;0] */



#define PIF_PLUGIN_udp_T __lmem struct pif_plugin_udp

/*
 * Access function prototypes
 */

int pif_plugin_hdr_udp_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_udp_T *pif_plugin_hdr_get_udp(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_udp_T *pif_plugin_hdr_readonly_get_udp(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_udp_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_udp_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

int pif_plugin_hdr_udp_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_udp_VALID(_ctl);
}

PIF_PLUGIN_udp_T *pif_plugin_hdr_get_udp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_udp_DIRTY(_ctl);
    return (PIF_PLUGIN_udp_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_udp_OFF_LW);
}

PIF_PLUGIN_udp_T *pif_plugin_hdr_readonly_get_udp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_udp_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_udp_OFF_LW);
}

int pif_plugin_hdr_udp_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T3_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_udp_VALID(_ctl);
    return 0;
}

int pif_plugin_hdr_udp_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_udp_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_udp_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_UDP_H__ */
