/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2001-2020 Intel Corporation
 */

#include "ice_common.h"

/**
 * ice_aq_read_nvm
 * @hw: pointer to the HW struct
 * @module_typeid: module pointer location in words from the NVM beginning
 * @offset: byte offset from the module beginning
 * @length: length of the section to be read (in bytes from the offset)
 * @data: command buffer (size [bytes] = length)
 * @last_command: tells if this is the last command in a series
 * @read_shadow_ram: tell if this is a shadow RAM read
 * @cd: pointer to command details structure or NULL
 *
 * Read the NVM using the admin queue commands (0x0701)
 */
static enum ice_status
ice_aq_read_nvm(struct ice_hw *hw, u16 module_typeid, u32 offset, u16 length,
		void *data, bool last_command, bool read_shadow_ram,
		struct ice_sq_cd *cd)
{
	struct ice_aq_desc desc;
	struct ice_aqc_nvm *cmd;

	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	cmd = &desc.params.nvm;

	if (offset > ICE_AQC_NVM_MAX_OFFSET)
		return ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_read);

	if (!read_shadow_ram && module_typeid == ICE_AQC_NVM_START_POINT)
		cmd->cmd_flags |= ICE_AQC_NVM_FLASH_ONLY;

	/* If this is the last command in a series, set the proper flag. */
	if (last_command)
		cmd->cmd_flags |= ICE_AQC_NVM_LAST_CMD;
	cmd->module_typeid = CPU_TO_LE16(module_typeid);
	cmd->offset_low = CPU_TO_LE16(offset & 0xFFFF);
	cmd->offset_high = (offset >> 16) & 0xFF;
	cmd->length = CPU_TO_LE16(length);

	return ice_aq_send_cmd(hw, &desc, data, length, cd);
}

/**
 * ice_read_flat_nvm - Read portion of NVM by flat offset
 * @hw: pointer to the HW struct
 * @offset: offset from beginning of NVM
 * @length: (in) number of bytes to read; (out) number of bytes actually read
 * @data: buffer to return data in (sized to fit the specified length)
 * @read_shadow_ram: if true, read from shadow RAM instead of NVM
 *
 * Reads a portion of the NVM, as a flat memory space. This function correctly
 * breaks read requests across Shadow RAM sectors and ensures that no single
 * read request exceeds the maximum 4Kb read for a single AdminQ command.
 *
 * Returns a status code on failure. Note that the data pointer may be
 * partially updated if some reads succeed before a failure.
 */
enum ice_status
ice_read_flat_nvm(struct ice_hw *hw, u32 offset, u32 *length, u8 *data,
		  bool read_shadow_ram)
{
	enum ice_status status;
	u32 inlen = *length;
	u32 bytes_read = 0;
	bool last_cmd;

	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	*length = 0;

	/* Verify the length of the read if this is for the Shadow RAM */
	if (read_shadow_ram && ((offset + inlen) > (hw->nvm.sr_words * 2u))) {
		ice_debug(hw, ICE_DBG_NVM,
			  "NVM error: requested data is beyond Shadow RAM limit\n");
		return ICE_ERR_PARAM;
	}

	do {
		u32 read_size, sector_offset;

		/* ice_aq_read_nvm cannot read more than 4Kb at a time.
		 * Additionally, a read from the Shadow RAM may not cross over
		 * a sector boundary. Conveniently, the sector size is also
		 * 4Kb.
		 */
		sector_offset = offset % ICE_AQ_MAX_BUF_LEN;
		read_size = MIN_T(u32, ICE_AQ_MAX_BUF_LEN - sector_offset,
				  inlen - bytes_read);

		last_cmd = !(bytes_read + read_size < inlen);

		/* ice_aq_read_nvm takes the length as a u16. Our read_size is
		 * calculated using a u32, but the ICE_AQ_MAX_BUF_LEN maximum
		 * size guarantees that it will fit within the 2 bytes.
		 */
		status = ice_aq_read_nvm(hw, ICE_AQC_NVM_START_POINT,
					 offset, (u16)read_size,
					 data + bytes_read, last_cmd,
					 read_shadow_ram, NULL);
		if (status)
			break;

		bytes_read += read_size;
		offset += read_size;
	} while (!last_cmd);

	*length = bytes_read;
	return status;
}

