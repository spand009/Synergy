/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_H__
#define __PIF_PLUGIN_H__

/* This file is generate, edit at your peril */

#include <stdint.h>
#include <nfp.h>

#define EXTRACTED_HEADERS_T __lmem uint32_t
#define MATCH_DATA_T __xread uint32_t
#define ACTION_DATA_T __xread uint32_t

#define PIF_PLUGIN_RETURN_DROP -1
#define PIF_PLUGIN_RETURN_FORWARD 0

#include "pif_plugin_metadata.h"
#ifdef PIF_PLUGIN_INIT
void pif_plugin_init(); /* called once per worker thread */
void pif_plugin_init_master(); /* called once system wide */
#endif /* PIF_PLUGIN_INIT */
#include "pif_plugin_udp.h"
#include "pif_plugin_gtpu_ipv4.h"
#include "pif_plugin_gtpu.h"
#include "pif_plugin_tcp.h"
#include "pif_plugin_ipv4.h"
#include "pif_plugin_ethernet.h"

#endif /* __PIF_PLUGIN_H__ */
