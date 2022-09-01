/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_TCP_H__
#define __PIF_PLUGIN_TCP_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* tcp (20B) */
struct pif_plugin_tcp {
    unsigned int srcPort:16;
    unsigned int dstPort:16;
    unsigned int seqNo:32;
    unsigned int ackNo:32;
    unsigned int dataOffset:4;
    unsigned int res:4;
    unsigned int flags:8;
    unsigned int window:16;
    unsigned int checksum:16;
    unsigned int urgentPtr:16;
};

/* tcp field accessor macros */
#define PIF_HEADER_GET_tcp___srcPort(_hdr_p) (((_hdr_p)->srcPort)) /* tcp.srcPort [16;0] */

#define PIF_HEADER_SET_tcp___srcPort(_hdr_p, _val) \
    do { \
        (_hdr_p)->srcPort = (unsigned)(((_val))); \
    } while (0) /* tcp.srcPort[16;0] */

#define PIF_HEADER_GET_tcp___dstPort(_hdr_p) (((_hdr_p)->dstPort)) /* tcp.dstPort [16;0] */

#define PIF_HEADER_SET_tcp___dstPort(_hdr_p, _val) \
    do { \
        (_hdr_p)->dstPort = (unsigned)(((_val))); \
    } while (0) /* tcp.dstPort[16;0] */

#define PIF_HEADER_GET_tcp___seqNo(_hdr_p) (((_hdr_p)->seqNo)) /* tcp.seqNo [32;0] */

#define PIF_HEADER_SET_tcp___seqNo(_hdr_p, _val) \
    do { \
        (_hdr_p)->seqNo = (unsigned)(((_val))); \
    } while (0) /* tcp.seqNo[32;0] */

#define PIF_HEADER_GET_tcp___ackNo(_hdr_p) (((_hdr_p)->ackNo)) /* tcp.ackNo [32;0] */

#define PIF_HEADER_SET_tcp___ackNo(_hdr_p, _val) \
    do { \
        (_hdr_p)->ackNo = (unsigned)(((_val))); \
    } while (0) /* tcp.ackNo[32;0] */

#define PIF_HEADER_GET_tcp___dataOffset(_hdr_p) (((_hdr_p)->dataOffset)) /* tcp.dataOffset [4;0] */

#define PIF_HEADER_SET_tcp___dataOffset(_hdr_p, _val) \
    do { \
        (_hdr_p)->dataOffset = (unsigned)(((_val))); \
    } while (0) /* tcp.dataOffset[4;0] */

#define PIF_HEADER_GET_tcp___res(_hdr_p) (((_hdr_p)->res)) /* tcp.res [4;0] */

#define PIF_HEADER_SET_tcp___res(_hdr_p, _val) \
    do { \
        (_hdr_p)->res = (unsigned)(((_val))); \
    } while (0) /* tcp.res[4;0] */

#define PIF_HEADER_GET_tcp___flags(_hdr_p) (((_hdr_p)->flags)) /* tcp.flags [8;0] */

#define PIF_HEADER_SET_tcp___flags(_hdr_p, _val) \
    do { \
        (_hdr_p)->flags = (unsigned)(((_val))); \
    } while (0) /* tcp.flags[8;0] */

#define PIF_HEADER_GET_tcp___window(_hdr_p) (((_hdr_p)->window)) /* tcp.window [16;0] */

#define PIF_HEADER_SET_tcp___window(_hdr_p, _val) \
    do { \
        (_hdr_p)->window = (unsigned)(((_val))); \
    } while (0) /* tcp.window[16;0] */

#define PIF_HEADER_GET_tcp___checksum(_hdr_p) (((_hdr_p)->checksum)) /* tcp.checksum [16;0] */

#define PIF_HEADER_SET_tcp___checksum(_hdr_p, _val) \
    do { \
        (_hdr_p)->checksum = (unsigned)(((_val))); \
    } while (0) /* tcp.checksum[16;0] */

#define PIF_HEADER_GET_tcp___urgentPtr(_hdr_p) (((_hdr_p)->urgentPtr)) /* tcp.urgentPtr [16;0] */

#define PIF_HEADER_SET_tcp___urgentPtr(_hdr_p, _val) \
    do { \
        (_hdr_p)->urgentPtr = (unsigned)(((_val))); \
    } while (0) /* tcp.urgentPtr[16;0] */



#define PIF_PLUGIN_tcp_T __lmem struct pif_plugin_tcp

/*
 * Access function prototypes
 */

int pif_plugin_hdr_tcp_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_tcp_T *pif_plugin_hdr_get_tcp(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_tcp_T *pif_plugin_hdr_readonly_get_tcp(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_tcp_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_tcp_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

int pif_plugin_hdr_tcp_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_tcp_VALID(_ctl);
}

PIF_PLUGIN_tcp_T *pif_plugin_hdr_get_tcp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_tcp_DIRTY(_ctl);
    return (PIF_PLUGIN_tcp_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_tcp_OFF_LW);
}

PIF_PLUGIN_tcp_T *pif_plugin_hdr_readonly_get_tcp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_tcp_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_tcp_OFF_LW);
}

int pif_plugin_hdr_tcp_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    return -1; /* this header is not addable in the P4 design */
}

int pif_plugin_hdr_tcp_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    return -1; /* this header is not removable in the P4 design */
}

#endif /* __PIF_PLUGIN_TCP_H__ */
