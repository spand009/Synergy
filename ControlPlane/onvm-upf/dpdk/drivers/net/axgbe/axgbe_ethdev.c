/*   SPDX-License-Identifier: BSD-3-Clause
 *   Copyright(c) 2018 Advanced Micro Devices, Inc. All rights reserved.
 *   Copyright(c) 2018 Synopsys, Inc. All rights reserved.
 */

#include "axgbe_rxtx.h"
#include "axgbe_ethdev.h"
#include "axgbe_common.h"
#include "axgbe_phy.h"
#include "axgbe_regs.h"

static int eth_axgbe_dev_init(struct rte_eth_dev *eth_dev);
static int eth_axgbe_dev_uninit(struct rte_eth_dev *eth_dev);
static int  axgbe_dev_configure(struct rte_eth_dev *dev);
static int  axgbe_dev_start(struct rte_eth_dev *dev);
static void axgbe_dev_stop(struct rte_eth_dev *dev);
static void axgbe_dev_interrupt_handler(void *param);
static void axgbe_dev_close(struct rte_eth_dev *dev);
static int axgbe_dev_promiscuous_enable(struct rte_eth_dev *dev);
static int axgbe_dev_promiscuous_disable(struct rte_eth_dev *dev);
static int axgbe_dev_allmulticast_enable(struct rte_eth_dev *dev);
static int axgbe_dev_allmulticast_disable(struct rte_eth_dev *dev);
static int axgbe_dev_mac_addr_set(struct rte_eth_dev *dev,
				  struct rte_ether_addr *mac_addr);
static int axgbe_dev_mac_addr_add(struct rte_eth_dev *dev,
				  struct rte_ether_addr *mac_addr,
				  uint32_t index,
				  uint32_t vmdq);
static void axgbe_dev_mac_addr_remove(struct rte_eth_dev *dev, uint32_t index);
static int axgbe_dev_set_mc_addr_list(struct rte_eth_dev *dev,
				      struct rte_ether_addr *mc_addr_set,
				      uint32_t nb_mc_addr);
static int axgbe_dev_uc_hash_table_set(struct rte_eth_dev *dev,
				       struct rte_ether_addr *mac_addr,
				       uint8_t add);
static int axgbe_dev_uc_all_hash_table_set(struct rte_eth_dev *dev,
					   uint8_t add);
static int axgbe_dev_link_update(struct rte_eth_dev *dev,
				 int wait_to_complete);
static int axgbe_dev_get_regs(struct rte_eth_dev *dev,
			      struct rte_dev_reg_info *regs);
static int axgbe_dev_stats_get(struct rte_eth_dev *dev,
				struct rte_eth_stats *stats);
static int axgbe_dev_stats_reset(struct rte_eth_dev *dev);
static int axgbe_dev_xstats_get(struct rte_eth_dev *dev,
				struct rte_eth_xstat *stats,
				unsigned int n);
static int
axgbe_dev_xstats_get_names(struct rte_eth_dev *dev,
			   struct rte_eth_xstat_name *xstats_names,
			   unsigned int size);
static int
axgbe_dev_xstats_get_by_id(struct rte_eth_dev *dev,
			   const uint64_t *ids,
			   uint64_t *values,
			   unsigned int n);
static int
axgbe_dev_xstats_get_names_by_id(struct rte_eth_dev *dev,
				 struct rte_eth_xstat_name *xstats_names,
				 const uint64_t *ids,
				 unsigned int size);
static int axgbe_dev_xstats_reset(struct rte_eth_dev *dev);
static int  axgbe_dev_info_get(struct rte_eth_dev *dev,
			       struct rte_eth_dev_info *dev_info);
static int axgbe_flow_ctrl_get(struct rte_eth_dev *dev,
				struct rte_eth_fc_conf *fc_conf);
static int axgbe_flow_ctrl_set(struct rte_eth_dev *dev,
				struct rte_eth_fc_conf *fc_conf);
static int axgbe_priority_flow_ctrl_set(struct rte_eth_dev *dev,
				struct rte_eth_pfc_conf *pfc_conf);
static void axgbe_rxq_info_get(struct rte_eth_dev *dev, uint16_t queue_id,
	struct rte_eth_rxq_info *qinfo);
static void axgbe_txq_info_get(struct rte_eth_dev *dev, uint16_t queue_id,
	struct rte_eth_txq_info *qinfo);
const uint32_t *axgbe_dev_supported_ptypes_get(struct rte_eth_dev *dev);

struct axgbe_xstats {
	char name[RTE_ETH_XSTATS_NAME_SIZE];
	int offset;
};

#define AXGMAC_MMC_STAT(_string, _var)                           \
	{ _string,                                              \
	  offsetof(struct axgbe_mmc_stats, _var),       \
	}

static const struct axgbe_xstats axgbe_xstats_strings[] = {
	AXGMAC_MMC_STAT("tx_bytes", txoctetcount_gb),
	AXGMAC_MMC_STAT("tx_packets", txframecount_gb),
	AXGMAC_MMC_STAT("tx_unicast_packets", txunicastframes_gb),
	AXGMAC_MMC_STAT("tx_broadcast_packets", txbroadcastframes_gb),
	AXGMAC_MMC_STAT("tx_multicast_packets", txmulticastframes_gb),
	AXGMAC_MMC_STAT("tx_vlan_packets", txvlanframes_g),
	AXGMAC_MMC_STAT("tx_64_byte_packets", tx64octets_gb),
	AXGMAC_MMC_STAT("tx_65_to_127_byte_packets", tx65to127octets_gb),
	AXGMAC_MMC_STAT("tx_128_to_255_byte_packets", tx128to255octets_gb),
	AXGMAC_MMC_STAT("tx_256_to_511_byte_packets", tx256to511octets_gb),
	AXGMAC_MMC_STAT("tx_512_to_1023_byte_packets", tx512to1023octets_gb),
	AXGMAC_MMC_STAT("tx_1024_to_max_byte_packets", tx1024tomaxoctets_gb),
	AXGMAC_MMC_STAT("tx_underflow_errors", txunderflowerror),
	AXGMAC_MMC_STAT("tx_pause_frames", txpauseframes),

	AXGMAC_MMC_STAT("rx_bytes", rxoctetcount_gb),
	AXGMAC_MMC_STAT("rx_packets", rxframecount_gb),
	AXGMAC_MMC_STAT("rx_unicast_packets", rxunicastframes_g),
	AXGMAC_MMC_STAT("rx_broadcast_packets", rxbroadcastframes_g),
	AXGMAC_MMC_STAT("rx_multicast_packets", rxmulticastframes_g),
	AXGMAC_MMC_STAT("rx_vlan_packets", rxvlanframes_gb),
	AXGMAC_MMC_STAT("rx_64_byte_packets", rx64octets_gb),
	AXGMAC_MMC_STAT("rx_65_to_127_byte_packets", rx65to127octets_gb),
	AXGMAC_MMC_STAT("rx_128_to_255_byte_packets", rx128to255octets_gb),
	AXGMAC_MMC_STAT("rx_256_to_511_byte_packets", rx256to511octets_gb),
	AXGMAC_MMC_STAT("rx_512_to_1023_byte_packets", rx512to1023octets_gb),
	AXGMAC_MMC_STAT("rx_1024_to_max_byte_packets", rx1024tomaxoctets_gb),
	AXGMAC_MMC_STAT("rx_undersize_packets", rxundersize_g),
	AXGMAC_MMC_STAT("rx_oversize_packets", rxoversize_g),
	AXGMAC_MMC_STAT("rx_crc_errors", rxcrcerror),
	AXGMAC_MMC_STAT("rx_crc_errors_small_packets", rxrunterror),
	AXGMAC_MMC_STAT("rx_crc_errors_giant_packets", rxjabbererror),
	AXGMAC_MMC_STAT("rx_length_errors", rxlengtherror),
	AXGMAC_MMC_STAT("rx_out_of_range_errors", rxoutofrangetype),
	AXGMAC_MMC_STAT("rx_fifo_overflow_errors", rxfifooverflow),
	AXGMAC_MMC_STAT("rx_watchdog_errors", rxwatchdogerror),
	AXGMAC_MMC_STAT("rx_pause_frames", rxpauseframes),
};

#define AXGBE_XSTATS_COUNT        ARRAY_SIZE(axgbe_xstats_strings)

/* The set of PCI devices this driver supports */
#define AMD_PCI_VENDOR_ID       0x1022
#define AMD_PCI_RV_ROOT_COMPLEX_ID	0x15d0
#define AMD_PCI_AXGBE_DEVICE_V2A 0x1458
#define AMD_PCI_AXGBE_DEVICE_V2B 0x1459

int axgbe_logtype_init;
int axgbe_logtype_driver;

static const struct rte_pci_id pci_id_axgbe_map[] = {
	{RTE_PCI_DEVICE(AMD_PCI_VENDOR_ID, AMD_PCI_AXGBE_DEVICE_V2A)},
	{RTE_PCI_DEVICE(AMD_PCI_VENDOR_ID, AMD_PCI_AXGBE_DEVICE_V2B)},
	{ .vendor_id = 0, },
};

