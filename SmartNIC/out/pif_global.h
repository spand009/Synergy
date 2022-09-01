/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_GLOBAL_H__
#define __PIF_GLOBAL_H__

#define PIF_GLOBAL_FLOWKEY_MAX_LW 8
__packed_bits struct pif_global_flowkey_metadata {
    unsigned int standard_metadata__ingress_port:10;
    unsigned int __padding:22;
};

__packed_bits struct pif_global_flowkey_parse_ipv4 {
    unsigned int ipv4__srcAddr:32;
    unsigned int ipv4__dstAddr:32;
};

__packed_bits struct pif_global_flowkey_parse_gtpu {
    unsigned int gtpu__teid:32;
};

__packed_bits struct pif_global_flowkey_parse_gtpu_ipv4 {
    unsigned int gtpu_ipv4__dstAddr:32;
    unsigned int gtpu_ipv4__srcAddr:32;
    unsigned int gtpu_ipv4__diffserv:8;
    unsigned int __padding:24;
};


void pif_global_metadata_init(__lmem uint32_t *parrep);

unsigned int pif_global_get_stdmd_egress_spec(__lmem uint32_t *parrep);
unsigned int pif_global_get_stdmd_egress_port(__lmem uint32_t *parrep);
void pif_global_set_stdmd_egress_port(__lmem uint32_t *parrep, unsigned int port_spec);
void pif_global_set_stdmd_instance_type(__lmem uint32_t *parrep, unsigned int instance_type);
void pif_global_set_stdmd_egress_instance(__lmem uint32_t *parrep, unsigned int egress_instance);

#endif /* __PIF_GLOBAL_H__ */