/**
 * ice_read_sr_word_aq - Reads Shadow RAM via AQ
 * @hw: pointer to the HW structure
 * @offset: offset of the Shadow RAM word to read (0x000000 - 0x001FFF)
 * @data: word read from the Shadow RAM
 *
 * Reads one 16 bit word from the Shadow RAM using ice_read_flat_nvm.
 */
static enum ice_status
ice_read_sr_word_aq(struct ice_hw *hw, u16 offset, u16 *data)
{
	u32 bytes = sizeof(u16);
	enum ice_status status;
	__le16 data_local;

	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	/* Note that ice_read_flat_nvm checks if the read is past the Shadow
	 * RAM size, and ensures we don't read across a Shadow RAM sector
	 * boundary
	 */
	status = ice_read_flat_nvm(hw, offset * sizeof(u16), &bytes,
				   (u8 *)&data_local, true);
	if (status)
		return status;

	*data = LE16_TO_CPU(data_local);
	return ICE_SUCCESS;
}

/**
 * ice_read_sr_buf_aq - Reads Shadow RAM buf via AQ
 * @hw: pointer to the HW structure
 * @offset: offset of the Shadow RAM word to read (0x000000 - 0x001FFF)
 * @words: (in) number of words to read; (out) number of words actually read
 * @data: words read from the Shadow RAM
 *
 * Reads 16 bit words (data buf) from the Shadow RAM. Ownership of the NVM is
 * taken before reading the buffer and later released.
 */
static enum ice_status
ice_read_sr_buf_aq(struct ice_hw *hw, u16 offset, u16 *words, u16 *data)
{
	u32 bytes = *words * 2, i;
	enum ice_status status;

	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	/* ice_read_flat_nvm takes into account the 4Kb AdminQ and Shadow RAM
	 * sector restrictions necessary when reading from the NVM.
	 */
	status = ice_read_flat_nvm(hw, offset * 2, &bytes, (u8 *)data, true);

	/* Report the number of words successfully read */
	*words = bytes / 2;

	/* Byte swap the words up to the amount we actually read */
	for (i = 0; i < *words; i++)
		data[i] = LE16_TO_CPU(((_FORCE_ __le16 *)data)[i]);

	return status;
}

/**
 * ice_acquire_nvm - Generic request for acquiring the NVM ownership
 * @hw: pointer to the HW structure
 * @access: NVM access type (read or write)
 *
 * This function will request NVM ownership.
 */
static enum ice_status
ice_acquire_nvm(struct ice_hw *hw, enum ice_aq_res_access_type access)
{
	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	if (hw->nvm.blank_nvm_mode)
		return ICE_SUCCESS;

	return ice_acquire_res(hw, ICE_NVM_RES_ID, access, ICE_NVM_TIMEOUT);
}

/**
 * ice_release_nvm - Generic request for releasing the NVM ownership
 * @hw: pointer to the HW structure
 *
 * This function will release NVM ownership.
 */
static void ice_release_nvm(struct ice_hw *hw)
{
	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	if (hw->nvm.blank_nvm_mode)
		return;

	ice_release_res(hw, ICE_NVM_RES_ID);
}

/**
 * ice_read_sr_word - Reads Shadow RAM word and acquire NVM if necessary
 * @hw: pointer to the HW structure
 * @offset: offset of the Shadow RAM word to read (0x000000 - 0x001FFF)
 * @data: word read from the Shadow RAM
 *
 * Reads one 16 bit word from the Shadow RAM using the ice_read_sr_word_aq.
 */
enum ice_status ice_read_sr_word(struct ice_hw *hw, u16 offset, u16 *data)
{
	enum ice_status status;

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	if (!status) {
		status = ice_read_sr_word_aq(hw, offset, data);
		ice_release_nvm(hw);
	}