static struct axgbe_version_data axgbe_v2a = {
	.init_function_ptrs_phy_impl    = axgbe_init_function_ptrs_phy_v2,
	.xpcs_access			= AXGBE_XPCS_ACCESS_V2,
	.mmc_64bit			= 1,
	.tx_max_fifo_size		= 229376,
	.rx_max_fifo_size		= 229376,
	.tx_tstamp_workaround		= 1,
	.ecc_support			= 1,
	.i2c_support			= 1,
	.an_cdr_workaround		= 1,
};

static struct axgbe_version_data axgbe_v2b = {
	.init_function_ptrs_phy_impl    = axgbe_init_function_ptrs_phy_v2,
	.xpcs_access			= AXGBE_XPCS_ACCESS_V2,
	.mmc_64bit			= 1,
	.tx_max_fifo_size		= 65536,
	.rx_max_fifo_size		= 65536,
	.tx_tstamp_workaround		= 1,
	.ecc_support			= 1,
	.i2c_support			= 1,
	.an_cdr_workaround		= 1,
};

static const struct rte_eth_desc_lim rx_desc_lim = {
	.nb_max = AXGBE_MAX_RING_DESC,
	.nb_min = AXGBE_MIN_RING_DESC,
	.nb_align = 8,
};

static const struct rte_eth_desc_lim tx_desc_lim = {
	.nb_max = AXGBE_MAX_RING_DESC,
	.nb_min = AXGBE_MIN_RING_DESC,
	.nb_align = 8,
};

static const struct eth_dev_ops axgbe_eth_dev_ops = {
	.dev_configure        = axgbe_dev_configure,
	.dev_start            = axgbe_dev_start,
	.dev_stop             = axgbe_dev_stop,
	.dev_close            = axgbe_dev_close,
	.promiscuous_enable   = axgbe_dev_promiscuous_enable,
	.promiscuous_disable  = axgbe_dev_promiscuous_disable,
	.allmulticast_enable  = axgbe_dev_allmulticast_enable,
	.allmulticast_disable = axgbe_dev_allmulticast_disable,
	.mac_addr_set         = axgbe_dev_mac_addr_set,
	.mac_addr_add         = axgbe_dev_mac_addr_add,
	.mac_addr_remove      = axgbe_dev_mac_addr_remove,
	.set_mc_addr_list     = axgbe_dev_set_mc_addr_list,
	.uc_hash_table_set    = axgbe_dev_uc_hash_table_set,
	.uc_all_hash_table_set = axgbe_dev_uc_all_hash_table_set,
	.link_update          = axgbe_dev_link_update,
	.get_reg	      = axgbe_dev_get_regs,
	.stats_get            = axgbe_dev_stats_get,
	.stats_reset          = axgbe_dev_stats_reset,
	.xstats_get	      = axgbe_dev_xstats_get,
	.xstats_reset	      = axgbe_dev_xstats_reset,
	.xstats_get_names     = axgbe_dev_xstats_get_names,
	.xstats_get_names_by_id = axgbe_dev_xstats_get_names_by_id,
	.xstats_get_by_id     = axgbe_dev_xstats_get_by_id,
	.dev_infos_get        = axgbe_dev_info_get,
	.rx_queue_setup       = axgbe_dev_rx_queue_setup,
	.rx_queue_release     = axgbe_dev_rx_queue_release,
	.tx_queue_setup       = axgbe_dev_tx_queue_setup,
	.tx_queue_release     = axgbe_dev_tx_queue_release,
	.flow_ctrl_get        = axgbe_flow_ctrl_get,
	.flow_ctrl_set        = axgbe_flow_ctrl_set,
	.priority_flow_ctrl_set = axgbe_priority_flow_ctrl_set,
	.rxq_info_get                 = axgbe_rxq_info_get,
	.txq_info_get                 = axgbe_txq_info_get,
	.dev_supported_ptypes_get     = axgbe_dev_supported_ptypes_get,
	.rx_descriptor_status         = axgbe_dev_rx_descriptor_status,
	.tx_descriptor_status         = axgbe_dev_tx_descriptor_status,
};

static int axgbe_phy_reset(struct axgbe_port *pdata)
{
	pdata->phy_link = -1;
	pdata->phy_speed = SPEED_UNKNOWN;
	return pdata->phy_if.phy_reset(pdata);
}

/*
 * Interrupt handler triggered by NIC  for handling
 * specific interrupt.
 *
 * @param handle
 *  Pointer to interrupt handle.
 * @param param
 *  The address of parameter (struct rte_eth_dev *) regsitered before.
 *
 * @return
 *  void
 */
static void
axgbe_dev_interrupt_handler(void *param)
{
	struct rte_eth_dev *dev = (struct rte_eth_dev *)param;
	struct axgbe_port *pdata = dev->data->dev_private;
	unsigned int dma_isr, dma_ch_isr;

	pdata->phy_if.an_isr(pdata);
	/*DMA related interrupts*/
	dma_isr = AXGMAC_IOREAD(pdata, DMA_ISR);
	PMD_DRV_LOG(DEBUG, "DMA_ISR=%#010x\n", dma_isr);
	if (dma_isr) {
		if (dma_isr & 1) {
			dma_ch_isr =
				AXGMAC_DMA_IOREAD((struct axgbe_rx_queue *)
						  pdata->rx_queues[0],
						  DMA_CH_SR);
			PMD_DRV_LOG(DEBUG, "DMA_CH0_ISR=%#010x\n", dma_ch_isr);
			AXGMAC_DMA_IOWRITE((struct axgbe_rx_queue *)
					   pdata->rx_queues[0],
					   DMA_CH_SR, dma_ch_isr);
		}
	}
	/* Unmask interrupts since disabled after generation */
	rte_intr_ack(&pdata->pci_dev->intr_handle);
}

/*
 * Configure device link speed and setup link.
 * It returns 0 on success.
 */
static int
axgbe_dev_configure(struct rte_eth_dev *dev)
{
	struct axgbe_port *pdata =  dev->data->dev_private;
	/* Checksum offload to hardware */
	pdata->rx_csum_enable = dev->data->dev_conf.rxmode.offloads &
				DEV_RX_OFFLOAD_CHECKSUM;
	return 0;
}

static int
axgbe_dev_rx_mq_config(struct rte_eth_dev *dev)
{
	struct axgbe_port *pdata = dev->data->dev_private;

	if (dev->data->dev_conf.rxmode.mq_mode == ETH_MQ_RX_RSS)
		pdata->rss_enable = 1;
	else if (dev->data->dev_conf.rxmode.mq_mode == ETH_MQ_RX_NONE)
		pdata->rss_enable = 0;
	else
		return  -1;
	return 0;
}

static int
axgbe_dev_start(struct rte_eth_dev *dev)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	int ret;
	struct rte_eth_dev_data *dev_data = dev->data;
	uint16_t max_pkt_len = dev_data->dev_conf.rxmode.max_rx_pkt_len;

	dev->dev_ops = &axgbe_eth_dev_ops;

	PMD_INIT_FUNC_TRACE();

	/* Multiqueue RSS */
	ret = axgbe_dev_rx_mq_config(dev);
	if (ret) {
		PMD_DRV_LOG(ERR, "Unable to config RX MQ\n");
		return ret;
	}
	ret = axgbe_phy_reset(pdata);
	if (ret) {
		PMD_DRV_LOG(ERR, "phy reset failed\n");
		return ret;
	}
	ret = pdata->hw_if.init(pdata);
	if (ret) {
		PMD_DRV_LOG(ERR, "dev_init failed\n");
		return ret;
	}

	/* enable uio/vfio intr/eventfd mapping */
	rte_intr_enable(&pdata->pci_dev->intr_handle);

	/* phy start*/
	pdata->phy_if.phy_start(pdata);
	axgbe_dev_enable_tx(dev);
	axgbe_dev_enable_rx(dev);

	axgbe_clear_bit(AXGBE_STOPPED, &pdata->dev_state);
	axgbe_clear_bit(AXGBE_DOWN, &pdata->dev_state);
	if ((dev_data->dev_conf.rxmode.offloads & DEV_RX_OFFLOAD_SCATTER) ||
				max_pkt_len > pdata->rx_buf_size)
		dev_data->scattered_rx = 1;

	/*  Scatter Rx handling */
	if (dev_data->scattered_rx)
		dev->rx_pkt_burst = &eth_axgbe_recv_scattered_pkts;
	else
		dev->rx_pkt_burst = &axgbe_recv_pkts;

	return 0;
}

/* Stop device: disable rx and tx functions to allow for reconfiguring. */
static void
axgbe_dev_stop(struct rte_eth_dev *dev)
{
	struct axgbe_port *pdata = dev->data->dev_private;

	PMD_INIT_FUNC_TRACE();

	rte_intr_disable(&pdata->pci_dev->intr_handle);

	if (axgbe_test_bit(AXGBE_STOPPED, &pdata->dev_state))
		return;

	axgbe_set_bit(AXGBE_STOPPED, &pdata->dev_state);
	axgbe_dev_disable_tx(dev);
	axgbe_dev_disable_rx(dev);

	pdata->phy_if.phy_stop(pdata);
	pdata->hw_if.exit(pdata);
	memset(&dev->data->dev_link, 0, sizeof(struct rte_eth_link));
	axgbe_set_bit(AXGBE_DOWN, &pdata->dev_state);
}

