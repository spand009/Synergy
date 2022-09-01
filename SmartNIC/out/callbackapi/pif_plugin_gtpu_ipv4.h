/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_GTPU_IPV4_H__
#define __PIF_PLUGIN_GTPU_IPV4_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* gtpu_ipv4 (20B) */
struct pif_plugin_gtpu_ipv4 {
    unsigned int version:4;
    unsigned int ihl:4;
    unsigned int diffserv:8;
    unsigned int totalLen:16;
    unsigned int identification:16;
    unsigned int flags:3;
    unsigned int fragOffset:13;
    unsigned int ttl:8;
    unsigned int protocol:8;
    unsigned int hdrChecksum:16;
    unsigned int srcAddr:32;
    unsigned int dstAddr:32;
};

/* gtpu_ipv4 field accessor macros */
#define PIF_HEADER_GET_gtpu_ipv4___version(_hdr_p) (((_hdr_p)->version)) /* gtpu_ipv4.version [4;0] */

#define PIF_HEADER_SET_gtpu_ipv4___version(_hdr_p, _val) \
    do { \
        (_hdr_p)->version = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.version[4;0] */

#define PIF_HEADER_GET_gtpu_ipv4___ihl(_hdr_p) (((_hdr_p)->ihl)) /* gtpu_ipv4.ihl [4;0] */

#define PIF_HEADER_SET_gtpu_ipv4___ihl(_hdr_p, _val) \
    do { \
        (_hdr_p)->ihl = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.ihl[4;0] */

#define PIF_HEADER_GET_gtpu_ipv4___diffserv(_hdr_p) (((_hdr_p)->diffserv)) /* gtpu_ipv4.diffserv [8;0] */

#define PIF_HEADER_SET_gtpu_ipv4___diffserv(_hdr_p, _val) \
    do { \
        (_hdr_p)->diffserv = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.diffserv[8;0] */

#define PIF_HEADER_GET_gtpu_ipv4___totalLen(_hdr_p) (((_hdr_p)->totalLen)) /* gtpu_ipv4.totalLen [16;0] */

#define PIF_HEADER_SET_gtpu_ipv4___totalLen(_hdr_p, _val) \
    do { \
        (_hdr_p)->totalLen = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.totalLen[16;0] */

#define PIF_HEADER_GET_gtpu_ipv4___identification(_hdr_p) (((_hdr_p)->identification)) /* gtpu_ipv4.identification [16;0] */

#define PIF_HEADER_SET_gtpu_ipv4___identification(_hdr_p, _val) \
    do { \
        (_hdr_p)->identification = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.identification[16;0] */

#define PIF_HEADER_GET_gtpu_ipv4___flags(_hdr_p) (((_hdr_p)->flags)) /* gtpu_ipv4.flags [3;0] */

#define PIF_HEADER_SET_gtpu_ipv4___flags(_hdr_p, _val) \
    do { \
        (_hdr_p)->flags = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.flags[3;0] */

#define PIF_HEADER_GET_gtpu_ipv4___fragOffset(_hdr_p) (((_hdr_p)->fragOffset)) /* gtpu_ipv4.fragOffset [13;0] */

#define PIF_HEADER_SET_gtpu_ipv4___fragOffset(_hdr_p, _val) \
    do { \
        (_hdr_p)->fragOffset = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.fragOffset[13;0] */

#define PIF_HEADER_GET_gtpu_ipv4___ttl(_hdr_p) (((_hdr_p)->ttl)) /* gtpu_ipv4.ttl [8;0] */

#define PIF_HEADER_SET_gtpu_ipv4___ttl(_hdr_p, _val) \
    do { \
        (_hdr_p)->ttl = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.ttl[8;0] */

#define PIF_HEADER_GET_gtpu_ipv4___protocol(_hdr_p) (((_hdr_p)->protocol)) /* gtpu_ipv4.protocol [8;0] */

#define PIF_HEADER_SET_gtpu_ipv4___protocol(_hdr_p, _val) \
    do { \
        (_hdr_p)->protocol = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.protocol[8;0] */

#define PIF_HEADER_GET_gtpu_ipv4___hdrChecksum(_hdr_p) (((_hdr_p)->hdrChecksum)) /* gtpu_ipv4.hdrChecksum [16;0] */

#define PIF_HEADER_SET_gtpu_ipv4___hdrChecksum(_hdr_p, _val) \
    do { \
        (_hdr_p)->hdrChecksum = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.hdrChecksum[16;0] */

#define PIF_HEADER_GET_gtpu_ipv4___srcAddr(_hdr_p) (((_hdr_p)->srcAddr)) /* gtpu_ipv4.srcAddr [32;0] */

#define PIF_HEADER_SET_gtpu_ipv4___srcAddr(_hdr_p, _val) \
    do { \
        (_hdr_p)->srcAddr = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.srcAddr[32;0] */

#define PIF_HEADER_GET_gtpu_ipv4___dstAddr(_hdr_p) (((_hdr_p)->dstAddr)) /* gtpu_ipv4.dstAddr [32;0] */

#define PIF_HEADER_SET_gtpu_ipv4___dstAddr(_hdr_p, _val) \
    do { \
        (_hdr_p)->dstAddr = (unsigned)(((_val))); \
    } while (0) /* gtpu_ipv4.dstAddr[32;0] */



#define PIF_PLUGIN_gtpu_ipv4_T __lmem struct pif_plugin_gtpu_ipv4

/*
 * Access function prototypes
 */

int pif_plugin_hdr_gtpu_ipv4_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_gtpu_ipv4_T *pif_plugin_hdr_get_gtpu_ipv4(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_gtpu_ipv4_T *pif_plugin_hdr_readonly_get_gtpu_ipv4(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_gtpu_ipv4_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_gtpu_ipv4_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

int pif_plugin_hdr_gtpu_ipv4_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_gtpu_ipv4_VALID(_ctl);
}

PIF_PLUGIN_gtpu_ipv4_T *pif_plugin_hdr_get_gtpu_ipv4(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_gtpu_ipv4_DIRTY(_ctl);
    return (PIF_PLUGIN_gtpu_ipv4_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_gtpu_ipv4_OFF_LW);
}

PIF_PLUGIN_gtpu_ipv4_T *pif_plugin_hdr_readonly_get_gtpu_ipv4(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_gtpu_ipv4_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_gtpu_ipv4_OFF_LW);
}

int pif_plugin_hdr_gtpu_ipv4_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T5_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_gtpu_ipv4_VALID(_ctl);
    return 0;
}

int pif_plugin_hdr_gtpu_ipv4_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_gtpu_ipv4_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_gtpu_ipv4_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_GTPU_IPV4_H__ */