	return status;
}

/**
 * ice_get_pfa_module_tlv - Reads sub module TLV from NVM PFA
 * @hw: pointer to hardware structure
 * @module_tlv: pointer to module TLV to return
 * @module_tlv_len: pointer to module TLV length to return
 * @module_type: module type requested
 *
 * Finds the requested sub module TLV type from the Preserved Field
 * Area (PFA) and returns the TLV pointer and length. The caller can
 * use these to read the variable length TLV value.
 */
enum ice_status
ice_get_pfa_module_tlv(struct ice_hw *hw, u16 *module_tlv, u16 *module_tlv_len,
		       u16 module_type)
{
	enum ice_status status;
	u16 pfa_len, pfa_ptr;
	u16 next_tlv;

	status = ice_read_sr_word(hw, ICE_SR_PFA_PTR, &pfa_ptr);
	if (status != ICE_SUCCESS) {
		ice_debug(hw, ICE_DBG_INIT, "Preserved Field Array pointer.\n");
		return status;
	}
	status = ice_read_sr_word(hw, pfa_ptr, &pfa_len);
	if (status != ICE_SUCCESS) {
		ice_debug(hw, ICE_DBG_INIT, "Failed to read PFA length.\n");
		return status;
	}
	/* Starting with first TLV after PFA length, iterate through the list
	 * of TLVs to find the requested one.
	 */
	next_tlv = pfa_ptr + 1;
	while (next_tlv < pfa_ptr + pfa_len) {
		u16 tlv_sub_module_type;
		u16 tlv_len;

		/* Read TLV type */
		status = ice_read_sr_word(hw, next_tlv, &tlv_sub_module_type);
		if (status != ICE_SUCCESS) {
			ice_debug(hw, ICE_DBG_INIT, "Failed to read TLV type.\n");
			break;
		}
		/* Read TLV length */
		status = ice_read_sr_word(hw, next_tlv + 1, &tlv_len);
		if (status != ICE_SUCCESS) {
			ice_debug(hw, ICE_DBG_INIT, "Failed to read TLV length.\n");
			break;
		}
		if (tlv_sub_module_type == module_type) {
			if (tlv_len) {
				*module_tlv = next_tlv;
				*module_tlv_len = tlv_len;
				return ICE_SUCCESS;
			}
			return ICE_ERR_INVAL_SIZE;
		}
		/* Check next TLV, i.e. current TLV pointer + length + 2 words
		 * (for current TLV's type and length)
		 */
		next_tlv = next_tlv + tlv_len + 2;
	}
	/* Module does not exist */
	return ICE_ERR_DOES_NOT_EXIST;
}

/**
 * ice_get_orom_ver_info - Read Option ROM version information
 * @hw: pointer to the HW struct
 *
 * Read the Combo Image version data from the Boot Configuration TLV and fill
 * in the option ROM version data.
 */
static enum ice_status ice_get_orom_ver_info(struct ice_hw *hw)
{
	u16 combo_hi, combo_lo, boot_cfg_tlv, boot_cfg_tlv_len;
	struct ice_orom_info *orom = &hw->nvm.orom;
	enum ice_status status;
	u32 combo_ver;

	status = ice_get_pfa_module_tlv(hw, &boot_cfg_tlv, &boot_cfg_tlv_len,
					ICE_SR_BOOT_CFG_PTR);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT,
			  "Failed to read Boot Configuration Block TLV.\n");
		return status;
	}

	/* Boot Configuration Block must have length at least 2 words
	 * (Combo Image Version High and Combo Image Version Low)
	 */
	if (boot_cfg_tlv_len < 2) {
		ice_debug(hw, ICE_DBG_INIT,
			  "Invalid Boot Configuration Block TLV size.\n");
		return ICE_ERR_INVAL_SIZE;
	}

	status = ice_read_sr_word(hw, (boot_cfg_tlv + ICE_NVM_OROM_VER_OFF),
				  &combo_hi);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Failed to read OROM_VER hi.\n");
		return status;
	}

	status = ice_read_sr_word(hw, (boot_cfg_tlv + ICE_NVM_OROM_VER_OFF + 1),
				  &combo_lo);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Failed to read OROM_VER lo.\n");
		return status;
	}

	combo_ver = ((u32)combo_hi << 16) | combo_lo;

	orom->major = (u8)((combo_ver & ICE_OROM_VER_MASK) >>
			   ICE_OROM_VER_SHIFT);
	orom->patch = (u8)(combo_ver & ICE_OROM_VER_PATCH_MASK);
	orom->build = (u16)((combo_ver & ICE_OROM_VER_BUILD_MASK) >>
			    ICE_OROM_VER_BUILD_SHIFT);

	return ICE_SUCCESS;
}