/* Clear all resources like TX/RX queues. */
static void
axgbe_dev_close(struct rte_eth_dev *dev)
{
	axgbe_dev_clear_queues(dev);
}

static int
axgbe_dev_promiscuous_enable(struct rte_eth_dev *dev)
{
	struct axgbe_port *pdata = dev->data->dev_private;

	PMD_INIT_FUNC_TRACE();

	AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, PR, 1);

	return 0;
}

static int
axgbe_dev_promiscuous_disable(struct rte_eth_dev *dev)
{
	struct axgbe_port *pdata = dev->data->dev_private;

	PMD_INIT_FUNC_TRACE();

	AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, PR, 0);

	return 0;
}

static int
axgbe_dev_allmulticast_enable(struct rte_eth_dev *dev)
{
	struct axgbe_port *pdata = dev->data->dev_private;

	PMD_INIT_FUNC_TRACE();

	if (AXGMAC_IOREAD_BITS(pdata, MAC_PFR, PM))
		return 0;
	AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, PM, 1);

	return 0;
}

static int
axgbe_dev_allmulticast_disable(struct rte_eth_dev *dev)
{
	struct axgbe_port *pdata = dev->data->dev_private;

	PMD_INIT_FUNC_TRACE();

	if (!AXGMAC_IOREAD_BITS(pdata, MAC_PFR, PM))
		return 0;
	AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, PM, 0);

	return 0;
}

static int
axgbe_dev_mac_addr_set(struct rte_eth_dev *dev, struct rte_ether_addr *mac_addr)
{
	struct axgbe_port *pdata = dev->data->dev_private;

	/* Set Default MAC Addr */
	axgbe_set_mac_addn_addr(pdata, (u8 *)mac_addr, 0);

	return 0;
}

static int
axgbe_dev_mac_addr_add(struct rte_eth_dev *dev, struct rte_ether_addr *mac_addr,
			      uint32_t index, uint32_t pool __rte_unused)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	struct axgbe_hw_features *hw_feat = &pdata->hw_feat;

	if (index > hw_feat->addn_mac) {
		PMD_DRV_LOG(ERR, "Invalid Index %d\n", index);
		return -EINVAL;
	}
	axgbe_set_mac_addn_addr(pdata, (u8 *)mac_addr, index);
	return 0;
}

static void
axgbe_dev_mac_addr_remove(struct rte_eth_dev *dev, uint32_t index)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	struct axgbe_hw_features *hw_feat = &pdata->hw_feat;

	if (index > hw_feat->addn_mac) {
		PMD_DRV_LOG(ERR, "Invalid Index %d\n", index);
		return;
	}
	axgbe_set_mac_addn_addr(pdata, NULL, index);
}

static int
axgbe_dev_set_mc_addr_list(struct rte_eth_dev *dev,
				      struct rte_ether_addr *mc_addr_set,
				      uint32_t nb_mc_addr)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	struct axgbe_hw_features *hw_feat = &pdata->hw_feat;
	uint32_t index = 1; /* 0 is always default mac */
	uint32_t i;

	if (nb_mc_addr > hw_feat->addn_mac) {
		PMD_DRV_LOG(ERR, "Invalid Index %d\n", nb_mc_addr);
		return -EINVAL;
	}

	/* clear unicast addresses */
	for (i = 1; i < hw_feat->addn_mac; i++) {
		if (rte_is_zero_ether_addr(&dev->data->mac_addrs[i]))
			continue;
		memset(&dev->data->mac_addrs[i], 0,
		       sizeof(struct rte_ether_addr));
	}

	while (nb_mc_addr--)
		axgbe_set_mac_addn_addr(pdata, (u8 *)mc_addr_set++, index++);

	return 0;
}

static int
axgbe_dev_uc_hash_table_set(struct rte_eth_dev *dev,
			    struct rte_ether_addr *mac_addr, uint8_t add)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	struct axgbe_hw_features *hw_feat = &pdata->hw_feat;

	if (!hw_feat->hash_table_size) {
		PMD_DRV_LOG(ERR, "MAC Hash Table not supported\n");
		return -ENOTSUP;
	}

	axgbe_set_mac_hash_table(pdata, (u8 *)mac_addr, add);

	if (pdata->uc_hash_mac_addr > 0) {
		AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, HPF, 1);
		AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, HUC, 1);
	} else {
		AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, HPF, 0);
		AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, HUC, 0);
	}
	return 0;
}

static int
axgbe_dev_uc_all_hash_table_set(struct rte_eth_dev *dev, uint8_t add)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	struct axgbe_hw_features *hw_feat = &pdata->hw_feat;
	uint32_t index;

	if (!hw_feat->hash_table_size) {
		PMD_DRV_LOG(ERR, "MAC Hash Table not supported\n");
		return -ENOTSUP;
	}

	for (index = 0; index < pdata->hash_table_count; index++) {
		if (add)
			pdata->uc_hash_table[index] = ~0;
		else
			pdata->uc_hash_table[index] = 0;

		PMD_DRV_LOG(DEBUG, "%s MAC hash table at Index %#x\n",
			    add ? "set" : "clear", index);

		AXGMAC_IOWRITE(pdata, MAC_HTR(index),
			       pdata->uc_hash_table[index]);
	}

	if (add) {
		AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, HPF, 1);
		AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, HUC, 1);
	} else {
		AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, HPF, 0);
		AXGMAC_IOWRITE_BITS(pdata, MAC_PFR, HUC, 0);
	}
	return 0;
}

/* return 0 means link status changed, -1 means not changed */
static int
axgbe_dev_link_update(struct rte_eth_dev *dev,
		      int wait_to_complete __rte_unused)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	struct rte_eth_link link;
	int ret = 0;

	PMD_INIT_FUNC_TRACE();
	rte_delay_ms(800);

	pdata->phy_if.phy_status(pdata);

	memset(&link, 0, sizeof(struct rte_eth_link));
	link.link_duplex = pdata->phy.duplex;
	link.link_status = pdata->phy_link;
	link.link_speed = pdata->phy_speed;
	link.link_autoneg = !(dev->data->dev_conf.link_speeds &
			      ETH_LINK_SPEED_FIXED);
	ret = rte_eth_linkstatus_set(dev, &link);
	if (ret == -1)
		PMD_DRV_LOG(ERR, "No change in link status\n");

	return ret;
}

