/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2019-2020 Broadcom
 * All rights reserved.
 */

#ifndef _BNXT_ULP_H_
#define _BNXT_ULP_H_

#include <inttypes.h>
#include <stdbool.h>
#include <sys/queue.h>

#include "rte_ethdev.h"

struct bnxt_ulp_data {
	uint32_t			tbl_scope_id;
	struct bnxt_ulp_mark_tbl	*mark_tbl;
	uint32_t			dev_id; /* Hardware device id */
	uint32_t			ref_cnt;
	struct bnxt_ulp_flow_db		*flow_db;
	void				*mapper_data;
	struct bnxt_ulp_port_db		*port_db;
};

struct bnxt_ulp_context {
	struct bnxt_ulp_data	*cfg_data;
	/* TBD The tfp should be removed once tf_attach is implemented. */
	struct tf		*g_tfp;
};

struct bnxt_ulp_pci_info {
	uint32_t	domain;
	uint8_t		bus;
};

struct bnxt_ulp_session_state {
	STAILQ_ENTRY(bnxt_ulp_session_state)	next;
	bool					bnxt_ulp_init;
	pthread_mutex_t				bnxt_ulp_mutex;
	struct bnxt_ulp_pci_info		pci_info;
	struct bnxt_ulp_data			*cfg_data;
	/* TBD The tfp should be removed once tf_attach is implemented. */
	struct tf				*g_tfp;
	uint32_t				session_opened;
};

/* ULP flow id structure */
struct rte_tf_flow {
	uint32_t	flow_id;
};

/*
 * Allow the deletion of context only for the bnxt device that
 * created the session
 * TBD - The implementation of the function should change to
 * using the reference count once tf_session_attach functionality
 * is fixed.
 */
bool
ulp_ctx_deinit_allowed(void *bp);

/* Function to set the device id of the hardware. */
int32_t
bnxt_ulp_cntxt_dev_id_set(struct bnxt_ulp_context *ulp_ctx, uint32_t dev_id);

/* Function to get the device id of the hardware. */
int32_t
bnxt_ulp_cntxt_dev_id_get(struct bnxt_ulp_context *ulp_ctx, uint32_t *dev_id);

/* Function to set the table scope id of the EEM table. */
int32_t
bnxt_ulp_cntxt_tbl_scope_id_set(struct bnxt_ulp_context *ulp_ctx,
				uint32_t tbl_scope_id);

/* Function to get the table scope id of the EEM table. */
int32_t
bnxt_ulp_cntxt_tbl_scope_id_get(struct bnxt_ulp_context *ulp_ctx,
				uint32_t *tbl_scope_id);

/* Function to set the tfp session details in the ulp context. */
int32_t
bnxt_ulp_cntxt_tfp_set(struct bnxt_ulp_context *ulp, struct tf *tfp);

/* Function to get the tfp session details from ulp context. */
struct tf *
bnxt_ulp_cntxt_tfp_get(struct bnxt_ulp_context *ulp);

/* Get the device table entry based on the device id. */
struct bnxt_ulp_device_params *
bnxt_ulp_device_params_get(uint32_t dev_id);

int32_t
bnxt_ulp_ctxt_ptr2_mark_db_set(struct bnxt_ulp_context *ulp_ctx,
			       struct bnxt_ulp_mark_tbl *mark_tbl);

struct bnxt_ulp_mark_tbl *
bnxt_ulp_ctxt_ptr2_mark_db_get(struct bnxt_ulp_context *ulp_ctx);

/* Function to set the flow database to the ulp context. */
int32_t
bnxt_ulp_cntxt_ptr2_flow_db_set(struct bnxt_ulp_context	*ulp_ctx,
				struct bnxt_ulp_flow_db	*flow_db);

/* Function to get the flow database from the ulp context. */
struct bnxt_ulp_flow_db	*
bnxt_ulp_cntxt_ptr2_flow_db_get(struct bnxt_ulp_context	*ulp_ctx);

/* Function to get the ulp context from eth device. */
struct bnxt_ulp_context	*
bnxt_ulp_eth_dev_ptr2_cntxt_get(struct rte_eth_dev *dev);

/* Function to add the ulp mapper data to the ulp context */
int32_t
bnxt_ulp_cntxt_ptr2_mapper_data_set(struct bnxt_ulp_context *ulp_ctx,
				    void *mapper_data);

/* Function to get the ulp mapper data from the ulp context */
void *
bnxt_ulp_cntxt_ptr2_mapper_data_get(struct bnxt_ulp_context *ulp_ctx);

/* Function to set the port database to the ulp context. */
int32_t
bnxt_ulp_cntxt_ptr2_port_db_set(struct bnxt_ulp_context	*ulp_ctx,
				struct bnxt_ulp_port_db	*port_db);

/* Function to get the port database from the ulp context. */
struct bnxt_ulp_port_db *
bnxt_ulp_cntxt_ptr2_port_db_get(struct bnxt_ulp_context	*ulp_ctx);

#endif /* _BNXT_ULP_H_ */
