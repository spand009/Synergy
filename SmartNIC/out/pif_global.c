/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <stdint.h>
#include <nfp/me.h>
#include <nfp/mem_bulk.h>
#include "pif_common.h"

#define PIF_EGRESS_DROP 0xffff
extern __forceinline void pif_global_metadata_init(__lmem uint32_t *parrep)
{
    __lmem struct pif_header_standard_metadata *standard_metadata = (__lmem struct pif_header_standard_metadata *)(parrep + PIF_PARREP_standard_metadata_OFF_LW);

    PIF_HEADER_SET_standard_metadata___egress_spec(standard_metadata, PIF_EGRESS_DROP);
    PIF_HEADER_SET_standard_metadata___packet_length(standard_metadata, pif_pkt_info_global.pkt_len);
    PIF_HEADER_SET_standard_metadata___ingress_port(standard_metadata, PIF_PKT_P4PORT(&pif_pkt_info_global));
    PIF_HEADER_SET_standard_metadata___instance_type(standard_metadata, 0);
    PIF_HEADER_SET_standard_metadata___egress_instance(standard_metadata, 0);
}

extern __forceinline unsigned int pif_global_get_stdmd_egress_spec(__lmem uint32_t *parrep)
{
    __lmem struct pif_header_standard_metadata *standard_metadata = (__lmem struct pif_header_standard_metadata *)(parrep + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___egress_spec(standard_metadata);
}

extern __forceinline unsigned int pif_global_get_stdmd_egress_port(__lmem uint32_t *parrep)
{
    __lmem struct pif_header_standard_metadata *standard_metadata = (__lmem struct pif_header_standard_metadata *)(parrep + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___egress_port(standard_metadata);
}

extern __forceinline void pif_global_set_stdmd_egress_port(__lmem uint32_t *parrep, unsigned int port_spec)
{
    __lmem struct pif_header_standard_metadata *standard_metadata = (__lmem struct pif_header_standard_metadata *)(parrep + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___egress_port(standard_metadata, port_spec);
}

extern __forceinline void pif_global_set_stdmd_instance_type(__lmem uint32_t *parrep, unsigned int instance_type)
{
    __lmem struct pif_header_standard_metadata *standard_metadata = (__lmem struct pif_header_standard_metadata *)(parrep + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___instance_type(standard_metadata, instance_type);
}

extern __forceinline void pif_global_set_stdmd_egress_instance(__lmem uint32_t *parrep, unsigned int egress_instance)
{
    __lmem struct pif_header_standard_metadata *standard_metadata = (__lmem struct pif_header_standard_metadata *)(parrep + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___egress_instance(standard_metadata, egress_instance);
}