static int
axgbe_dev_get_regs(struct rte_eth_dev *dev, struct rte_dev_reg_info *regs)
{
	struct axgbe_port *pdata = dev->data->dev_private;

	if (regs->data == NULL) {
		regs->length = axgbe_regs_get_count(pdata);
		regs->width = sizeof(uint32_t);
		return 0;
	}

	/* Only full register dump is supported */
	if (regs->length &&
	    regs->length != (uint32_t)axgbe_regs_get_count(pdata))
		return -ENOTSUP;

	regs->version = pdata->pci_dev->id.vendor_id << 16 |
			pdata->pci_dev->id.device_id;
	axgbe_regs_dump(pdata, regs->data);
	return 0;
}
static void axgbe_read_mmc_stats(struct axgbe_port *pdata)
{
	struct axgbe_mmc_stats *stats = &pdata->mmc_stats;

	/* Freeze counters */
	AXGMAC_IOWRITE_BITS(pdata, MMC_CR, MCF, 1);

	/* Tx counters */
	stats->txoctetcount_gb +=
		AXGMAC_IOREAD(pdata, MMC_TXOCTETCOUNT_GB_LO);
	stats->txoctetcount_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXOCTETCOUNT_GB_HI) << 32);

	stats->txframecount_gb +=
		AXGMAC_IOREAD(pdata, MMC_TXFRAMECOUNT_GB_LO);
	stats->txframecount_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXFRAMECOUNT_GB_HI) << 32);

	stats->txbroadcastframes_g +=
		AXGMAC_IOREAD(pdata, MMC_TXBROADCASTFRAMES_G_LO);
	stats->txbroadcastframes_g +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXBROADCASTFRAMES_G_HI) << 32);

	stats->txmulticastframes_g +=
		AXGMAC_IOREAD(pdata, MMC_TXMULTICASTFRAMES_G_LO);
	stats->txmulticastframes_g +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXMULTICASTFRAMES_G_HI) << 32);

	stats->tx64octets_gb +=
		AXGMAC_IOREAD(pdata, MMC_TX64OCTETS_GB_LO);
	stats->tx64octets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TX64OCTETS_GB_HI) << 32);

	stats->tx65to127octets_gb +=
		AXGMAC_IOREAD(pdata, MMC_TX65TO127OCTETS_GB_LO);
	stats->tx65to127octets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TX65TO127OCTETS_GB_HI) << 32);

	stats->tx128to255octets_gb +=
		AXGMAC_IOREAD(pdata, MMC_TX128TO255OCTETS_GB_LO);
	stats->tx128to255octets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TX128TO255OCTETS_GB_HI) << 32);

	stats->tx256to511octets_gb +=
		AXGMAC_IOREAD(pdata, MMC_TX256TO511OCTETS_GB_LO);
	stats->tx256to511octets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TX256TO511OCTETS_GB_HI) << 32);

	stats->tx512to1023octets_gb +=
		AXGMAC_IOREAD(pdata, MMC_TX512TO1023OCTETS_GB_LO);
	stats->tx512to1023octets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TX512TO1023OCTETS_GB_HI) << 32);

	stats->tx1024tomaxoctets_gb +=
		AXGMAC_IOREAD(pdata, MMC_TX1024TOMAXOCTETS_GB_LO);
	stats->tx1024tomaxoctets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TX1024TOMAXOCTETS_GB_HI) << 32);

	stats->txunicastframes_gb +=
		AXGMAC_IOREAD(pdata, MMC_TXUNICASTFRAMES_GB_LO);
	stats->txunicastframes_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXUNICASTFRAMES_GB_HI) << 32);

	stats->txmulticastframes_gb +=
		AXGMAC_IOREAD(pdata, MMC_TXMULTICASTFRAMES_GB_LO);
	stats->txmulticastframes_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXMULTICASTFRAMES_GB_HI) << 32);

	stats->txbroadcastframes_g +=
		AXGMAC_IOREAD(pdata, MMC_TXBROADCASTFRAMES_GB_LO);
	stats->txbroadcastframes_g +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXBROADCASTFRAMES_GB_HI) << 32);

	stats->txunderflowerror +=
		AXGMAC_IOREAD(pdata, MMC_TXUNDERFLOWERROR_LO);
	stats->txunderflowerror +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXUNDERFLOWERROR_HI) << 32);

	stats->txoctetcount_g +=
		AXGMAC_IOREAD(pdata, MMC_TXOCTETCOUNT_G_LO);
	stats->txoctetcount_g +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXOCTETCOUNT_G_HI) << 32);

	stats->txframecount_g +=
		AXGMAC_IOREAD(pdata, MMC_TXFRAMECOUNT_G_LO);
	stats->txframecount_g +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXFRAMECOUNT_G_HI) << 32);

	stats->txpauseframes +=
		AXGMAC_IOREAD(pdata, MMC_TXPAUSEFRAMES_LO);
	stats->txpauseframes +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXPAUSEFRAMES_HI) << 32);

	stats->txvlanframes_g +=
		AXGMAC_IOREAD(pdata, MMC_TXVLANFRAMES_G_LO);
	stats->txvlanframes_g +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_TXVLANFRAMES_G_HI) << 32);

	/* Rx counters */
	stats->rxframecount_gb +=
		AXGMAC_IOREAD(pdata, MMC_RXFRAMECOUNT_GB_LO);
	stats->rxframecount_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXFRAMECOUNT_GB_HI) << 32);

	stats->rxoctetcount_gb +=
		AXGMAC_IOREAD(pdata, MMC_RXOCTETCOUNT_GB_LO);
	stats->rxoctetcount_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXOCTETCOUNT_GB_HI) << 32);

	stats->rxoctetcount_g +=
		AXGMAC_IOREAD(pdata, MMC_RXOCTETCOUNT_G_LO);
	stats->rxoctetcount_g +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXOCTETCOUNT_G_HI) << 32);

	stats->rxbroadcastframes_g +=
		AXGMAC_IOREAD(pdata, MMC_RXBROADCASTFRAMES_G_LO);
	stats->rxbroadcastframes_g +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXBROADCASTFRAMES_G_HI) << 32);

	stats->rxmulticastframes_g +=
		AXGMAC_IOREAD(pdata, MMC_RXMULTICASTFRAMES_G_LO);
	stats->rxmulticastframes_g +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXMULTICASTFRAMES_G_HI) << 32);

	stats->rxcrcerror +=
		AXGMAC_IOREAD(pdata, MMC_RXCRCERROR_LO);
	stats->rxcrcerror +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXCRCERROR_HI) << 32);

	stats->rxrunterror +=
		AXGMAC_IOREAD(pdata, MMC_RXRUNTERROR);

	stats->rxjabbererror +=
		AXGMAC_IOREAD(pdata, MMC_RXJABBERERROR);

	stats->rxundersize_g +=
		AXGMAC_IOREAD(pdata, MMC_RXUNDERSIZE_G);

	stats->rxoversize_g +=
		AXGMAC_IOREAD(pdata, MMC_RXOVERSIZE_G);

	stats->rx64octets_gb +=
		AXGMAC_IOREAD(pdata, MMC_RX64OCTETS_GB_LO);
	stats->rx64octets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RX64OCTETS_GB_HI) << 32);

	stats->rx65to127octets_gb +=
		AXGMAC_IOREAD(pdata, MMC_RX65TO127OCTETS_GB_LO);
	stats->rx65to127octets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RX65TO127OCTETS_GB_HI) << 32);

	stats->rx128to255octets_gb +=
		AXGMAC_IOREAD(pdata, MMC_RX128TO255OCTETS_GB_LO);
	stats->rx128to255octets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RX128TO255OCTETS_GB_HI) << 32);

	stats->rx256to511octets_gb +=
		AXGMAC_IOREAD(pdata, MMC_RX256TO511OCTETS_GB_LO);
	stats->rx256to511octets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RX256TO511OCTETS_GB_HI) << 32);

	stats->rx512to1023octets_gb +=
		AXGMAC_IOREAD(pdata, MMC_RX512TO1023OCTETS_GB_LO);
	stats->rx512to1023octets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RX512TO1023OCTETS_GB_HI) << 32);

	stats->rx1024tomaxoctets_gb +=
		AXGMAC_IOREAD(pdata, MMC_RX1024TOMAXOCTETS_GB_LO);
	stats->rx1024tomaxoctets_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RX1024TOMAXOCTETS_GB_HI) << 32);

	stats->rxunicastframes_g +=
		AXGMAC_IOREAD(pdata, MMC_RXUNICASTFRAMES_G_LO);
	stats->rxunicastframes_g +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXUNICASTFRAMES_G_HI) << 32);

	stats->rxlengtherror +=
		AXGMAC_IOREAD(pdata, MMC_RXLENGTHERROR_LO);
	stats->rxlengtherror +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXLENGTHERROR_HI) << 32);

	stats->rxoutofrangetype +=
		AXGMAC_IOREAD(pdata, MMC_RXOUTOFRANGETYPE_LO);
	stats->rxoutofrangetype +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXOUTOFRANGETYPE_HI) << 32);

	stats->rxpauseframes +=
		AXGMAC_IOREAD(pdata, MMC_RXPAUSEFRAMES_LO);
	stats->rxpauseframes +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXPAUSEFRAMES_HI) << 32);

	stats->rxfifooverflow +=
		AXGMAC_IOREAD(pdata, MMC_RXFIFOOVERFLOW_LO);
	stats->rxfifooverflow +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXFIFOOVERFLOW_HI) << 32);

	stats->rxvlanframes_gb +=
		AXGMAC_IOREAD(pdata, MMC_RXVLANFRAMES_GB_LO);
	stats->rxvlanframes_gb +=
	((uint64_t)AXGMAC_IOREAD(pdata, MMC_RXVLANFRAMES_GB_HI) << 32);

	stats->rxwatchdogerror +=
		AXGMAC_IOREAD(pdata, MMC_RXWATCHDOGERROR);

	/* Un-freeze counters */
	AXGMAC_IOWRITE_BITS(pdata, MMC_CR, MCF, 0);
}

static int
axgbe_dev_xstats_get(struct rte_eth_dev *dev, struct rte_eth_xstat *stats,
		     unsigned int n)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	unsigned int i;

	if (!stats)
		return 0;

	axgbe_read_mmc_stats(pdata);

	for (i = 0; i < n && i < AXGBE_XSTATS_COUNT; i++) {
		stats[i].id = i;
		stats[i].value = *(u64 *)((uint8_t *)&pdata->mmc_stats +
				axgbe_xstats_strings[i].offset);
	}

	return i;
}

static int
axgbe_dev_xstats_get_names(__rte_unused struct rte_eth_dev *dev,
			   struct rte_eth_xstat_name *xstats_names,
			   unsigned int n)
{
	unsigned int i;

	if (n >= AXGBE_XSTATS_COUNT && xstats_names) {
		for (i = 0; i < AXGBE_XSTATS_COUNT; ++i) {
			snprintf(xstats_names[i].name,
				 RTE_ETH_XSTATS_NAME_SIZE, "%s",
				 axgbe_xstats_strings[i].name);
		}
	}

	return AXGBE_XSTATS_COUNT;
}