/**
 * ice_discover_flash_size - Discover the available flash size.
 * @hw: pointer to the HW struct
 *
 * The device flash could be up to 16MB in size. However, it is possible that
 * the actual size is smaller. Use bisection to determine the accessible size
 * of flash memory.
 */
static enum ice_status ice_discover_flash_size(struct ice_hw *hw)
{
	u32 min_size = 0, max_size = ICE_AQC_NVM_MAX_OFFSET + 1;
	enum ice_status status;

	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	if (status)
		return status;

	while ((max_size - min_size) > 1) {
		u32 offset = (max_size + min_size) / 2;
		u32 len = 1;
		u8 data;

		status = ice_read_flat_nvm(hw, offset, &len, &data, false);
		if (status == ICE_ERR_AQ_ERROR &&
		    hw->adminq.sq_last_status == ICE_AQ_RC_EINVAL) {
			ice_debug(hw, ICE_DBG_NVM,
				  "%s: New upper bound of %u bytes\n",
				  __func__, offset);
			status = ICE_SUCCESS;
			max_size = offset;
		} else if (!status) {
			ice_debug(hw, ICE_DBG_NVM,
				  "%s: New lower bound of %u bytes\n",
				  __func__, offset);
			min_size = offset;
		} else {
			/* an unexpected error occurred */
			goto err_read_flat_nvm;
		}
	}

	ice_debug(hw, ICE_DBG_NVM,
		  "Predicted flash size is %u bytes\n", max_size);

	hw->nvm.flash_size = max_size;

err_read_flat_nvm:
	ice_release_nvm(hw);

	return status;
}

/**
 * ice_init_nvm - initializes NVM setting
 * @hw: pointer to the HW struct
 *
 * This function reads and populates NVM settings such as Shadow RAM size,
 * max_timeout, and blank_nvm_mode
 */
enum ice_status ice_init_nvm(struct ice_hw *hw)
{
	struct ice_nvm_info *nvm = &hw->nvm;
	u16 eetrack_lo, eetrack_hi, ver;
	enum ice_status status;
	u32 fla, gens_stat;
	u8 sr_size;

	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	/* The SR size is stored regardless of the NVM programming mode
	 * as the blank mode may be used in the factory line.
	 */
	gens_stat = rd32(hw, GLNVM_GENS);
	sr_size = (gens_stat & GLNVM_GENS_SR_SIZE_M) >> GLNVM_GENS_SR_SIZE_S;

	/* Switching to words (sr_size contains power of 2) */
	nvm->sr_words = BIT(sr_size) * ICE_SR_WORDS_IN_1KB;

	/* Check if we are in the normal or blank NVM programming mode */
	fla = rd32(hw, GLNVM_FLA);
	if (fla & GLNVM_FLA_LOCKED_M) { /* Normal programming mode */
		nvm->blank_nvm_mode = false;
	} else {
		/* Blank programming mode */
		nvm->blank_nvm_mode = true;
		ice_debug(hw, ICE_DBG_NVM,
			  "NVM init error: unsupported blank mode.\n");
		return ICE_ERR_NVM_BLANK_MODE;
	}

