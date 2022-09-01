/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_HEADERS_H__
#define __PIF_HEADERS_H__

/* Generated C source defining PIF headers, metadata and registers */
/* Warning: your edits to this file may be lost */

/*
 * Packet headers
 */

/* udp (8B) */
struct pif_header_udp {
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


/* gtpu_ipv4 (20B) */
struct pif_header_gtpu_ipv4 {
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


/* gtpu (8B) */
struct pif_header_gtpu {
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


/* tcp (20B) */
struct pif_header_tcp {
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


/* ipv4 (20B) */
struct pif_header_ipv4 {
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

/* ipv4 field accessor macros */
#define PIF_HEADER_GET_ipv4___version(_hdr_p) (((_hdr_p)->version)) /* ipv4.version [4;0] */

#define PIF_HEADER_SET_ipv4___version(_hdr_p, _val) \
    do { \
        (_hdr_p)->version = (unsigned)(((_val))); \
    } while (0) /* ipv4.version[4;0] */

#define PIF_HEADER_GET_ipv4___ihl(_hdr_p) (((_hdr_p)->ihl)) /* ipv4.ihl [4;0] */

#define PIF_HEADER_SET_ipv4___ihl(_hdr_p, _val) \
    do { \
        (_hdr_p)->ihl = (unsigned)(((_val))); \
    } while (0) /* ipv4.ihl[4;0] */

#define PIF_HEADER_GET_ipv4___diffserv(_hdr_p) (((_hdr_p)->diffserv)) /* ipv4.diffserv [8;0] */

#define PIF_HEADER_SET_ipv4___diffserv(_hdr_p, _val) \
    do { \
        (_hdr_p)->diffserv = (unsigned)(((_val))); \
    } while (0) /* ipv4.diffserv[8;0] */

#define PIF_HEADER_GET_ipv4___totalLen(_hdr_p) (((_hdr_p)->totalLen)) /* ipv4.totalLen [16;0] */

#define PIF_HEADER_SET_ipv4___totalLen(_hdr_p, _val) \
    do { \
        (_hdr_p)->totalLen = (unsigned)(((_val))); \
    } while (0) /* ipv4.totalLen[16;0] */

#define PIF_HEADER_GET_ipv4___identification(_hdr_p) (((_hdr_p)->identification)) /* ipv4.identification [16;0] */

#define PIF_HEADER_SET_ipv4___identification(_hdr_p, _val) \
    do { \
        (_hdr_p)->identification = (unsigned)(((_val))); \
    } while (0) /* ipv4.identification[16;0] */

#define PIF_HEADER_GET_ipv4___flags(_hdr_p) (((_hdr_p)->flags)) /* ipv4.flags [3;0] */

#define PIF_HEADER_SET_ipv4___flags(_hdr_p, _val) \
    do { \
        (_hdr_p)->flags = (unsigned)(((_val))); \
    } while (0) /* ipv4.flags[3;0] */

#define PIF_HEADER_GET_ipv4___fragOffset(_hdr_p) (((_hdr_p)->fragOffset)) /* ipv4.fragOffset [13;0] */

#define PIF_HEADER_SET_ipv4___fragOffset(_hdr_p, _val) \
    do { \
        (_hdr_p)->fragOffset = (unsigned)(((_val))); \
    } while (0) /* ipv4.fragOffset[13;0] */

#define PIF_HEADER_GET_ipv4___ttl(_hdr_p) (((_hdr_p)->ttl)) /* ipv4.ttl [8;0] */

#define PIF_HEADER_SET_ipv4___ttl(_hdr_p, _val) \
    do { \
        (_hdr_p)->ttl = (unsigned)(((_val))); \
    } while (0) /* ipv4.ttl[8;0] */

#define PIF_HEADER_GET_ipv4___protocol(_hdr_p) (((_hdr_p)->protocol)) /* ipv4.protocol [8;0] */

#define PIF_HEADER_SET_ipv4___protocol(_hdr_p, _val) \
    do { \
        (_hdr_p)->protocol = (unsigned)(((_val))); \
    } while (0) /* ipv4.protocol[8;0] */

#define PIF_HEADER_GET_ipv4___hdrChecksum(_hdr_p) (((_hdr_p)->hdrChecksum)) /* ipv4.hdrChecksum [16;0] */

#define PIF_HEADER_SET_ipv4___hdrChecksum(_hdr_p, _val) \
    do { \
        (_hdr_p)->hdrChecksum = (unsigned)(((_val))); \
    } while (0) /* ipv4.hdrChecksum[16;0] */

#define PIF_HEADER_GET_ipv4___srcAddr(_hdr_p) (((_hdr_p)->srcAddr)) /* ipv4.srcAddr [32;0] */

#define PIF_HEADER_SET_ipv4___srcAddr(_hdr_p, _val) \
    do { \
        (_hdr_p)->srcAddr = (unsigned)(((_val))); \
    } while (0) /* ipv4.srcAddr[32;0] */

#define PIF_HEADER_GET_ipv4___dstAddr(_hdr_p) (((_hdr_p)->dstAddr)) /* ipv4.dstAddr [32;0] */

#define PIF_HEADER_SET_ipv4___dstAddr(_hdr_p, _val) \
    do { \
        (_hdr_p)->dstAddr = (unsigned)(((_val))); \
    } while (0) /* ipv4.dstAddr[32;0] */


/* ethernet (14B) */
struct pif_header_ethernet {
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


/*
 * Metadata
 */

/* standard_metadata (16B) */
struct pif_header_standard_metadata {
    unsigned int clone_spec:32;
    unsigned int egress_spec:16;
    unsigned int egress_port:16;
    unsigned int packet_length:14;
    unsigned int egress_instance:10;
    unsigned int instance_type:4;
    unsigned int _padding_0:4;
    unsigned int ingress_port:10;
    unsigned int _padding_1:22;
};

/* standard_metadata field accessor macros */
#define PIF_HEADER_GET_standard_metadata___clone_spec(_hdr_p) (((_hdr_p)->clone_spec)) /* standard_metadata.clone_spec [32;0] */

#define PIF_HEADER_SET_standard_metadata___clone_spec(_hdr_p, _val) \
    do { \
        (_hdr_p)->clone_spec = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.clone_spec[32;0] */

#define PIF_HEADER_GET_standard_metadata___egress_spec(_hdr_p) (((_hdr_p)->egress_spec)) /* standard_metadata.egress_spec [16;0] */

#define PIF_HEADER_SET_standard_metadata___egress_spec(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_spec = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.egress_spec[16;0] */

#define PIF_HEADER_GET_standard_metadata___egress_port(_hdr_p) (((_hdr_p)->egress_port)) /* standard_metadata.egress_port [16;0] */

#define PIF_HEADER_SET_standard_metadata___egress_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_port = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.egress_port[16;0] */

#define PIF_HEADER_GET_standard_metadata___packet_length(_hdr_p) (((_hdr_p)->packet_length)) /* standard_metadata.packet_length [14;0] */

#define PIF_HEADER_SET_standard_metadata___packet_length(_hdr_p, _val) \
    do { \
        (_hdr_p)->packet_length = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.packet_length[14;0] */

#define PIF_HEADER_GET_standard_metadata___egress_instance(_hdr_p) (((_hdr_p)->egress_instance)) /* standard_metadata.egress_instance [10;0] */

#define PIF_HEADER_SET_standard_metadata___egress_instance(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_instance = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.egress_instance[10;0] */

#define PIF_HEADER_GET_standard_metadata___instance_type(_hdr_p) (((_hdr_p)->instance_type)) /* standard_metadata.instance_type [4;0] */

#define PIF_HEADER_SET_standard_metadata___instance_type(_hdr_p, _val) \
    do { \
        (_hdr_p)->instance_type = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.instance_type[4;0] */

#define PIF_HEADER_GET_standard_metadata____padding_0(_hdr_p) (((_hdr_p)->_padding_0)) /* standard_metadata._padding_0 [4;0] */

#define PIF_HEADER_SET_standard_metadata____padding_0(_hdr_p, _val) \
    do { \
        (_hdr_p)->_padding_0 = (unsigned)(((_val))); \
    } while (0) /* standard_metadata._padding_0[4;0] */

#define PIF_HEADER_GET_standard_metadata___ingress_port(_hdr_p) (((_hdr_p)->ingress_port)) /* standard_metadata.ingress_port [10;0] */

#define PIF_HEADER_SET_standard_metadata___ingress_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->ingress_port = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.ingress_port[10;0] */

#define PIF_HEADER_GET_standard_metadata____padding_1(_hdr_p) (((_hdr_p)->_padding_1)) /* standard_metadata._padding_1 [22;0] */

#define PIF_HEADER_SET_standard_metadata____padding_1(_hdr_p, _val) \
    do { \
        (_hdr_p)->_padding_1 = (unsigned)(((_val))); \
    } while (0) /* standard_metadata._padding_1[22;0] */



/*
 * Registers
 */

#endif /* __PIF_HEADERS_H__ */