static int
axgbe_dev_xstats_get_by_id(struct rte_eth_dev *dev, const uint64_t *ids,
			   uint64_t *values, unsigned int n)
{
	unsigned int i;
	uint64_t values_copy[AXGBE_XSTATS_COUNT];

	if (!ids) {
		struct axgbe_port *pdata = dev->data->dev_private;

		if (n < AXGBE_XSTATS_COUNT)
			return AXGBE_XSTATS_COUNT;

		axgbe_read_mmc_stats(pdata);

		for (i = 0; i < AXGBE_XSTATS_COUNT; i++) {
			values[i] = *(u64 *)((uint8_t *)&pdata->mmc_stats +
					axgbe_xstats_strings[i].offset);
		}

		return i;
	}

	axgbe_dev_xstats_get_by_id(dev, NULL, values_copy, AXGBE_XSTATS_COUNT);

	for (i = 0; i < n; i++) {
		if (ids[i] >= AXGBE_XSTATS_COUNT) {
			PMD_DRV_LOG(ERR, "id value isn't valid\n");
			return -1;
		}
		values[i] = values_copy[ids[i]];
	}
	return n;
}

static int
axgbe_dev_xstats_get_names_by_id(struct rte_eth_dev *dev,
				 struct rte_eth_xstat_name *xstats_names,
				 const uint64_t *ids,
				 unsigned int size)
{
	struct rte_eth_xstat_name xstats_names_copy[AXGBE_XSTATS_COUNT];
	unsigned int i;

	if (!ids)
		return axgbe_dev_xstats_get_names(dev, xstats_names, size);

	axgbe_dev_xstats_get_names(dev, xstats_names_copy, size);

	for (i = 0; i < size; i++) {
		if (ids[i] >= AXGBE_XSTATS_COUNT) {
			PMD_DRV_LOG(ERR, "id value isn't valid\n");
			return -1;
		}
		strcpy(xstats_names[i].name, xstats_names_copy[ids[i]].name);
	}
	return size;
}

static int
axgbe_dev_xstats_reset(struct rte_eth_dev *dev)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	struct axgbe_mmc_stats *stats = &pdata->mmc_stats;

	/* MMC registers are configured for reset on read */
	axgbe_read_mmc_stats(pdata);

	/* Reset stats */
	memset(stats, 0, sizeof(*stats));

	return 0;
}

static int
axgbe_dev_stats_get(struct rte_eth_dev *dev,
		    struct rte_eth_stats *stats)
{
	struct axgbe_rx_queue *rxq;
	struct axgbe_tx_queue *txq;
	struct axgbe_port *pdata = dev->data->dev_private;
	struct axgbe_mmc_stats *mmc_stats = &pdata->mmc_stats;
	unsigned int i;

	axgbe_read_mmc_stats(pdata);

	stats->imissed = mmc_stats->rxfifooverflow;

	for (i = 0; i < dev->data->nb_rx_queues; i++) {
		rxq = dev->data->rx_queues[i];
		stats->q_ipackets[i] = rxq->pkts;
		stats->ipackets += rxq->pkts;
		stats->q_ibytes[i] = rxq->bytes;
		stats->ibytes += rxq->bytes;
		stats->rx_nombuf += rxq->rx_mbuf_alloc_failed;
		stats->q_errors[i] = rxq->errors + rxq->rx_mbuf_alloc_failed;
		stats->ierrors += rxq->errors;
	}

	for (i = 0; i < dev->data->nb_tx_queues; i++) {
		txq = dev->data->tx_queues[i];
		stats->q_opackets[i] = txq->pkts;
		stats->opackets += txq->pkts;
		stats->q_obytes[i] = txq->bytes;
		stats->obytes += txq->bytes;
		stats->oerrors += txq->errors;
	}

	return 0;
}

static int
axgbe_dev_stats_reset(struct rte_eth_dev *dev)
{
	struct axgbe_rx_queue *rxq;
	struct axgbe_tx_queue *txq;
	unsigned int i;

	for (i = 0; i < dev->data->nb_rx_queues; i++) {
		rxq = dev->data->rx_queues[i];
		rxq->pkts = 0;
		rxq->bytes = 0;
		rxq->errors = 0;
		rxq->rx_mbuf_alloc_failed = 0;
	}
	for (i = 0; i < dev->data->nb_tx_queues; i++) {
		txq = dev->data->tx_queues[i];
		txq->pkts = 0;
		txq->bytes = 0;
		txq->errors = 0;
	}

	return 0;
}

static int
axgbe_dev_info_get(struct rte_eth_dev *dev, struct rte_eth_dev_info *dev_info)
{
	struct axgbe_port *pdata = dev->data->dev_private;

	dev_info->max_rx_queues = pdata->rx_ring_count;
	dev_info->max_tx_queues = pdata->tx_ring_count;
	dev_info->min_rx_bufsize = AXGBE_RX_MIN_BUF_SIZE;
	dev_info->max_rx_pktlen = AXGBE_RX_MAX_BUF_SIZE;
	dev_info->max_mac_addrs = pdata->hw_feat.addn_mac + 1;
	dev_info->max_hash_mac_addrs = pdata->hw_feat.hash_table_size;
	dev_info->speed_capa =  ETH_LINK_SPEED_10G;

	dev_info->rx_offload_capa =
		DEV_RX_OFFLOAD_IPV4_CKSUM |
		DEV_RX_OFFLOAD_UDP_CKSUM  |
		DEV_RX_OFFLOAD_TCP_CKSUM  |
		DEV_RX_OFFLOAD_JUMBO_FRAME	|
		DEV_RX_OFFLOAD_SCATTER	  |
		DEV_RX_OFFLOAD_KEEP_CRC;

	dev_info->tx_offload_capa =
		DEV_TX_OFFLOAD_IPV4_CKSUM  |
		DEV_TX_OFFLOAD_UDP_CKSUM   |
		DEV_TX_OFFLOAD_TCP_CKSUM;

	if (pdata->hw_feat.rss) {
		dev_info->flow_type_rss_offloads = AXGBE_RSS_OFFLOAD;
		dev_info->reta_size = pdata->hw_feat.hash_table_size;
		dev_info->hash_key_size =  AXGBE_RSS_HASH_KEY_SIZE;
	}

	dev_info->rx_desc_lim = rx_desc_lim;
	dev_info->tx_desc_lim = tx_desc_lim;

	dev_info->default_rxconf = (struct rte_eth_rxconf) {
		.rx_free_thresh = AXGBE_RX_FREE_THRESH,
	};

	dev_info->default_txconf = (struct rte_eth_txconf) {
		.tx_free_thresh = AXGBE_TX_FREE_THRESH,
	};

	return 0;
}

static int
axgbe_flow_ctrl_get(struct rte_eth_dev *dev, struct rte_eth_fc_conf *fc_conf)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	struct xgbe_fc_info fc = pdata->fc;
	unsigned int reg, reg_val = 0;

	reg = MAC_Q0TFCR;
	reg_val = AXGMAC_IOREAD(pdata, reg);
	fc.low_water[0] =  AXGMAC_MTL_IOREAD_BITS(pdata, 0, MTL_Q_RQFCR, RFA);
	fc.high_water[0] =  AXGMAC_MTL_IOREAD_BITS(pdata, 0, MTL_Q_RQFCR, RFD);
	fc.pause_time[0] = AXGMAC_GET_BITS(reg_val, MAC_Q0TFCR, PT);
	fc.autoneg = pdata->pause_autoneg;

	if (pdata->rx_pause && pdata->tx_pause)
		fc.mode = RTE_FC_FULL;
	else if (pdata->rx_pause)
		fc.mode = RTE_FC_RX_PAUSE;
	else if (pdata->tx_pause)
		fc.mode = RTE_FC_TX_PAUSE;
	else
		fc.mode = RTE_FC_NONE;

	fc_conf->high_water =  (1024 + (fc.low_water[0] << 9)) / 1024;
	fc_conf->low_water =  (1024 + (fc.high_water[0] << 9)) / 1024;
	fc_conf->pause_time = fc.pause_time[0];
	fc_conf->send_xon = fc.send_xon;
	fc_conf->mode = fc.mode;

	return 0;
}

static int
axgbe_flow_ctrl_set(struct rte_eth_dev *dev, struct rte_eth_fc_conf *fc_conf)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	struct xgbe_fc_info fc = pdata->fc;
	unsigned int reg, reg_val = 0;
	reg = MAC_Q0TFCR;

	pdata->pause_autoneg = fc_conf->autoneg;
	pdata->phy.pause_autoneg = pdata->pause_autoneg;
	fc.send_xon = fc_conf->send_xon;
	AXGMAC_MTL_IOWRITE_BITS(pdata, 0, MTL_Q_RQFCR, RFA,
			AXGMAC_FLOW_CONTROL_VALUE(1024 * fc_conf->high_water));
	AXGMAC_MTL_IOWRITE_BITS(pdata, 0, MTL_Q_RQFCR, RFD,
			AXGMAC_FLOW_CONTROL_VALUE(1024 * fc_conf->low_water));
	AXGMAC_SET_BITS(reg_val, MAC_Q0TFCR, PT, fc_conf->pause_time);
	AXGMAC_IOWRITE(pdata, reg, reg_val);
	fc.mode = fc_conf->mode;

	if (fc.mode == RTE_FC_FULL) {
		pdata->tx_pause = 1;
		pdata->rx_pause = 1;
	} else if (fc.mode == RTE_FC_RX_PAUSE) {
		pdata->tx_pause = 0;
		pdata->rx_pause = 1;
	} else if (fc.mode == RTE_FC_TX_PAUSE) {
		pdata->tx_pause = 1;
		pdata->rx_pause = 0;
	} else {
		pdata->tx_pause = 0;
		pdata->rx_pause = 0;
	}

	if (pdata->tx_pause != (unsigned int)pdata->phy.tx_pause)
		pdata->hw_if.config_tx_flow_control(pdata);

	if (pdata->rx_pause != (unsigned int)pdata->phy.rx_pause)
		pdata->hw_if.config_rx_flow_control(pdata);

	pdata->hw_if.config_flow_control(pdata);
	pdata->phy.tx_pause = pdata->tx_pause;
	pdata->phy.rx_pause = pdata->rx_pause;

	return 0;
}