	status = ice_read_sr_word(hw, ICE_SR_NVM_DEV_STARTER_VER, &ver);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT,
			  "Failed to read DEV starter version.\n");
		return status;
	}
	nvm->major_ver = (ver & ICE_NVM_VER_HI_MASK) >> ICE_NVM_VER_HI_SHIFT;
	nvm->minor_ver = (ver & ICE_NVM_VER_LO_MASK) >> ICE_NVM_VER_LO_SHIFT;

	status = ice_read_sr_word(hw, ICE_SR_NVM_EETRACK_LO, &eetrack_lo);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Failed to read EETRACK lo.\n");
		return status;
	}
	status = ice_read_sr_word(hw, ICE_SR_NVM_EETRACK_HI, &eetrack_hi);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Failed to read EETRACK hi.\n");
		return status;
	}

	nvm->eetrack = (eetrack_hi << 16) | eetrack_lo;

	status = ice_discover_flash_size(hw);
	if (status) {
		ice_debug(hw, ICE_DBG_NVM,
			  "NVM init error: failed to discover flash size.\n");
		return status;
	}

	switch (hw->device_id) {
	/* the following devices do not have boot_cfg_tlv yet */
	case ICE_DEV_ID_E822C_BACKPLANE:
	case ICE_DEV_ID_E822C_QSFP:
	case ICE_DEV_ID_E822C_10G_BASE_T:
	case ICE_DEV_ID_E822C_SGMII:
	case ICE_DEV_ID_E822C_SFP:
	case ICE_DEV_ID_E822L_BACKPLANE:
	case ICE_DEV_ID_E822L_SFP:
	case ICE_DEV_ID_E822L_10G_BASE_T:
	case ICE_DEV_ID_E822L_SGMII:
		return status;
	default:
		break;
	}

	status = ice_get_orom_ver_info(hw);
	if (status) {
		ice_debug(hw, ICE_DBG_INIT, "Failed to read Option ROM info.\n");
		return status;
	}

	return ICE_SUCCESS;
}

/**
 * ice_read_sr_buf - Reads Shadow RAM buf and acquire lock if necessary
 * @hw: pointer to the HW structure
 * @offset: offset of the Shadow RAM word to read (0x000000 - 0x001FFF)
 * @words: (in) number of words to read; (out) number of words actually read
 * @data: words read from the Shadow RAM
 *
 * Reads 16 bit words (data buf) from the SR using the ice_read_nvm_buf_aq
 * method. The buf read is preceded by the NVM ownership take
 * and followed by the release.
 */
enum ice_status
ice_read_sr_buf(struct ice_hw *hw, u16 offset, u16 *words, u16 *data)
{
	enum ice_status status;

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	if (!status) {
		status = ice_read_sr_buf_aq(hw, offset, words, data);
		ice_release_nvm(hw);
	}

	return status;
}

/**
 * ice_nvm_validate_checksum
 * @hw: pointer to the HW struct
 *
 * Verify NVM PFA checksum validity (0x0706)
 */
enum ice_status ice_nvm_validate_checksum(struct ice_hw *hw)
{
	struct ice_aqc_nvm_checksum *cmd;
	struct ice_aq_desc desc;
	enum ice_status status;

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	if (status)
		return status;

	cmd = &desc.params.nvm_checksum;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_checksum);
	cmd->flags = ICE_AQC_NVM_CHECKSUM_VERIFY;

	status = ice_aq_send_cmd(hw, &desc, NULL, 0, NULL);
	ice_release_nvm(hw);

	if (!status)
		if (LE16_TO_CPU(cmd->checksum) != ICE_AQC_NVM_CHECKSUM_CORRECT)
			status = ICE_ERR_NVM_CHECKSUM;

	return status;
}

/**
 * ice_nvm_access_get_features - Return the NVM access features structure
 * @cmd: NVM access command to process
 * @data: storage for the driver NVM features
 *
 * Fill in the data section of the NVM access request with a copy of the NVM
 * features structure.
 */
