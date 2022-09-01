/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2014-2019 Broadcom
 * All rights reserved.
 */

#ifndef _ULP_FLOW_DB_H_
#define _ULP_FLOW_DB_H_

#include "bnxt_ulp.h"
#include "ulp_template_db.h"

#define BNXT_FLOW_DB_DEFAULT_NUM_FLOWS		128
#define BNXT_FLOW_DB_DEFAULT_NUM_RESOURCES	5

/* Structure for the flow database resource information. */
struct ulp_fdb_resource_info {
	/* Points to next resource in the chained list. */
	uint32_t	nxt_resource_idx;
	union {
		uint64_t	resource_em_handle;
		struct {
			uint32_t	resource_type;
			uint32_t	resource_hndl;
		};
	};
};

/* Structure for the flow database resource information. */
struct bnxt_ulp_flow_tbl {
	/* Flow tbl is the resource object list for each flow id. */
	struct ulp_fdb_resource_info	*flow_resources;

	/* Flow table stack to track free list of resources. */
	uint32_t	*flow_tbl_stack;
	uint32_t	head_index;
	uint32_t	tail_index;

	/* Table to track the active flows. */
	uint64_t	*active_flow_tbl;
	uint32_t	num_flows;
	uint32_t	num_resources;
};

/* Flow database supports two tables. */
enum bnxt_ulp_flow_db_tables {
	BNXT_ULP_REGULAR_FLOW_TABLE,
	BNXT_ULP_DEFAULT_FLOW_TABLE,
	BNXT_ULP_FLOW_TABLE_MAX
};

/* Structure for the flow database resource information. */
struct bnxt_ulp_flow_db {
	struct bnxt_ulp_flow_tbl	flow_tbl[BNXT_ULP_FLOW_TABLE_MAX];
	uint16_t			*func_id_tbl;
	uint32_t			func_id_tbl_size;
};

/* flow db resource params to add resources */
struct ulp_flow_db_res_params {
	enum tf_dir			direction;
	enum bnxt_ulp_resource_func	resource_func;
	uint64_t			resource_hndl;
	uint32_t			resource_type;
	uint32_t			critical_resource;
};

/*
 * Initialize the flow database. Memory is allocated in this
 * call and assigned to the flow database.
 *
 * ulp_ctxt [in] Ptr to ulp context
 *
 * Returns 0 on success or negative number on failure.
 */
int32_t	ulp_flow_db_init(struct bnxt_ulp_context *ulp_ctxt);

/*
 * Deinitialize the flow database. Memory is deallocated in
 * this call and all flows should have been purged before this
 * call.
 *
 * ulp_ctxt [in] Ptr to ulp context
 *
 * Returns 0 on success.
 */
int32_t	ulp_flow_db_deinit(struct bnxt_ulp_context *ulp_ctxt);

/*
 * Allocate the flow database entry
 *
 * ulp_ctxt [in] Ptr to ulp_context
 * tbl_idx [in] Specify it is regular or default flow
 * func_id [in] The function id of the device.Valid only for regular flows.
 * fid [out] The index to the flow entry
 *
 * returns 0 on success and negative on failure.
 */
int32_t ulp_flow_db_fid_alloc(struct bnxt_ulp_context *ulp_ctxt,
			      enum bnxt_ulp_flow_db_tables tbl_idx,
			      uint16_t func_id,
			      uint32_t *fid);

/*
 * Allocate the flow database entry.
 * The params->critical_resource has to be set to 0 to allocate a new resource.
 *
 * ulp_ctxt [in] Ptr to ulp_context
 * tbl_idx [in] Specify it is regular or default flow
 * fid [in] The index to the flow entry
 * params [in] The contents to be copied into resource
 *
 * returns 0 on success and negative on failure.
 */
int32_t	ulp_flow_db_resource_add(struct bnxt_ulp_context	*ulp_ctxt,
				 enum bnxt_ulp_flow_db_tables	tbl_idx,
				 uint32_t			fid,
				 struct ulp_flow_db_res_params	*params);

/*
 * Free the flow database entry.
 * The params->critical_resource has to be set to 1 to free the first resource.
 *
 * ulp_ctxt [in] Ptr to ulp_context
 * tbl_idx [in] Specify it is regular or default flow
 * fid [in] The index to the flow entry
 * params [in/out] The contents to be copied into params.
 * Only the critical_resource needs to be set by the caller.
 *
 * Returns 0 on success and negative on failure.
 */
int32_t	ulp_flow_db_resource_del(struct bnxt_ulp_context	*ulp_ctxt,
				 enum bnxt_ulp_flow_db_tables	tbl_idx,
				 uint32_t			fid,
				 struct ulp_flow_db_res_params	*params);

/*
 * Free the flow database entry
 *
 * ulp_ctxt [in] Ptr to ulp_context
 * tbl_idx [in] Specify it is regular or default flow
 * fid [in] The index to the flow entry
 *
 * returns 0 on success and negative on failure.
 */
int32_t	ulp_flow_db_fid_free(struct bnxt_ulp_context		*ulp_ctxt,
			     enum bnxt_ulp_flow_db_tables	tbl_idx,
			     uint32_t				fid);

/*
 *Get the flow database entry details
 *
 * ulp_ctxt [in] Ptr to ulp_context
 * tbl_idx [in] Specify it is regular or default flow
 * fid [in] The index to the flow entry
 * nxt_idx [in/out] the index to the next entry
 * params [out] The contents to be copied into params.
 *
 * returns 0 on success and negative on failure.
 */
int32_t	ulp_flow_db_resource_get(struct bnxt_ulp_context	*ulp_ctxt,
				 enum bnxt_ulp_flow_db_tables	tbl_idx,
				 uint32_t			fid,
				 uint32_t			*nxt_idx,
				 struct ulp_flow_db_res_params	*params);

/*
 * Flush all flows in the flow database.
 *
 * ulp_ctxt [in] Ptr to ulp context
 * tbl_idx [in] The index to table
 *
 * returns 0 on success or negative number on failure
 */
int32_t	ulp_flow_db_flush_flows(struct bnxt_ulp_context *ulp_ctx,
				uint32_t		idx);

/*
 * Flush all flows in the flow database that belong to a device function.
 *
 * ulp_ctxt [in] Ptr to ulp context
 * tbl_idx [in] The index to table
 *
 * returns 0 on success or negative number on failure
 */
int32_t
ulp_flow_db_function_flow_flush(struct bnxt_ulp_context *ulp_ctx,
				uint16_t func_id);

/*
 * Flush all flows in the flow database that are associated with the session.
 *
 * ulp_ctxt [in] Ptr to ulp context
 *
 * returns 0 on success or negative number on failure
 */
int32_t
ulp_flow_db_session_flow_flush(struct bnxt_ulp_context *ulp_ctx);

/*
 * Check that flow id matches the function id or not
 *
 * ulp_ctxt [in] Ptr to ulp context
 * flow_db [in] Ptr to flow table
 * func_id [in] The func_id to be set, for reset pass zero.
 *
 * returns true on success or false on failure
 */
bool
ulp_flow_db_validate_flow_func(struct bnxt_ulp_context *ulp_ctx,
			       uint32_t flow_id,
			       uint32_t func_id);

#endif /* _ULP_FLOW_DB_H_ */