static int
axgbe_priority_flow_ctrl_set(struct rte_eth_dev *dev,
		struct rte_eth_pfc_conf *pfc_conf)
{
	struct axgbe_port *pdata = dev->data->dev_private;
	struct xgbe_fc_info fc = pdata->fc;
	uint8_t tc_num;

	tc_num = pdata->pfc_map[pfc_conf->priority];

	if (pfc_conf->priority >= pdata->hw_feat.tc_cnt) {
		PMD_INIT_LOG(ERR, "Max supported  traffic class: %d\n",
				pdata->hw_feat.tc_cnt);
	return -EINVAL;
	}

	pdata->pause_autoneg = pfc_conf->fc.autoneg;
	pdata->phy.pause_autoneg = pdata->pause_autoneg;
	fc.send_xon = pfc_conf->fc.send_xon;
	AXGMAC_MTL_IOWRITE_BITS(pdata, tc_num, MTL_Q_RQFCR, RFA,
		AXGMAC_FLOW_CONTROL_VALUE(1024 * pfc_conf->fc.high_water));
	AXGMAC_MTL_IOWRITE_BITS(pdata, tc_num, MTL_Q_RQFCR, RFD,
		AXGMAC_FLOW_CONTROL_VALUE(1024 * pfc_conf->fc.low_water));

	switch (tc_num) {
	case 0:
		AXGMAC_IOWRITE_BITS(pdata, MTL_TCPM0R,
				PSTC0, pfc_conf->fc.pause_time);
		break;
	case 1:
		AXGMAC_IOWRITE_BITS(pdata, MTL_TCPM0R,
				PSTC1, pfc_conf->fc.pause_time);
		break;
	case 2:
		AXGMAC_IOWRITE_BITS(pdata, MTL_TCPM0R,
				PSTC2, pfc_conf->fc.pause_time);
		break;
	case 3:
		AXGMAC_IOWRITE_BITS(pdata, MTL_TCPM0R,
				PSTC3, pfc_conf->fc.pause_time);
		break;
	case 4:
		AXGMAC_IOWRITE_BITS(pdata, MTL_TCPM1R,
				PSTC4, pfc_conf->fc.pause_time);
		break;
	case 5:
		AXGMAC_IOWRITE_BITS(pdata, MTL_TCPM1R,
				PSTC5, pfc_conf->fc.pause_time);
		break;
	case 7:
		AXGMAC_IOWRITE_BITS(pdata, MTL_TCPM1R,
				PSTC6, pfc_conf->fc.pause_time);
		break;
	case 6:
		AXGMAC_IOWRITE_BITS(pdata, MTL_TCPM1R,
				PSTC7, pfc_conf->fc.pause_time);
		break;
	}

	fc.mode = pfc_conf->fc.mode;

	if (fc.mode == RTE_FC_FULL) {
		pdata->tx_pause = 1;
		pdata->rx_pause = 1;
		AXGMAC_IOWRITE_BITS(pdata, MAC_RFCR, PFCE, 1);
	} else if (fc.mode == RTE_FC_RX_PAUSE) {
		pdata->tx_pause = 0;
		pdata->rx_pause = 1;
		AXGMAC_IOWRITE_BITS(pdata, MAC_RFCR, PFCE, 1);
	} else if (fc.mode == RTE_FC_TX_PAUSE) {
		pdata->tx_pause = 1;
		pdata->rx_pause = 0;
		AXGMAC_IOWRITE_BITS(pdata, MAC_RFCR, PFCE, 0);
	} else {
		pdata->tx_pause = 0;
		pdata->rx_pause = 0;
		AXGMAC_IOWRITE_BITS(pdata, MAC_RFCR, PFCE, 0);
	}

	if (pdata->tx_pause != (unsigned int)pdata->phy.tx_pause)
		pdata->hw_if.config_tx_flow_control(pdata);

	if (pdata->rx_pause != (unsigned int)pdata->phy.rx_pause)
		pdata->hw_if.config_rx_flow_control(pdata);
	pdata->hw_if.config_flow_control(pdata);
	pdata->phy.tx_pause = pdata->tx_pause;
	pdata->phy.rx_pause = pdata->rx_pause;

	return 0;
}

void
axgbe_rxq_info_get(struct rte_eth_dev *dev, uint16_t queue_id,
	struct rte_eth_rxq_info *qinfo)
{
	struct   axgbe_rx_queue *rxq;

	rxq = dev->data->rx_queues[queue_id];
	qinfo->mp = rxq->mb_pool;
	qinfo->scattered_rx = dev->data->scattered_rx;
	qinfo->nb_desc = rxq->nb_desc;
	qinfo->conf.rx_free_thresh = rxq->free_thresh;
}

void
axgbe_txq_info_get(struct rte_eth_dev *dev, uint16_t queue_id,
	struct rte_eth_txq_info *qinfo)
{
	struct  axgbe_tx_queue *txq;

	txq = dev->data->tx_queues[queue_id];
	qinfo->nb_desc = txq->nb_desc;
	qinfo->conf.tx_free_thresh = txq->free_thresh;
}
const uint32_t *
axgbe_dev_supported_ptypes_get(struct rte_eth_dev *dev)
{
	static const uint32_t ptypes[] = {
		RTE_PTYPE_L2_ETHER,
		RTE_PTYPE_L2_ETHER_TIMESYNC,
		RTE_PTYPE_L2_ETHER_LLDP,
		RTE_PTYPE_L2_ETHER_ARP,
		RTE_PTYPE_L3_IPV4_EXT_UNKNOWN,
		RTE_PTYPE_L3_IPV6_EXT_UNKNOWN,
		RTE_PTYPE_L4_FRAG,
		RTE_PTYPE_L4_ICMP,
		RTE_PTYPE_L4_NONFRAG,
		RTE_PTYPE_L4_SCTP,
		RTE_PTYPE_L4_TCP,
		RTE_PTYPE_L4_UDP,
		RTE_PTYPE_TUNNEL_GRENAT,
		RTE_PTYPE_TUNNEL_IP,
		RTE_PTYPE_INNER_L2_ETHER,
		RTE_PTYPE_INNER_L2_ETHER_VLAN,
		RTE_PTYPE_INNER_L3_IPV4_EXT_UNKNOWN,
		RTE_PTYPE_INNER_L3_IPV6_EXT_UNKNOWN,
		RTE_PTYPE_INNER_L4_FRAG,
		RTE_PTYPE_INNER_L4_ICMP,
		RTE_PTYPE_INNER_L4_NONFRAG,
		RTE_PTYPE_INNER_L4_SCTP,
		RTE_PTYPE_INNER_L4_TCP,
		RTE_PTYPE_INNER_L4_UDP,
		RTE_PTYPE_UNKNOWN
	};

	if (dev->rx_pkt_burst == axgbe_recv_pkts)
		return ptypes;
	return NULL;
}