enum ice_status
ice_nvm_access_get_features(struct ice_nvm_access_cmd *cmd,
			    union ice_nvm_access_data *data)
{
	/* The provided data_size must be at least as large as our NVM
	 * features structure. A larger size should not be treated as an
	 * error, to allow future extensions to to the features structure to
	 * work on older drivers.
	 */
	if (cmd->data_size < sizeof(struct ice_nvm_features))
		return ICE_ERR_NO_MEMORY;

	/* Initialize the data buffer to zeros */
	ice_memset(data, 0, cmd->data_size, ICE_NONDMA_MEM);

	/* Fill in the features data */
	data->drv_features.major = ICE_NVM_ACCESS_MAJOR_VER;
	data->drv_features.minor = ICE_NVM_ACCESS_MINOR_VER;
	data->drv_features.size = sizeof(struct ice_nvm_features);
	data->drv_features.features[0] = ICE_NVM_FEATURES_0_REG_ACCESS;

	return ICE_SUCCESS;
}

/**
 * ice_nvm_access_get_module - Helper function to read module value
 * @cmd: NVM access command structure
 *
 * Reads the module value out of the NVM access config field.
 */
u32 ice_nvm_access_get_module(struct ice_nvm_access_cmd *cmd)
{
	return ((cmd->config & ICE_NVM_CFG_MODULE_M) >> ICE_NVM_CFG_MODULE_S);
}

/**
 * ice_nvm_access_get_flags - Helper function to read flags value
 * @cmd: NVM access command structure
 *
 * Reads the flags value out of the NVM access config field.
 */
u32 ice_nvm_access_get_flags(struct ice_nvm_access_cmd *cmd)
{
	return ((cmd->config & ICE_NVM_CFG_FLAGS_M) >> ICE_NVM_CFG_FLAGS_S);
}

/**
 * ice_nvm_access_get_adapter - Helper function to read adapter info
 * @cmd: NVM access command structure
 *
 * Read the adapter info value out of the NVM access config field.
 */
u32 ice_nvm_access_get_adapter(struct ice_nvm_access_cmd *cmd)
{
	return ((cmd->config & ICE_NVM_CFG_ADAPTER_INFO_M) >>
		ICE_NVM_CFG_ADAPTER_INFO_S);
}

/**
 * ice_validate_nvm_rw_reg - Check than an NVM access request is valid
 * @cmd: NVM access command structure
 *
 * Validates that an NVM access structure is request to read or write a valid
 * register offset. First validates that the module and flags are correct, and
 * then ensures that the register offset is one of the accepted registers.
 */
static enum ice_status
ice_validate_nvm_rw_reg(struct ice_nvm_access_cmd *cmd)
{
	u32 module, flags, offset;
	u16 i;

	module = ice_nvm_access_get_module(cmd);
	flags = ice_nvm_access_get_flags(cmd);
	offset = cmd->offset;

	/* Make sure the module and flags indicate a read/write request */
	if (module != ICE_NVM_REG_RW_MODULE ||
	    flags != ICE_NVM_REG_RW_FLAGS ||
	    cmd->data_size != FIELD_SIZEOF(union ice_nvm_access_data, regval))
		return ICE_ERR_PARAM;

	switch (offset) {
	case GL_HICR:
	case GL_HICR_EN: /* Note, this register is read only */
	case GL_FWSTS:
	case GL_MNG_FWSM:
	case GLGEN_CSR_DEBUG_C:
	case GLGEN_RSTAT:
	case GLPCI_LBARCTRL:
	case GLNVM_GENS:
	case GLNVM_FLA:
	case PF_FUNC_RID:
		return ICE_SUCCESS;
	default:
		break;
	}

	for (i = 0; i <= ICE_NVM_ACCESS_GL_HIDA_MAX; i++)
		if (offset == (u32)GL_HIDA(i))
			return ICE_SUCCESS;

	for (i = 0; i <= ICE_NVM_ACCESS_GL_HIBA_MAX; i++)
		if (offset == (u32)GL_HIBA(i))
			return ICE_SUCCESS;

	/* All other register offsets are not valid */
	return ICE_ERR_OUT_OF_RANGE;
}