static void axgbe_get_all_hw_features(struct axgbe_port *pdata)
{
	unsigned int mac_hfr0, mac_hfr1, mac_hfr2;
	struct axgbe_hw_features *hw_feat = &pdata->hw_feat;

	mac_hfr0 = AXGMAC_IOREAD(pdata, MAC_HWF0R);
	mac_hfr1 = AXGMAC_IOREAD(pdata, MAC_HWF1R);
	mac_hfr2 = AXGMAC_IOREAD(pdata, MAC_HWF2R);

	memset(hw_feat, 0, sizeof(*hw_feat));

	hw_feat->version = AXGMAC_IOREAD(pdata, MAC_VR);

	/* Hardware feature register 0 */
	hw_feat->gmii        = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, GMIISEL);
	hw_feat->vlhash      = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, VLHASH);
	hw_feat->sma         = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, SMASEL);
	hw_feat->rwk         = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, RWKSEL);
	hw_feat->mgk         = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, MGKSEL);
	hw_feat->mmc         = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, MMCSEL);
	hw_feat->aoe         = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, ARPOFFSEL);
	hw_feat->ts          = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, TSSEL);
	hw_feat->eee         = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, EEESEL);
	hw_feat->tx_coe      = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, TXCOESEL);
	hw_feat->rx_coe      = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, RXCOESEL);
	hw_feat->addn_mac    = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R,
					      ADDMACADRSEL);
	hw_feat->ts_src      = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, TSSTSSEL);
	hw_feat->sa_vlan_ins = AXGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, SAVLANINS);

	/* Hardware feature register 1 */
	hw_feat->rx_fifo_size  = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						RXFIFOSIZE);
	hw_feat->tx_fifo_size  = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						TXFIFOSIZE);
	hw_feat->adv_ts_hi     = AXGMAC_GET_BITS(mac_hfr1,
						 MAC_HWF1R, ADVTHWORD);
	hw_feat->dma_width     = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, ADDR64);
	hw_feat->dcb           = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, DCBEN);
	hw_feat->sph           = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, SPHEN);
	hw_feat->tso           = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, TSOEN);
	hw_feat->dma_debug     = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, DBGMEMA);
	hw_feat->rss           = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, RSSEN);
	hw_feat->tc_cnt	       = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, NUMTC);
	hw_feat->hash_table_size = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						  HASHTBLSZ);
	hw_feat->l3l4_filter_num = AXGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						  L3L4FNUM);

	/* Hardware feature register 2 */
	hw_feat->rx_q_cnt     = AXGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, RXQCNT);
	hw_feat->tx_q_cnt     = AXGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, TXQCNT);
	hw_feat->rx_ch_cnt    = AXGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, RXCHCNT);
	hw_feat->tx_ch_cnt    = AXGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, TXCHCNT);
	hw_feat->pps_out_num  = AXGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, PPSOUTNUM);
	hw_feat->aux_snap_num = AXGMAC_GET_BITS(mac_hfr2, MAC_HWF2R,
						AUXSNAPNUM);

	/* Translate the Hash Table size into actual number */
	switch (hw_feat->hash_table_size) {
	case 0:
		break;
	case 1:
		hw_feat->hash_table_size = 64;
		break;
	case 2:
		hw_feat->hash_table_size = 128;
		break;
	case 3:
		hw_feat->hash_table_size = 256;
		break;
	}

	/* Translate the address width setting into actual number */
	switch (hw_feat->dma_width) {
	case 0:
		hw_feat->dma_width = 32;
		break;
	case 1:
		hw_feat->dma_width = 40;
		break;
	case 2:
		hw_feat->dma_width = 48;
		break;
	default:
		hw_feat->dma_width = 32;
	}

	/* The Queue, Channel and TC counts are zero based so increment them
	 * to get the actual number
	 */
	hw_feat->rx_q_cnt++;
	hw_feat->tx_q_cnt++;
	hw_feat->rx_ch_cnt++;
	hw_feat->tx_ch_cnt++;
	hw_feat->tc_cnt++;

	/* Translate the fifo sizes into actual numbers */
	hw_feat->rx_fifo_size = 1 << (hw_feat->rx_fifo_size + 7);
	hw_feat->tx_fifo_size = 1 << (hw_feat->tx_fifo_size + 7);
}

static void axgbe_init_all_fptrs(struct axgbe_port *pdata)
{
	axgbe_init_function_ptrs_dev(&pdata->hw_if);
	axgbe_init_function_ptrs_phy(&pdata->phy_if);
	axgbe_init_function_ptrs_i2c(&pdata->i2c_if);
	pdata->vdata->init_function_ptrs_phy_impl(&pdata->phy_if);
}

static void axgbe_set_counts(struct axgbe_port *pdata)
{
	/* Set all the function pointers */
	axgbe_init_all_fptrs(pdata);

	/* Populate the hardware features */
	axgbe_get_all_hw_features(pdata);

	/* Set default max values if not provided */
	if (!pdata->tx_max_channel_count)
		pdata->tx_max_channel_count = pdata->hw_feat.tx_ch_cnt;
	if (!pdata->rx_max_channel_count)
		pdata->rx_max_channel_count = pdata->hw_feat.rx_ch_cnt;

	if (!pdata->tx_max_q_count)
		pdata->tx_max_q_count = pdata->hw_feat.tx_q_cnt;
	if (!pdata->rx_max_q_count)
		pdata->rx_max_q_count = pdata->hw_feat.rx_q_cnt;

	/* Calculate the number of Tx and Rx rings to be created
	 *  -Tx (DMA) Channels map 1-to-1 to Tx Queues so set
	 *   the number of Tx queues to the number of Tx channels
	 *   enabled
	 *  -Rx (DMA) Channels do not map 1-to-1 so use the actual
	 *   number of Rx queues or maximum allowed
	 */
	pdata->tx_ring_count = RTE_MIN(pdata->hw_feat.tx_ch_cnt,
				     pdata->tx_max_channel_count);
	pdata->tx_ring_count = RTE_MIN(pdata->tx_ring_count,
				     pdata->tx_max_q_count);

	pdata->tx_q_count = pdata->tx_ring_count;

	pdata->rx_ring_count = RTE_MIN(pdata->hw_feat.rx_ch_cnt,
				     pdata->rx_max_channel_count);

	pdata->rx_q_count = RTE_MIN(pdata->hw_feat.rx_q_cnt,
				  pdata->rx_max_q_count);
}

static void axgbe_default_config(struct axgbe_port *pdata)
{
	pdata->pblx8 = DMA_PBL_X8_ENABLE;
	pdata->tx_sf_mode = MTL_TSF_ENABLE;
	pdata->tx_threshold = MTL_TX_THRESHOLD_64;
	pdata->tx_pbl = DMA_PBL_32;
	pdata->tx_osp_mode = DMA_OSP_ENABLE;
	pdata->rx_sf_mode = MTL_RSF_ENABLE;
	pdata->rx_threshold = MTL_RX_THRESHOLD_64;
	pdata->rx_pbl = DMA_PBL_32;
	pdata->pause_autoneg = 1;
	pdata->tx_pause = 0;
	pdata->rx_pause = 0;
	pdata->phy_speed = SPEED_UNKNOWN;
	pdata->power_down = 0;
}

static int
pci_device_cmp(const struct rte_device *dev, const void *_pci_id)
{
	const struct rte_pci_device *pdev = RTE_DEV_TO_PCI_CONST(dev);
	const struct rte_pci_id *pcid = _pci_id;

	if (pdev->id.vendor_id == AMD_PCI_VENDOR_ID &&
			pdev->id.device_id == pcid->device_id)
		return 0;
	return 1;
}

static bool
pci_search_device(int device_id)
{
	struct rte_bus *pci_bus;
	struct rte_pci_id dev_id;

	dev_id.device_id = device_id;
	pci_bus = rte_bus_find_by_name("pci");
	return (pci_bus != NULL) &&
		(pci_bus->find_device(NULL, pci_device_cmp, &dev_id) != NULL);
}

/*
 * It returns 0 on success.
 */
static int
eth_axgbe_dev_init(struct rte_eth_dev *eth_dev)
{
	PMD_INIT_FUNC_TRACE();
	struct axgbe_port *pdata;
	struct rte_pci_device *pci_dev;
	uint32_t reg, mac_lo, mac_hi;
	uint32_t len;
	int ret;

	eth_dev->dev_ops = &axgbe_eth_dev_ops;

	/*
	 * For secondary processes, we don't initialise any further as primary
	 * has already done this work.
	 */
	if (rte_eal_process_type() != RTE_PROC_PRIMARY)
		return 0;

	pdata = eth_dev->data->dev_private;
	/* initial state */
	axgbe_set_bit(AXGBE_DOWN, &pdata->dev_state);
	axgbe_set_bit(AXGBE_STOPPED, &pdata->dev_state);
	pdata->eth_dev = eth_dev;

	pci_dev = RTE_DEV_TO_PCI(eth_dev->device);
	pdata->pci_dev = pci_dev;

	/*
	 * Use root complex device ID to differentiate RV AXGBE vs SNOWY AXGBE
	 */
	if (pci_search_device(AMD_PCI_RV_ROOT_COMPLEX_ID)) {
		pdata->xpcs_window_def_reg = PCS_V2_RV_WINDOW_DEF;
		pdata->xpcs_window_sel_reg = PCS_V2_RV_WINDOW_SELECT;
	} else {
		pdata->xpcs_window_def_reg = PCS_V2_WINDOW_DEF;
		pdata->xpcs_window_sel_reg = PCS_V2_WINDOW_SELECT;
	}

	pdata->xgmac_regs =
		(void *)pci_dev->mem_resource[AXGBE_AXGMAC_BAR].addr;
	pdata->xprop_regs = (void *)((uint8_t *)pdata->xgmac_regs
				     + AXGBE_MAC_PROP_OFFSET);
	pdata->xi2c_regs = (void *)((uint8_t *)pdata->xgmac_regs
				    + AXGBE_I2C_CTRL_OFFSET);
	pdata->xpcs_regs = (void *)pci_dev->mem_resource[AXGBE_XPCS_BAR].addr;

	/* version specific driver data*/
	if (pci_dev->id.device_id == AMD_PCI_AXGBE_DEVICE_V2A)
		pdata->vdata = &axgbe_v2a;
	else
		pdata->vdata = &axgbe_v2b;

	/* Configure the PCS indirect addressing support */
	reg = XPCS32_IOREAD(pdata, pdata->xpcs_window_def_reg);
	pdata->xpcs_window = XPCS_GET_BITS(reg, PCS_V2_WINDOW_DEF, OFFSET);
	pdata->xpcs_window <<= 6;
	pdata->xpcs_window_size = XPCS_GET_BITS(reg, PCS_V2_WINDOW_DEF, SIZE);
	pdata->xpcs_window_size = 1 << (pdata->xpcs_window_size + 7);
	pdata->xpcs_window_mask = pdata->xpcs_window_size - 1;

	PMD_INIT_LOG(DEBUG,
		     "xpcs window :%x, size :%x, mask :%x ", pdata->xpcs_window,
		     pdata->xpcs_window_size, pdata->xpcs_window_mask);
	XP_IOWRITE(pdata, XP_INT_EN, 0x1fffff);

	/* Retrieve the MAC address */
	mac_lo = XP_IOREAD(pdata, XP_MAC_ADDR_LO);
	mac_hi = XP_IOREAD(pdata, XP_MAC_ADDR_HI);
	pdata->mac_addr.addr_bytes[0] = mac_lo & 0xff;
	pdata->mac_addr.addr_bytes[1] = (mac_lo >> 8) & 0xff;
	pdata->mac_addr.addr_bytes[2] = (mac_lo >> 16) & 0xff;
	pdata->mac_addr.addr_bytes[3] = (mac_lo >> 24) & 0xff;
	pdata->mac_addr.addr_bytes[4] = mac_hi & 0xff;
	pdata->mac_addr.addr_bytes[5] = (mac_hi >> 8)  &  0xff;

	len = RTE_ETHER_ADDR_LEN * AXGBE_MAX_MAC_ADDRS;
	eth_dev->data->mac_addrs = rte_zmalloc("axgbe_mac_addr", len, 0);

	if (!eth_dev->data->mac_addrs) {
		PMD_INIT_LOG(ERR,
			     "Failed to alloc %u bytes needed to "
			     "store MAC addresses", len);
		return -ENOMEM;
	}

	/* Allocate memory for storing hash filter MAC addresses */
	len = RTE_ETHER_ADDR_LEN * AXGBE_MAX_HASH_MAC_ADDRS;
	eth_dev->data->hash_mac_addrs = rte_zmalloc("axgbe_hash_mac_addr",
						    len, 0);

	if (eth_dev->data->hash_mac_addrs == NULL) {
		PMD_INIT_LOG(ERR,
			     "Failed to allocate %d bytes needed to "
			     "store MAC addresses", len);
		return -ENOMEM;
	}

	if (!rte_is_valid_assigned_ether_addr(&pdata->mac_addr))
		rte_eth_random_addr(pdata->mac_addr.addr_bytes);

	/* Copy the permanent MAC address */
	rte_ether_addr_copy(&pdata->mac_addr, &eth_dev->data->mac_addrs[0]);

	/* Clock settings */
	pdata->sysclk_rate = AXGBE_V2_DMA_CLOCK_FREQ;
	pdata->ptpclk_rate = AXGBE_V2_PTP_CLOCK_FREQ;

	/* Set the DMA coherency values */
	pdata->coherent = 1;
	pdata->axdomain = AXGBE_DMA_OS_AXDOMAIN;
	pdata->arcache = AXGBE_DMA_OS_ARCACHE;
	pdata->awcache = AXGBE_DMA_OS_AWCACHE;

	/* Set the maximum channels and queues */
	reg = XP_IOREAD(pdata, XP_PROP_1);
	pdata->tx_max_channel_count = XP_GET_BITS(reg, XP_PROP_1, MAX_TX_DMA);
	pdata->rx_max_channel_count = XP_GET_BITS(reg, XP_PROP_1, MAX_RX_DMA);
	pdata->tx_max_q_count = XP_GET_BITS(reg, XP_PROP_1, MAX_TX_QUEUES);
	pdata->rx_max_q_count = XP_GET_BITS(reg, XP_PROP_1, MAX_RX_QUEUES);

	/* Set the hardware channel and queue counts */
	axgbe_set_counts(pdata);

	/* Set the maximum fifo amounts */
	reg = XP_IOREAD(pdata, XP_PROP_2);
	pdata->tx_max_fifo_size = XP_GET_BITS(reg, XP_PROP_2, TX_FIFO_SIZE);
	pdata->tx_max_fifo_size *= 16384;
	pdata->tx_max_fifo_size = RTE_MIN(pdata->tx_max_fifo_size,
					  pdata->vdata->tx_max_fifo_size);
	pdata->rx_max_fifo_size = XP_GET_BITS(reg, XP_PROP_2, RX_FIFO_SIZE);
	pdata->rx_max_fifo_size *= 16384;
	pdata->rx_max_fifo_size = RTE_MIN(pdata->rx_max_fifo_size,
					  pdata->vdata->rx_max_fifo_size);
	/* Issue software reset to DMA */
	ret = pdata->hw_if.exit(pdata);
	if (ret)
		PMD_DRV_LOG(ERR, "hw_if->exit EBUSY error\n");

	/* Set default configuration data */
	axgbe_default_config(pdata);

	/* Set default max values if not provided */
	if (!pdata->tx_max_fifo_size)
		pdata->tx_max_fifo_size = pdata->hw_feat.tx_fifo_size;
	if (!pdata->rx_max_fifo_size)
		pdata->rx_max_fifo_size = pdata->hw_feat.rx_fifo_size;

	pdata->tx_desc_count = AXGBE_MAX_RING_DESC;
	pdata->rx_desc_count = AXGBE_MAX_RING_DESC;
	pthread_mutex_init(&pdata->xpcs_mutex, NULL);
	pthread_mutex_init(&pdata->i2c_mutex, NULL);
	pthread_mutex_init(&pdata->an_mutex, NULL);
	pthread_mutex_init(&pdata->phy_mutex, NULL);

	ret = pdata->phy_if.phy_init(pdata);
	if (ret) {
		rte_free(eth_dev->data->mac_addrs);
		eth_dev->data->mac_addrs = NULL;
		return ret;
	}

	rte_intr_callback_register(&pci_dev->intr_handle,
				   axgbe_dev_interrupt_handler,
				   (void *)eth_dev);
	PMD_INIT_LOG(DEBUG, "port %d vendorID=0x%x deviceID=0x%x",
		     eth_dev->data->port_id, pci_dev->id.vendor_id,
		     pci_dev->id.device_id);

	return 0;
}

static int
eth_axgbe_dev_uninit(struct rte_eth_dev *eth_dev)
{
	struct rte_pci_device *pci_dev;

	PMD_INIT_FUNC_TRACE();

	if (rte_eal_process_type() != RTE_PROC_PRIMARY)
		return 0;

	pci_dev = RTE_DEV_TO_PCI(eth_dev->device);
	eth_dev->dev_ops = NULL;
	eth_dev->rx_pkt_burst = NULL;
	eth_dev->tx_pkt_burst = NULL;
	axgbe_dev_clear_queues(eth_dev);

	/* disable uio intr before callback unregister */
	rte_intr_disable(&pci_dev->intr_handle);
	rte_intr_callback_unregister(&pci_dev->intr_handle,
				     axgbe_dev_interrupt_handler,
				     (void *)eth_dev);

	return 0;
}

static int eth_axgbe_pci_probe(struct rte_pci_driver *pci_drv __rte_unused,
	struct rte_pci_device *pci_dev)
{
	return rte_eth_dev_pci_generic_probe(pci_dev,
		sizeof(struct axgbe_port), eth_axgbe_dev_init);
}

static int eth_axgbe_pci_remove(struct rte_pci_device *pci_dev)
{
	return rte_eth_dev_pci_generic_remove(pci_dev, eth_axgbe_dev_uninit);
}

static struct rte_pci_driver rte_axgbe_pmd = {
	.id_table = pci_id_axgbe_map,
	.drv_flags = RTE_PCI_DRV_NEED_MAPPING,
	.probe = eth_axgbe_pci_probe,
	.remove = eth_axgbe_pci_remove,
};

RTE_PMD_REGISTER_PCI(net_axgbe, rte_axgbe_pmd);
RTE_PMD_REGISTER_PCI_TABLE(net_axgbe, pci_id_axgbe_map);
RTE_PMD_REGISTER_KMOD_DEP(net_axgbe, "* igb_uio | uio_pci_generic | vfio-pci");

RTE_INIT(axgbe_init_log)
{
	axgbe_logtype_init = rte_log_register("pmd.net.axgbe.init");
	if (axgbe_logtype_init >= 0)
		rte_log_set_level(axgbe_logtype_init, RTE_LOG_NOTICE);
	axgbe_logtype_driver = rte_log_register("pmd.net.axgbe.driver");
	if (axgbe_logtype_driver >= 0)
		rte_log_set_level(axgbe_logtype_driver, RTE_LOG_NOTICE);
}