/**
 * ice_nvm_access_read - Handle an NVM read request
 * @hw: pointer to the HW struct
 * @cmd: NVM access command to process
 * @data: storage for the register value read
 *
 * Process an NVM access request to read a register.
 */
enum ice_status
ice_nvm_access_read(struct ice_hw *hw, struct ice_nvm_access_cmd *cmd,
		    union ice_nvm_access_data *data)
{
	enum ice_status status;

	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	/* Always initialize the output data, even on failure */
	ice_memset(data, 0, cmd->data_size, ICE_NONDMA_MEM);

	/* Make sure this is a valid read/write access request */
	status = ice_validate_nvm_rw_reg(cmd);
	if (status)
		return status;

	ice_debug(hw, ICE_DBG_NVM, "NVM access: reading register %08x\n",
		  cmd->offset);

	/* Read the register and store the contents in the data field */
	data->regval = rd32(hw, cmd->offset);

	return ICE_SUCCESS;
}

/**
 * ice_nvm_access_write - Handle an NVM write request
 * @hw: pointer to the HW struct
 * @cmd: NVM access command to process
 * @data: NVM access data to write
 *
 * Process an NVM access request to write a register.
 */
enum ice_status
ice_nvm_access_write(struct ice_hw *hw, struct ice_nvm_access_cmd *cmd,
		     union ice_nvm_access_data *data)
{
	enum ice_status status;

	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	/* Make sure this is a valid read/write access request */
	status = ice_validate_nvm_rw_reg(cmd);
	if (status)
		return status;

	/* Reject requests to write to read-only registers */
	switch (cmd->offset) {
	case GL_HICR_EN:
	case GLGEN_RSTAT:
		return ICE_ERR_OUT_OF_RANGE;
	default:
		break;
	}

	ice_debug(hw, ICE_DBG_NVM,
		  "NVM access: writing register %08x with value %08x\n",
		  cmd->offset, data->regval);

	/* Write the data field to the specified register */
	wr32(hw, cmd->offset, data->regval);

	return ICE_SUCCESS;
}

/**
 * ice_handle_nvm_access - Handle an NVM access request
 * @hw: pointer to the HW struct
 * @cmd: NVM access command info
 * @data: pointer to read or return data
 *
 * Process an NVM access request. Read the command structure information and
 * determine if it is valid. If not, report an error indicating the command
 * was invalid.
 *
 * For valid commands, perform the necessary function, copying the data into
 * the provided data buffer.
 */
enum ice_status
ice_handle_nvm_access(struct ice_hw *hw, struct ice_nvm_access_cmd *cmd,
		      union ice_nvm_access_data *data)
{
	u32 module, flags, adapter_info;

	ice_debug(hw, ICE_DBG_TRACE, "%s\n", __func__);

	/* Extended flags are currently reserved and must be zero */
	if ((cmd->config & ICE_NVM_CFG_EXT_FLAGS_M) != 0)
		return ICE_ERR_PARAM;

	/* Adapter info must match the HW device ID */
	adapter_info = ice_nvm_access_get_adapter(cmd);
	if (adapter_info != hw->device_id)
		return ICE_ERR_PARAM;

	switch (cmd->command) {
	case ICE_NVM_CMD_READ:
		module = ice_nvm_access_get_module(cmd);
		flags = ice_nvm_access_get_flags(cmd);

		/* Getting the driver's NVM features structure shares the same
		 * command type as reading a register. Read the config field
		 * to determine if this is a request to get features.
		 */
		if (module == ICE_NVM_GET_FEATURES_MODULE &&
		    flags == ICE_NVM_GET_FEATURES_FLAGS &&
		    cmd->offset == 0)
			return ice_nvm_access_get_features(cmd, data);
		else
			return ice_nvm_access_read(hw, cmd, data);
	case ICE_NVM_CMD_WRITE:
		return ice_nvm_access_write(hw, cmd, data);
	default:
		return ICE_ERR_PARAM;
	}
}
