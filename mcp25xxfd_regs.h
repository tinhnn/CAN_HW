/* SPDX-License-Identifier: GPL-2.0 */

/* CAN bus driver for Microchip 25XXFD CAN Controller with SPI Interface
 *
 * Copyright 2019 Martin Sperl <kernel@martin.sperl.org>
 */

#ifndef __MCP25XXFD_REGS_H
#define __MCP25XXFD_REGS_H

#include <linux/bitops.h>

/* some constants derived from the datasheets */
#define MCP25XXFD_OST_DELAY_MS		3
#define MCP25XXFD_MIN_CLOCK_FREQUENCY	1000000
#define MCP25XXFD_MAX_CLOCK_FREQUENCY	40000000
#define MCP25XXFD_PLL_MULTIPLIER	10
#define MCP25XXFD_AUTO_PLL_MAX_CLOCK_FREQUENCY				\
	(MCP25XXFD_MAX_CLOCK_FREQUENCY / MCP25XXFD_PLL_MULTIPLIER)
#define MCP25XXFD_SCLK_DIVIDER		2

/* GPIO, clock, ecc related register definitions of Controller itself */
#define MCP25XXFD_SFR_BASE(x)			(0xE00 + (x))
#define MCP25XXFD_OSC				MCP25XXFD_SFR_BASE(0x00)
#  define MCP25XXFD_OSC_PLLEN			BIT(0)
#  define MCP25XXFD_OSC_OSCDIS			BIT(2)
#  define MCP25XXFD_OSC_SCLKDIV			BIT(4)
#  define MCP25XXFD_OSC_CLKODIV_BITS		2
#  define MCP25XXFD_OSC_CLKODIV_SHIFT		5
#  define MCP25XXFD_OSC_CLKODIV_MASK					\
	GENMASK(MCP25XXFD_OSC_CLKODIV_SHIFT				\
		+ MCP25XXFD_OSC_CLKODIV_BITS - 1,			\
		MCP25XXFD_OSC_CLKODIV_SHIFT)
#  define MCP25XXFD_OSC_CLKODIV_10		3
#  define MCP25XXFD_OSC_CLKODIV_4		2
#  define MCP25XXFD_OSC_CLKODIV_2		1
#  define MCP25XXFD_OSC_CLKODIV_1		0
#  define MCP25XXFD_OSC_PLLRDY			BIT(8)
#  define MCP25XXFD_OSC_OSCRDY			BIT(10)
#  define MCP25XXFD_OSC_SCLKRDY			BIT(12)
#define MCP25XXFD_IOCON				MCP25XXFD_SFR_BASE(0x04)
#  define MCP25XXFD_IOCON_TRIS0			BIT(0)
#  define MCP25XXFD_IOCON_TRIS1			BIT(1)
#  define MCP25XXFD_IOCON_XSTBYEN		BIT(6)
#  define MCP25XXFD_IOCON_LAT0			BIT(8)
#  define MCP25XXFD_IOCON_LAT1			BIT(9)
#  define MCP25XXFD_IOCON_GPIO0			BIT(16)
#  define MCP25XXFD_IOCON_GPIO1			BIT(17)
#  define MCP25XXFD_IOCON_PM0			BIT(24)
#  define MCP25XXFD_IOCON_PM1			BIT(25)
#  define MCP25XXFD_IOCON_TXCANOD		BIT(28)
#  define MCP25XXFD_IOCON_SOF			BIT(29)
#  define MCP25XXFD_IOCON_INTOD			BIT(30)
#define MCP25XXFD_CRC				MCP25XXFD_SFR_BASE(0x08)
#  define MCP25XXFD_CRC_MASK			GENMASK(15, 0)
#  define MCP25XXFD_CRC_CRCERRIE		BIT(16)
#  define MCP25XXFD_CRC_FERRIE			BIT(17)
#  define MCP25XXFD_CRC_CRCERRIF		BIT(24)
#  define MCP25XXFD_CRC_FERRIF			BIT(25)
#define MCP25XXFD_ECCCON			MCP25XXFD_SFR_BASE(0x0C)
#  define MCP25XXFD_ECCCON_ECCEN		BIT(0)
#  define MCP25XXFD_ECCCON_SECIE		BIT(1)
#  define MCP25XXFD_ECCCON_DEDIE		BIT(2)
#  define MCP25XXFD_ECCCON_PARITY_BITS		6
#  define MCP25XXFD_ECCCON_PARITY_SHIFT		8
#  define MCP25XXFD_ECCCON_PARITY_MASK					\
	GENMASK(MCP25XXFD_ECCCON_PARITY_SHIFT				\
		+ MCP25XXFD_ECCCON_PARITY_BITS - 1,			\
		MCP25XXFD_ECCCON_PARITY_SHIFT)
#define MCP25XXFD_ECCSTAT			MCP25XXFD_SFR_BASE(0x10)
#  define MCP25XXFD_ECCSTAT_SECIF		BIT(1)
#  define MCP25XXFD_ECCSTAT_DEDIF		BIT(2)
#  define MCP25XXFD_ECCSTAT_ERRADDR_SHIFT	8
#  define MCP25XXFD_ECCSTAT_ERRADDR_MASK				\
	GENMASK(MCP25XXFD_ECCSTAT_ERRADDR_SHIFT + 11,			\
		MCP25XXFD_ECCSTAT_ERRADDR_SHIFT)

#define MCP25XXFD_DEVID				MCP25XXFD_SFR_BASE(0x14)
#  define MCP25XXFD_DEVID_REV_BITS		4
#  define MCP25XXFD_DEVID_REV_SHIFT		0
#  define MCP25XXFD_DEVID_REV_MASK					\
	GENMASK(MCP25XXFD_DEVID_REV_SHIFT +				\
		MCP25XXFD_DEVID_REV_BITS - 1,				\
		MCP25XXFD_DEVID_REV_SHIFT)
#  define MCP25XXFD_DEVID_ID_BITS		4
#  define MCP25XXFD_DEVID_ID_SHIFT		4
#  define MCP25XXFD_DEVID_ID_MASK					\
	GENMASK(MCP25XXFD_DEVID_ID_SHIFT +				\
		MCP25XXFD_DEVID_ID_BITS - 1,				\
		MCP25XXFD_DEVID_ID_SHIFT)

/* CAN related register definitions of Controller CAN block */
#define MCP25XXFD_CAN_SFR_BASE(x)		(0x000 + (x))
#define MCP25XXFD_CAN_CON						\
	MCP25XXFD_CAN_SFR_BASE(0x00)
#  define MCP25XXFD_CAN_CON_DNCNT_BITS		5
#  define MCP25XXFD_CAN_CON_DNCNT_SHIFT		0
#  define MCP25XXFD_CAN_CON_DNCNT_MASK					\
	GENMASK(MCP25XXFD_CAN_CON_DNCNT_SHIFT +				\
		MCP25XXFD_CAN_CON_DNCNT_BITS - 1,			\
		MCP25XXFD_CAN_CON_DNCNT_SHIFT)
#  define MCP25XXFD_CAN_CON_ISOCRCEN		BIT(5)
#  define MCP25XXFD_CAN_CON_PXEDIS		BIT(6)
#  define MCP25XXFD_CAN_CON_WAKFIL		BIT(8)
#  define MCP25XXFD_CAN_CON_WFT_BITS		2
#  define MCP25XXFD_CAN_CON_WFT_SHIFT		9
#  define MCP25XXFD_CAN_CON_WFT_MASK					\
	GENMASK(MCP25XXFD_CAN_CON_WFT_SHIFT +				\
		MCP25XXFD_CAN_CON_WFT_BITS - 1,				\
		MCP25XXFD_CAN_CON_WFT_SHIFT)
#  define MCP25XXFD_CAN_CON_BUSY		BIT(11)
#  define MCP25XXFD_CAN_CON_BRSDIS		BIT(12)
#  define MCP25XXFD_CAN_CON_RTXAT		BIT(16)
#  define MCP25XXFD_CAN_CON_ESIGM		BIT(17)
#  define MCP25XXFD_CAN_CON_SERR2LOM		BIT(18)
#  define MCP25XXFD_CAN_CON_STEF		BIT(19)
#  define MCP25XXFD_CAN_CON_TXQEN		BIT(20)
#  define MCP25XXFD_CAN_CON_OPMODE_BITS		3
#  define MCP25XXFD_CAN_CON_OPMOD_SHIFT		21
#  define MCP25XXFD_CAN_CON_OPMOD_MASK					\
	GENMASK(MCP25XXFD_CAN_CON_OPMOD_SHIFT +				\
		MCP25XXFD_CAN_CON_OPMODE_BITS - 1,			\
		MCP25XXFD_CAN_CON_OPMOD_SHIFT)
#  define MCP25XXFD_CAN_CON_REQOP_BITS		3
#  define MCP25XXFD_CAN_CON_REQOP_SHIFT		24
#  define MCP25XXFD_CAN_CON_REQOP_MASK					\
	GENMASK(MCP25XXFD_CAN_CON_REQOP_SHIFT +				\
		MCP25XXFD_CAN_CON_REQOP_BITS - 1,			\
		MCP25XXFD_CAN_CON_REQOP_SHIFT)
#    define MCP25XXFD_CAN_CON_MODE_MIXED	0
#    define MCP25XXFD_CAN_CON_MODE_SLEEP	1
#    define MCP25XXFD_CAN_CON_MODE_INT_LOOPBACK	2
#    define MCP25XXFD_CAN_CON_MODE_LISTENONLY	3
#    define MCP25XXFD_CAN_CON_MODE_CONFIG	4
#    define MCP25XXFD_CAN_CON_MODE_EXT_LOOPBACK	5
#    define MCP25XXFD_CAN_CON_MODE_CAN2_0	6
#    define MCP25XXFD_CAN_CON_MODE_RESTRICTED	7
#  define MCP25XXFD_CAN_CON_ABAT		BIT(27)
#  define MCP25XXFD_CAN_CON_TXBWS_BITS		3
#  define MCP25XXFD_CAN_CON_TXBWS_SHIFT		28
#  define MCP25XXFD_CAN_CON_TXBWS_MASK					\
	GENMASK(MCP25XXFD_CAN_CON_TXBWS_SHIFT +				\
		MCP25XXFD_CAN_CON_TXBWS_BITS - 1,			\
		MCP25XXFD_CAN_CON_TXBWS_SHIFT)
#  define MCP25XXFD_CAN_CON_DEFAULT					\
	(MCP25XXFD_CAN_CON_ISOCRCEN |					\
	 MCP25XXFD_CAN_CON_PXEDIS |					\
	 MCP25XXFD_CAN_CON_WAKFIL |					\
	 (3 << MCP25XXFD_CAN_CON_WFT_SHIFT) |				\
	 MCP25XXFD_CAN_CON_STEF |					\
	 MCP25XXFD_CAN_CON_TXQEN |					\
	 (MCP25XXFD_CAN_CON_MODE_CONFIG << MCP25XXFD_CAN_CON_OPMOD_SHIFT) | \
	 (MCP25XXFD_CAN_CON_MODE_CONFIG << MCP25XXFD_CAN_CON_REQOP_SHIFT))
#  define MCP25XXFD_CAN_CON_DEFAULT_MASK				\
	(MCP25XXFD_CAN_CON_DNCNT_MASK |					\
	 MCP25XXFD_CAN_CON_ISOCRCEN |					\
	 MCP25XXFD_CAN_CON_PXEDIS |					\
	 MCP25XXFD_CAN_CON_WAKFIL |					\
	 MCP25XXFD_CAN_CON_WFT_MASK |					\
	 MCP25XXFD_CAN_CON_BRSDIS |					\
	 MCP25XXFD_CAN_CON_RTXAT |					\
	 MCP25XXFD_CAN_CON_ESIGM |					\
	 MCP25XXFD_CAN_CON_SERR2LOM |					\
	 MCP25XXFD_CAN_CON_STEF |					\
	 MCP25XXFD_CAN_CON_TXQEN |					\
	 MCP25XXFD_CAN_CON_OPMOD_MASK |					\
	 MCP25XXFD_CAN_CON_REQOP_MASK |					\
	 MCP25XXFD_CAN_CON_ABAT |					\
	 MCP25XXFD_CAN_CON_TXBWS_MASK)
#define MCP25XXFD_CAN_NBTCFG			MCP25XXFD_CAN_SFR_BASE(0x04)
#  define MCP25XXFD_CAN_NBTCFG_SJW_BITS		7
#  define MCP25XXFD_CAN_NBTCFG_SJW_SHIFT	0
#  define MCP25XXFD_CAN_NBTCFG_SJW_MASK					\
	GENMASK(MCP25XXFD_CAN_NBTCFG_SJW_SHIFT +			\
		MCP25XXFD_CAN_NBTCFG_SJW_BITS - 1,			\
		MCP25XXFD_CAN_NBTCFG_SJW_SHIFT)
#  define MCP25XXFD_CAN_NBTCFG_TSEG2_BITS	7
#  define MCP25XXFD_CAN_NBTCFG_TSEG2_SHIFT	8
#  define MCP25XXFD_CAN_NBTCFG_TSEG2_MASK				\
	GENMASK(MCP25XXFD_CAN_NBTCFG_TSEG2_SHIFT +			\
		MCP25XXFD_CAN_NBTCFG_TSEG2_BITS - 1,			\
		MCP25XXFD_CAN_NBTCFG_TSEG2_SHIFT)
#  define MCP25XXFD_CAN_NBTCFG_TSEG1_BITS	8
#  define MCP25XXFD_CAN_NBTCFG_TSEG1_SHIFT	16
#  define MCP25XXFD_CAN_NBTCFG_TSEG1_MASK				\
	GENMASK(MCP25XXFD_CAN_NBTCFG_TSEG1_SHIFT +			\
		MCP25XXFD_CAN_NBTCFG_TSEG1_BITS - 1,			\
		MCP25XXFD_CAN_NBTCFG_TSEG1_SHIFT)
#  define MCP25XXFD_CAN_NBTCFG_BRP_BITS		8
#  define MCP25XXFD_CAN_NBTCFG_BRP_SHIFT	24
#  define MCP25XXFD_CAN_NBTCFG_BRP_MASK					\
	GENMASK(MCP25XXFD_CAN_NBTCFG_BRP_SHIFT +			\
		MCP25XXFD_CAN_NBTCFG_BRP_BITS - 1,			\
		MCP25XXFD_CAN_NBTCFG_BRP_SHIFT)
#define MCP25XXFD_CAN_DBTCFG			MCP25XXFD_CAN_SFR_BASE(0x08)
#  define MCP25XXFD_CAN_DBTCFG_SJW_BITS		4
#  define MCP25XXFD_CAN_DBTCFG_SJW_SHIFT	0
#  define MCP25XXFD_CAN_DBTCFG_SJW_MASK					\
	GENMASK(MCP25XXFD_CAN_DBTCFG_SJW_SHIFT +			\
		MCP25XXFD_CAN_DBTCFG_SJW_BITS - 1,			\
		MCP25XXFD_CAN_DBTCFG_SJW_SHIFT)
#  define MCP25XXFD_CAN_DBTCFG_TSEG2_BITS	4
#  define MCP25XXFD_CAN_DBTCFG_TSEG2_SHIFT	8
#  define MCP25XXFD_CAN_DBTCFG_TSEG2_MASK				\
	GENMASK(MCP25XXFD_CAN_DBTCFG_TSEG2_SHIFT +			\
		MCP25XXFD_CAN_DBTCFG_TSEG2_BITS - 1,			\
		MCP25XXFD_CAN_DBTCFG_TSEG2_SHIFT)
#  define MCP25XXFD_CAN_DBTCFG_TSEG1_BITS	5
#  define MCP25XXFD_CAN_DBTCFG_TSEG1_SHIFT	16
#  define MCP25XXFD_CAN_DBTCFG_TSEG1_MASK				\
	GENMASK(MCP25XXFD_CAN_DBTCFG_TSEG1_SHIFT +			\
		MCP25XXFD_CAN_DBTCFG_TSEG1_BITS - 1,			\
		MCP25XXFD_CAN_DBTCFG_TSEG1_SHIFT)
#  define MCP25XXFD_CAN_DBTCFG_BRP_BITS		8
#  define MCP25XXFD_CAN_DBTCFG_BRP_SHIFT	24
#  define MCP25XXFD_CAN_DBTCFG_BRP_MASK					\
	GENMASK(MCP25XXFD_CAN_DBTCFG_BRP_SHIFT +			\
		MCP25XXFD_CAN_DBTCFG_BRP_BITS - 1,			\
		MCP25XXFD_CAN_DBTCFG_BRP_SHIFT)
#define MCP25XXFD_CAN_TDC			MCP25XXFD_CAN_SFR_BASE(0x0C)
#  define MCP25XXFD_CAN_TDC_TDCV_BITS		5
#  define MCP25XXFD_CAN_TDC_TDCV_SHIFT		0
#  define MCP25XXFD_CAN_TDC_TDCV_MASK					\
	GENMASK(MCP25XXFD_CAN_TDC_TDCV_SHIFT +				\
		MCP25XXFD_CAN_TDC_TDCV_BITS - 1,			\
		MCP25XXFD_CAN_TDC_TDCV_SHIFT)
#  define MCP25XXFD_CAN_TDC_TDCO_BITS		5
#  define MCP25XXFD_CAN_TDC_TDCO_SHIFT		8
#  define MCP25XXFD_CAN_TDC_TDCO_MASK					\
	GENMASK(MCP25XXFD_CAN_TDC_TDCO_SHIFT +				\
		MCP25XXFD_CAN_TDC_TDCO_BITS - 1,			\
		MCP25XXFD_CAN_TDC_TDCO_SHIFT)
#  define MCP25XXFD_CAN_TDC_TDCMOD_BITS		2
#  define MCP25XXFD_CAN_TDC_TDCMOD_SHIFT	16
#  define MCP25XXFD_CAN_TDC_TDCMOD_MASK					\
	GENMASK(MCP25XXFD_CAN_TDC_TDCMOD_SHIFT +			\
		MCP25XXFD_CAN_TDC_TDCMOD_BITS - 1,			\
		MCP25XXFD_CAN_TDC_TDCMOD_SHIFT)
#  define MCP25XXFD_CAN_TDC_TDCMOD_DISABLED	0
#  define MCP25XXFD_CAN_TDC_TDCMOD_MANUAL	1
#  define MCP25XXFD_CAN_TDC_TDCMOD_AUTO		2
#  define MCP25XXFD_CAN_TDC_SID11EN		BIT(24)
#  define MCP25XXFD_CAN_TDC_EDGFLTEN		BIT(25)
#define MCP25XXFD_CAN_TBC			MCP25XXFD_CAN_SFR_BASE(0x10)
#define MCP25XXFD_CAN_TSCON			MCP25XXFD_CAN_SFR_BASE(0x14)
#  define MCP25XXFD_CAN_TSCON_TBCPRE_BITS	10
#  define MCP25XXFD_CAN_TSCON_TBCPRE_SHIFT	0
#  define MCP25XXFD_CAN_TSCON_TBCPRE_MASK				\
	GENMASK(MCP25XXFD_CAN_TSCON_TBCPRE_SHIFT +			\
		MCP25XXFD_CAN_TSCON_TBCPRE_BITS - 1,			\
		MCP25XXFD_CAN_TSCON_TBCPRE_SHIFT)
#  define MCP25XXFD_CAN_TSCON_TBCEN		BIT(16)
#  define MCP25XXFD_CAN_TSCON_TSEOF		BIT(17)
#  define MCP25XXFD_CAN_TSCON_TSRES		BIT(18)
#define MCP25XXFD_CAN_VEC			MCP25XXFD_CAN_SFR_BASE(0x18)
#  define MCP25XXFD_CAN_VEC_ICODE_BITS		7
#  define MCP25XXFD_CAN_VEC_ICODE_SHIFT		0
#  define MCP25XXFD_CAN_VEC_ICODE_MASK					\
	GENMASK(MCP25XXFD_CAN_VEC_ICODE_SHIFT +				\
		MCP25XXFD_CAN_VEC_ICODE_BITS - 1,			\
		MCP25XXFD_CAN_VEC_ICODE_SHIFT)
#  define MCP25XXFD_CAN_VEC_FILHIT_BITS		5
#  define MCP25XXFD_CAN_VEC_FILHIT_SHIFT	8
#  define MCP25XXFD_CAN_VEC_FILHIT_MASK					\
	GENMASK(MCP25XXFD_CAN_VEC_FILHIT_SHIFT +			\
		MCP25XXFD_CAN_VEC_FILHIT_BITS - 1,			\
		MCP25XXFD_CAN_VEC_FILHIT_SHIFT)
#  define MCP25XXFD_CAN_VEC_TXCODE_BITS		7
#  define MCP25XXFD_CAN_VEC_TXCODE_SHIFT	16
#  define MCP25XXFD_CAN_VEC_TXCODE_MASK					\
	GENMASK(MCP25XXFD_CAN_VEC_TXCODE_SHIFT +			\
		MCP25XXFD_CAN_VEC_TXCODE_BITS - 1,			\
		MCP25XXFD_CAN_VEC_TXCODE_SHIFT)
#  define MCP25XXFD_CAN_VEC_RXCODE_BITS		7
#  define MCP25XXFD_CAN_VEC_RXCODE_SHIFT	24
#  define MCP25XXFD_CAN_VEC_RXCODE_MASK					\
	GENMASK(MCP25XXFD_CAN_VEC_RXCODE_SHIFT +			\
		MCP25XXFD_CAN_VEC_RXCODE_BITS - 1,			\
		MCP25XXFD_CAN_VEC_RXCODE_SHIFT)
#define MCP25XXFD_CAN_INT			MCP25XXFD_CAN_SFR_BASE(0x1C)
#  define MCP25XXFD_CAN_INT_IF_SHIFT		0
#  define MCP25XXFD_CAN_INT_TXIF		BIT(0)
#  define MCP25XXFD_CAN_INT_RXIF		BIT(1)
#  define MCP25XXFD_CAN_INT_TBCIF		BIT(2)
#  define MCP25XXFD_CAN_INT_MODIF		BIT(3)
#  define MCP25XXFD_CAN_INT_TEFIF		BIT(4)
#  define MCP25XXFD_CAN_INT_ECCIF		BIT(8)
#  define MCP25XXFD_CAN_INT_SPICRCIF		BIT(9)
#  define MCP25XXFD_CAN_INT_TXATIF		BIT(10)
#  define MCP25XXFD_CAN_INT_RXOVIF		BIT(11)
#  define MCP25XXFD_CAN_INT_SERRIF		BIT(12)
#  define MCP25XXFD_CAN_INT_CERRIF		BIT(13)
#  define MCP25XXFD_CAN_INT_WAKIF		BIT(14)
#  define MCP25XXFD_CAN_INT_IVMIF		BIT(15)
#  define MCP25XXFD_CAN_INT_IF_MASK					\
	(MCP25XXFD_CAN_INT_TXIF |					\
	 MCP25XXFD_CAN_INT_RXIF |					\
	 MCP25XXFD_CAN_INT_TBCIF |					\
	 MCP25XXFD_CAN_INT_MODIF |					\
	 MCP25XXFD_CAN_INT_TEFIF |					\
	 MCP25XXFD_CAN_INT_ECCIF |					\
	 MCP25XXFD_CAN_INT_SPICRCIF |					\
	 MCP25XXFD_CAN_INT_TXATIF |					\
	 MCP25XXFD_CAN_INT_RXOVIF |					\
	 MCP25XXFD_CAN_INT_CERRIF |					\
	 MCP25XXFD_CAN_INT_SERRIF |					\
	 MCP25XXFD_CAN_INT_WAKIF |					\
	 MCP25XXFD_CAN_INT_IVMIF)
#  define MCP25XXFD_CAN_INT_IF_CLEAR_MASK				\
	(MCP25XXFD_CAN_INT_TBCIF  |					\
	 MCP25XXFD_CAN_INT_MODIF  |					\
	 MCP25XXFD_CAN_INT_CERRIF |					\
	 MCP25XXFD_CAN_INT_SERRIF |					\
	 MCP25XXFD_CAN_INT_WAKIF |					\
	 MCP25XXFD_CAN_INT_IVMIF)
#  define MCP25XXFD_CAN_INT_IE_SHIFT		16
#  define MCP25XXFD_CAN_INT_TXIE					\
	(MCP25XXFD_CAN_INT_TXIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_RXIE					\
	(MCP25XXFD_CAN_INT_RXIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_TBCIE					\
	(MCP25XXFD_CAN_INT_TBCIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_MODIE					\
	(MCP25XXFD_CAN_INT_MODIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_TEFIE					\
	(MCP25XXFD_CAN_INT_TEFIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_ECCIE					\
	(MCP25XXFD_CAN_INT_ECCIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_SPICRCIE					\
	(MCP25XXFD_CAN_INT_SPICRCIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_TXATIE					\
	(MCP25XXFD_CAN_INT_TXATIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_RXOVIE					\
	(MCP25XXFD_CAN_INT_RXOVIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_CERRIE					\
	(MCP25XXFD_CAN_INT_CERRIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_SERRIE					\
	(MCP25XXFD_CAN_INT_SERRIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_WAKIE					\
	(MCP25XXFD_CAN_INT_WAKIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_IVMIE					\
	(MCP25XXFD_CAN_INT_IVMIF << MCP25XXFD_CAN_INT_IE_SHIFT)
#  define MCP25XXFD_CAN_INT_IE_MASK					\
	(MCP25XXFD_CAN_INT_TXIE |					\
	 MCP25XXFD_CAN_INT_RXIE |					\
	 MCP25XXFD_CAN_INT_TBCIE |					\
	 MCP25XXFD_CAN_INT_MODIE |					\
	 MCP25XXFD_CAN_INT_TEFIE |					\
	 MCP25XXFD_CAN_INT_ECCIE |					\
	 MCP25XXFD_CAN_INT_SPICRCIE |					\
	 MCP25XXFD_CAN_INT_TXATIE |					\
	 MCP25XXFD_CAN_INT_RXOVIE |					\
	 MCP25XXFD_CAN_INT_CERRIE |					\
	 MCP25XXFD_CAN_INT_SERRIE |					\
	 MCP25XXFD_CAN_INT_WAKIE |					\
	 MCP25XXFD_CAN_INT_IVMIE)
#define MCP25XXFD_CAN_RXIF			MCP25XXFD_CAN_SFR_BASE(0x20)
#define MCP25XXFD_CAN_TXIF			MCP25XXFD_CAN_SFR_BASE(0x24)
#define MCP25XXFD_CAN_RXOVIF			MCP25XXFD_CAN_SFR_BASE(0x28)
#define MCP25XXFD_CAN_TXATIF			MCP25XXFD_CAN_SFR_BASE(0x2C)
#define MCP25XXFD_CAN_TXREQ			MCP25XXFD_CAN_SFR_BASE(0x30)
#define MCP25XXFD_CAN_TREC			MCP25XXFD_CAN_SFR_BASE(0x34)
#  define MCP25XXFD_CAN_TREC_REC_BITS		8
#  define MCP25XXFD_CAN_TREC_REC_SHIFT		0
#  define MCP25XXFD_CAN_TREC_REC_MASK					\
	GENMASK(MCP25XXFD_CAN_TREC_REC_SHIFT +				\
		MCP25XXFD_CAN_TREC_REC_BITS - 1,			\
		MCP25XXFD_CAN_TREC_REC_SHIFT)
#  define MCP25XXFD_CAN_TREC_TEC_BITS		8
#  define MCP25XXFD_CAN_TREC_TEC_SHIFT		8
#  define MCP25XXFD_CAN_TREC_TEC_MASK					\
	GENMASK(MCP25XXFD_CAN_TREC_TEC_SHIFT +				\
		MCP25XXFD_CAN_TREC_TEC_BITS - 1,			\
		MCP25XXFD_CAN_TREC_TEC_SHIFT)
#  define MCP25XXFD_CAN_TREC_EWARN		BIT(16)
#  define MCP25XXFD_CAN_TREC_RXWARN		BIT(17)
#  define MCP25XXFD_CAN_TREC_TXWARN		BIT(18)
#  define MCP25XXFD_CAN_TREC_RXBP		BIT(19)
#  define MCP25XXFD_CAN_TREC_TXBP		BIT(20)
#  define MCP25XXFD_CAN_TREC_TXBO		BIT(21)
#define MCP25XXFD_CAN_BDIAG0			MCP25XXFD_CAN_SFR_BASE(0x38)
#  define MCP25XXFD_CAN_BDIAG0_NRERRCNT_BITS	8
#  define MCP25XXFD_CAN_BDIAG0_NRERRCNT_SHIFT	0
#  define MCP25XXFD_CAN_BDIAG0_NRERRCNT_MASK				\
	GENMASK(MCP25XXFD_CAN_BDIAG0_NRERRCNT_SHIFT +			\
		MCP25XXFD_CAN_BDIAG0_NRERRCNT_BITS - 1,			\
		MCP25XXFD_CAN_BDIAG0_NRERRCNT_SHIFT)
#  define MCP25XXFD_CAN_BDIAG0_NTERRCNT_BITS	8
#  define MCP25XXFD_CAN_BDIAG0_NTERRCNT_SHIFT	8
#  define MCP25XXFD_CAN_BDIAG0_NTERRCNT_MASK				\
	GENMASK(MCP25XXFD_CAN_BDIAG0_NTERRCNT_SHIFT +			\
		MCP25XXFD_CAN_BDIAG0_NTERRCNT_BITS - 1,			\
		MCP25XXFD_CAN_BDIAG0_NTERRCNT_SHIFT)
#  define MCP25XXFD_CAN_BDIAG0_DRERRCNT_BITS	8
#  define MCP25XXFD_CAN_BDIAG0_DRERRCNT_SHIFT	16
#  define MCP25XXFD_CAN_BDIAG0_DRERRCNT_MASK				\
	GENMASK(MCP25XXFD_CAN_BDIAG0_DRERRCNT_SHIFT +			\
		MCP25XXFD_CAN_BDIAG0_DRERRCNT_BITS - 1,			\
		MCP25XXFD_CAN_BDIAG0_DRERRCNT_SHIFT)
#  define MCP25XXFD_CAN_BDIAG0_DTERRCNT_BITS	8
#  define MCP25XXFD_CAN_BDIAG0_DTERRCNT_SHIFT	24
#  define MCP25XXFD_CAN_BDIAG0_DTERRCNT_MASK				\
	GENMASK(MCP25XXFD_CAN_BDIAG0_DTERRCNT_SHIFT +			\
		MCP25XXFD_CAN_BDIAG0_DTERRCNT_BITS - 1,			\
		MCP25XXFD_CAN_BDIAG0_DTERRCNT_SHIFT)
#define MCP25XXFD_CAN_BDIAG1			MCP25XXFD_CAN_SFR_BASE(0x3C)
#  define MCP25XXFD_CAN_BDIAG1_EFMSGCNT_BITS	16
#  define MCP25XXFD_CAN_BDIAG1_EFMSGCNT_SHIFT	0
#  define MCP25XXFD_CAN_BDIAG1_EFMSGCNT_MASK				\
	GENMASK(MCP25XXFD_CAN_BDIAG1_EFMSGCNT_SHIFT +			\
		MCP25XXFD_CAN_BDIAG1_EFMSGCNT_BITS - 1,			\
		MCP25XXFD_CAN_BDIAG1_EFMSGCNT_SHIFT)
#  define MCP25XXFD_CAN_BDIAG1_NBIT0ERR		BIT(16)
#  define MCP25XXFD_CAN_BDIAG1_NBIT1ERR		BIT(17)
#  define MCP25XXFD_CAN_BDIAG1_NACKERR		BIT(18)
#  define MCP25XXFD_CAN_BDIAG1_NSTUFERR		BIT(19)
#  define MCP25XXFD_CAN_BDIAG1_NFORMERR		BIT(20)
#  define MCP25XXFD_CAN_BDIAG1_NCRCERR		BIT(21)
#  define MCP25XXFD_CAN_BDIAG1_TXBOERR		BIT(23)
#  define MCP25XXFD_CAN_BDIAG1_DBIT0ERR		BIT(24)
#  define MCP25XXFD_CAN_BDIAG1_DBIT1ERR		BIT(25)
#  define MCP25XXFD_CAN_BDIAG1_DFORMERR		BIT(27)
#  define MCP25XXFD_CAN_BDIAG1_DSTUFERR		BIT(28)
#  define MCP25XXFD_CAN_BDIAG1_DCRCERR		BIT(29)
#  define MCP25XXFD_CAN_BDIAG1_ESI		BIT(30)
#  define MCP25XXFD_CAN_BDIAG1_DLCMM		BIT(31)
#define MCP25XXFD_CAN_TEFCON			MCP25XXFD_CAN_SFR_BASE(0x40)
#  define MCP25XXFD_CAN_TEFCON_TEFNEIE		BIT(0)
#  define MCP25XXFD_CAN_TEFCON_TEFHIE		BIT(1)
#  define MCP25XXFD_CAN_TEFCON_TEFFIE		BIT(2)
#  define MCP25XXFD_CAN_TEFCON_TEFOVIE		BIT(3)
#  define MCP25XXFD_CAN_TEFCON_TEFTSEN		BIT(5)
#  define MCP25XXFD_CAN_TEFCON_UINC		BIT(8)
#  define MCP25XXFD_CAN_TEFCON_FRESET		BIT(10)
#  define MCP25XXFD_CAN_TEFCON_FSIZE_BITS	5
#  define MCP25XXFD_CAN_TEFCON_FSIZE_SHIFT	24
#  define MCP25XXFD_CAN_TEFCON_FSIZE_MASK				\
	GENMASK(MCP25XXFD_CAN_TEFCON_FSIZE_SHIFT +			\
		MCP25XXFD_CAN_TEFCON_FSIZE_BITS - 1,			\
		MCP25XXFD_CAN_TEFCON_FSIZE_SHIFT)
#define MCP25XXFD_CAN_TEFSTA			MCP25XXFD_CAN_SFR_BASE(0x44)
#  define MCP25XXFD_CAN_TEFSTA_TEFNEIF		BIT(0)
#  define MCP25XXFD_CAN_TEFSTA_TEFHIF		BIT(1)
#  define MCP25XXFD_CAN_TEFSTA_TEFFIF		BIT(2)
#  define MCP25XXFD_CAN_TEFSTA_TEVOVIF		BIT(3)
#define MCP25XXFD_CAN_TEFUA			MCP25XXFD_CAN_SFR_BASE(0x48)
#define MCP25XXFD_CAN_RESERVED			MCP25XXFD_CAN_SFR_BASE(0x4C)
#define MCP25XXFD_CAN_TXQCON			MCP25XXFD_CAN_SFR_BASE(0x50)
#  define MCP25XXFD_CAN_TXQCON_TXQNIE		BIT(0)
#  define MCP25XXFD_CAN_TXQCON_TXQEIE		BIT(2)
#  define MCP25XXFD_CAN_TXQCON_TXATIE		BIT(4)
#  define MCP25XXFD_CAN_TXQCON_TXEN		BIT(7)
#  define MCP25XXFD_CAN_TXQCON_UINC		BIT(8)
#  define MCP25XXFD_CAN_TXQCON_TXREQ		BIT(9)
#  define MCP25XXFD_CAN_TXQCON_FRESET		BIT(10)
#  define MCP25XXFD_CAN_TXQCON_TXPRI_BITS	5
#  define MCP25XXFD_CAN_TXQCON_TXPRI_SHIFT	16
#  define MCP25XXFD_CAN_TXQCON_TXPRI_MASK				\
	GENMASK(MCP25XXFD_CAN_TXQCON_TXPRI_SHIFT +			\
		MCP25XXFD_CAN_TXQCON_TXPRI_BITS - 1,			\
		MCP25XXFD_CAN_TXQCON_TXPRI_SHIFT)
#  define MCP25XXFD_CAN_TXQCON_TXAT_BITS	2
#  define MCP25XXFD_CAN_TXQCON_TXAT_SHIFT	21
#  define MCP25XXFD_CAN_TXQCON_TXAT_MASK				\
	GENMASK(MCP25XXFD_CAN_TXQCON_TXAT_SHIFT +			\
		#MCP25XXFD_CAN_TXQCON_TXAT_BITS - 1,			\
		MCP25XXFD_CAN_TXQCON_TXAT_SHIFT)
#  define MCP25XXFD_CAN_TXQCON_FSIZE_BITS	5
#  define MCP25XXFD_CAN_TXQCON_FSIZE_SHIFT	24
#  define MCP25XXFD_CAN_TXQCON_FSIZE_MASK				\
	GENMASK(MCP25XXFD_CAN_TXQCON_FSIZE_SHIFT +			\
		MCP25XXFD_CAN_TXQCON_FSIZE_BITS - 1,			\
		MCP25XXFD_CAN_TXQCON_FSIZE_SHIFT)
#  define MCP25XXFD_CAN_TXQCON_PLSIZE_BITS	3
#  define MCP25XXFD_CAN_TXQCON_PLSIZE_SHIFT	29
#  define MCP25XXFD_CAN_TXQCON_PLSIZE_MASK				\
	GENMASK(MCP25XXFD_CAN_TXQCON_PLSIZE_SHIFT +			\
		MCP25XXFD_CAN_TXQCON_PLSIZE_BITS - 1,			\
		MCP25XXFD_CAN_TXQCON_PLSIZE_SHIFT)
#    define MCP25XXFD_CAN_TXQCON_PLSIZE_8	0
#    define MCP25XXFD_CAN_TXQCON_PLSIZE_12	1
#    define MCP25XXFD_CAN_TXQCON_PLSIZE_16	2
#    define MCP25XXFD_CAN_TXQCON_PLSIZE_20	3
#    define MCP25XXFD_CAN_TXQCON_PLSIZE_24	4
#    define MCP25XXFD_CAN_TXQCON_PLSIZE_32	5
#    define MCP25XXFD_CAN_TXQCON_PLSIZE_48	6
#    define MCP25XXFD_CAN_TXQCON_PLSIZE_64	7

#define MCP25XXFD_CAN_TXQSTA			MCP25XXFD_CAN_SFR_BASE(0x54)
#  define MCP25XXFD_CAN_TXQSTA_TXQNIF		BIT(0)
#  define MCP25XXFD_CAN_TXQSTA_TXQEIF		BIT(2)
#  define MCP25XXFD_CAN_TXQSTA_TXATIF		BIT(4)
#  define MCP25XXFD_CAN_TXQSTA_TXERR		BIT(5)
#  define MCP25XXFD_CAN_TXQSTA_TXLARB		BIT(6)
#  define MCP25XXFD_CAN_TXQSTA_TXABT		BIT(7)
#  define MCP25XXFD_CAN_TXQSTA_TXQCI_BITS	5
#  define MCP25XXFD_CAN_TXQSTA_TXQCI_SHIFT	8
#  define MCP25XXFD_CAN_TXQSTA_TXQCI_MASK				\
	GENMASK(MCP25XXFD_CAN_TXQSTA_TXQCI_SHIFT +			\
		MCP25XXFD_CAN_TXQSTA_TXQCI_BITS - 1,			\
		MCP25XXFD_CAN_TXQSTA_TXQCI_SHIFT)

#define MCP25XXFD_CAN_TXQUA			MCP25XXFD_CAN_SFR_BASE(0x58)
#define MCP25XXFD_CAN_FIFOCON(x)					\
	MCP25XXFD_CAN_SFR_BASE(0x5C + 12 * ((x) - 1))
#define MCP25XXFD_CAN_FIFOCON_TFNRFNIE		BIT(0)
#define MCP25XXFD_CAN_FIFOCON_TFHRFHIE		BIT(1)
#define MCP25XXFD_CAN_FIFOCON_TFERFFIE		BIT(2)
#define MCP25XXFD_CAN_FIFOCON_RXOVIE		BIT(3)
#define MCP25XXFD_CAN_FIFOCON_TXATIE		BIT(4)
#define MCP25XXFD_CAN_FIFOCON_RXTSEN		BIT(5)
#define MCP25XXFD_CAN_FIFOCON_RTREN		BIT(6)
#define MCP25XXFD_CAN_FIFOCON_TXEN		BIT(7)
#define MCP25XXFD_CAN_FIFOCON_UINC		BIT(8)
#define MCP25XXFD_CAN_FIFOCON_TXREQ		BIT(9)
#define MCP25XXFD_CAN_FIFOCON_FRESET		BIT(10)
#  define MCP25XXFD_CAN_FIFOCON_TXPRI_BITS	5
#  define MCP25XXFD_CAN_FIFOCON_TXPRI_SHIFT	16
#  define MCP25XXFD_CAN_FIFOCON_TXPRI_MASK				\
	GENMASK(MCP25XXFD_CAN_FIFOCON_TXPRI_SHIFT +			\
		MCP25XXFD_CAN_FIFOCON_TXPRI_BITS - 1,			\
		MCP25XXFD_CAN_FIFOCON_TXPRI_SHIFT)
#  define MCP25XXFD_CAN_FIFOCON_TXAT_BITS	2
#  define MCP25XXFD_CAN_FIFOCON_TXAT_SHIFT	21
#  define MCP25XXFD_CAN_FIFOCON_TXAT_MASK				\
	GENMASK(MCP25XXFD_CAN_FIFOCON_TXAT_SHIFT +			\
		MCP25XXFD_CAN_FIFOCON_TXAT_BITS - 1,			\
		MCP25XXFD_CAN_FIFOCON_TXAT_SHIFT)
#  define MCP25XXFD_CAN_FIFOCON_TXAT_ONE_SHOT	0
#  define MCP25XXFD_CAN_FIFOCON_TXAT_THREE_SHOT	1
#  define MCP25XXFD_CAN_FIFOCON_TXAT_UNLIMITED	2
#  define MCP25XXFD_CAN_FIFOCON_FSIZE_BITS	5
#  define MCP25XXFD_CAN_FIFOCON_FSIZE_SHIFT	24
#  define MCP25XXFD_CAN_FIFOCON_FSIZE_MASK				\
	GENMASK(MCP25XXFD_CAN_FIFOCON_FSIZE_SHIFT +			\
		MCP25XXFD_CAN_FIFOCON_FSIZE_BITS - 1,			\
		MCP25XXFD_CAN_FIFOCON_FSIZE_SHIFT)
#  define MCP25XXFD_CAN_FIFOCON_PLSIZE_BITS	3
#  define MCP25XXFD_CAN_FIFOCON_PLSIZE_SHIFT	29
#  define MCP25XXFD_CAN_FIFOCON_PLSIZE_MASK				\
	GENMASK(MCP25XXFD_CAN_FIFOCON_PLSIZE_SHIFT +			\
		MCP25XXFD_CAN_FIFOCON_PLSIZE_BITS - 1,			\
		MCP25XXFD_CAN_FIFOCON_PLSIZE_SHIFT)
#define MCP25XXFD_CAN_FIFOSTA(x)					\
	MCP25XXFD_CAN_SFR_BASE(0x60 + 12 * ((x) - 1))
#  define MCP25XXFD_CAN_FIFOSTA_TFNRFNIF	BIT(0)
#  define MCP25XXFD_CAN_FIFOSTA_TFHRFHIF	BIT(1)
#  define MCP25XXFD_CAN_FIFOSTA_TFERFFIF	BIT(2)
#  define MCP25XXFD_CAN_FIFOSTA_RXOVIF		BIT(3)
#  define MCP25XXFD_CAN_FIFOSTA_TXATIF		BIT(4)
#  define MCP25XXFD_CAN_FIFOSTA_TXERR		BIT(5)
#  define MCP25XXFD_CAN_FIFOSTA_TXLARB		BIT(6)
#  define MCP25XXFD_CAN_FIFOSTA_TXABT		BIT(7)
#  define MCP25XXFD_CAN_FIFOSTA_FIFOCI_BITS	5
#  define MCP25XXFD_CAN_FIFOSTA_FIFOCI_SHIFT	8
#  define MCP25XXFD_CAN_FIFOSTA_FIFOCI_MASK				\
	GENMASK(MCP25XXFD_CAN_FIFOSTA_FIFOCI_SHIFT +			\
		MCP25XXFD_CAN_FIFOSTA_FIFOCI_BITS - 1,			\
		MCP25XXFD_CAN_FIFOSTA_FIFOCI_SHIFT)
#define MCP25XXFD_CAN_FIFOUA(x)						\
	MCP25XXFD_CAN_SFR_BASE(0x64 + 12 * ((x) - 1))
#define MCP25XXFD_CAN_FLTCON(x)						\
	MCP25XXFD_CAN_SFR_BASE(0x1D0 + ((x) & 0x1c))
#  define MCP25XXFD_CAN_FILCON_SHIFT(x)		(((x) & 3) * 8)
#  define MCP25XXFD_CAN_FILCON_BITS(x)		MCP25XXFD_CAN_FILCON_BITS_
#  define MCP25XXFD_CAN_FILCON_BITS_		4
	/* avoid macro reuse warning, so do not use GENMASK as above */
#  define MCP25XXFD_CAN_FILCON_MASK(x)					\
	(GENMASK(MCP25XXFD_CAN_FILCON_BITS_ - 1, 0) <<			\
	 MCP25XXFD_CAN_FILCON_SHIFT(x))
#  define MCP25XXFD_CAN_FIFOCON_FLTEN(x)				\
	BIT(7 + MCP25XXFD_CAN_FILCON_SHIFT(x))
#define MCP25XXFD_CAN_FLTOBJ(x)						\
	MCP25XXFD_CAN_SFR_BASE(0x1F0 + 8 * (x))
#  define MCP25XXFD_CAN_FILOBJ_SID_BITS		11
#  define MCP25XXFD_CAN_FILOBJ_SID_SHIFT	0
#  define MCP25XXFD_CAN_FILOBJ_SID_MASK					\
	GENMASK(MCP25XXFD_CAN_FILOBJ_SID_SHIFT +			\
		MCP25XXFD_CAN_FILOBJ_SID_BITS - 1,			\
		MCP25XXFD_CAN_FILOBJ_SID_SHIFT)
#  define MCP25XXFD_CAN_FILOBJ_EID_BITS		18
#  define MCP25XXFD_CAN_FILOBJ_EID_SHIFT	12
#  define MCP25XXFD_CAN_FILOBJ_EID_MASK					\
	GENMASK(MCP25XXFD_CAN_FILOBJ_EID_SHIFT +			\
		MCP25XXFD_CAN_FILOBJ_EID_BITS - 1,			\
		MCP25XXFD_CAN_FILOBJ_EID_SHIFT)
#  define MCP25XXFD_CAN_FILOBJ_SID11		BIT(29)
#  define MCP25XXFD_CAN_FILOBJ_EXIDE		BIT(30)
#define MCP25XXFD_CAN_FLTMASK(x)					\
	MCP25XXFD_CAN_SFR_BASE(0x1F4 + 8 * (x))
#  define MCP25XXFD_CAN_FILMASK_MSID_BITS	11
#  define MCP25XXFD_CAN_FILMASK_MSID_SHIFT	0
#  define MCP25XXFD_CAN_FILMASK_MSID_MASK				\
	GENMASK(MCP25XXFD_CAN_FILMASK_MSID_SHIFT +			\
		MCP25XXFD_CAN_FILMASK_MSID_BITS - 1,			\
		MCP25XXFD_CAN_FILMASK_MSID_SHIFT)
#  define MCP25XXFD_CAN_FILMASK_MEID_BITS	18
#  define MCP25XXFD_CAN_FILMASK_MEID_SHIFT	12
#  define MCP25XXFD_CAN_FILMASK_MEID_MASK				\
	GENMASK(MCP25XXFD_CAN_FILMASK_MEID_SHIFT +			\
		MCP25XXFD_CAN_FILMASK_MEID_BITS - 1,			\
		MCP25XXFD_CAN_FILMASK_MEID_SHIFT)
#  define MCP25XXFD_CAN_FILMASK_MSID11		BIT(29)
#  define MCP25XXFD_CAN_FILMASK_MIDE		BIT(30)

/* the FIFO Objects in SRAM */
#define MCP25XXFD_SRAM_SIZE 2048
#define MCP25XXFD_SRAM_ADDR(x) (0x400 + (x))

/* memory structure in sram for tx fifos */
struct mcp25xxfd_can_obj_tx {
	u32 id;
	u32 flags;
	u8 data[];
};

/* memory structure in sram for rx fifos */
struct mcp25xxfd_can_obj_rx {
	u32 id;
	u32 flags;
	u32 ts;
	u8 data[];
};

/* memory structure in sram for tef fifos */
struct mcp25xxfd_can_obj_tef {
	u32 id;
	u32 flags;
	u32 ts;
};

#define MCP25XXFD_CAN_OBJ_ID_SID_BITS		11
#define MCP25XXFD_CAN_OBJ_ID_SID_SHIFT		0
#define MCP25XXFD_CAN_OBJ_ID_SID_MASK					\
	GENMASK(MCP25XXFD_CAN_OBJ_ID_SID_SHIFT +			\
		MCP25XXFD_CAN_OBJ_ID_SID_BITS - 1,			\
		MCP25XXFD_CAN_OBJ_ID_SID_SHIFT)
#define MCP25XXFD_CAN_OBJ_ID_EID_BITS		18
#define MCP25XXFD_CAN_OBJ_ID_EID_SHIFT		11
#define MCP25XXFD_CAN_OBJ_ID_EID_MASK					\
	GENMASK(MCP25XXFD_CAN_OBJ_ID_EID_SHIFT +			\
		MCP25XXFD_CAN_OBJ_ID_EID_BITS - 1,			\
		MCP25XXFD_CAN_OBJ_ID_EID_SHIFT)
#define MCP25XXFD_CAN_OBJ_ID_SID_BIT11		BIT(29)

#define MCP25XXFD_CAN_OBJ_FLAGS_DLC_BITS	4
#define MCP25XXFD_CAN_OBJ_FLAGS_DLC_SHIFT	0
#define MCP25XXFD_CAN_OBJ_FLAGS_DLC_MASK				\
	GENMASK(MCP25XXFD_CAN_OBJ_FLAGS_DLC_SHIFT +			\
		MCP25XXFD_CAN_OBJ_FLAGS_DLC_BITS - 1,			\
		MCP25XXFD_CAN_OBJ_FLAGS_DLC_SHIFT)
#define MCP25XXFD_CAN_OBJ_FLAGS_IDE		BIT(4)
#define MCP25XXFD_CAN_OBJ_FLAGS_RTR		BIT(5)
#define MCP25XXFD_CAN_OBJ_FLAGS_BRS		BIT(6)
#define MCP25XXFD_CAN_OBJ_FLAGS_FDF		BIT(7)
#define MCP25XXFD_CAN_OBJ_FLAGS_ESI		BIT(8)
#define MCP25XXFD_CAN_OBJ_FLAGS_SEQ_BITS	7
#define MCP25XXFD_CAN_OBJ_FLAGS_SEQ_SHIFT	9
#define MCP25XXFD_CAN_OBJ_FLAGS_SEQ_MASK				\
	GENMASK(MCP25XXFD_CAN_OBJ_FLAGS_SEQ_SHIFT +			\
		MCP25XXFD_CAN_OBJ_FLAGS_SEQ_BITS - 1,			\
		MCP25XXFD_CAN_OBJ_FLAGS_SEQ_SHIFT)
/* the mcp2518 has an extended number of SEQ bits */
#define MCP25XXFD_CAN_OBJ_FLAGS_SEQX_BITS	23
#define MCP25XXFD_CAN_OBJ_FLAGS_SEQX_MASK				\
	GENMASK(MCP25XXFD_CAN_OBJ_FLAGS_SEQ_SHIFT +			\
		MCP25XXFD_CAN_OBJ_FLAGS_SEQX_BITS - 1,			\
		MCP25XXFD_CAN_OBJ_FLAGS_SEQ_SHIFT)
#define MCP25XXFD_CAN_OBJ_FLAGS_FILHIT_BITS	11
#define MCP25XXFD_CAN_OBJ_FLAGS_FILHIT_SHIFT	5
#define MCP25XXFD_CAN_OBJ_FLAGS_FILHIT_MASK				\
	GENMASK(MCP25XXFD_CAN_FLAGS_FILHIT_SHIFT +			\
		MCP25XXFD_CAN_FLAGS_FILHIT_BITS - 1,			\
		MCP25XXFD_CAN_FLAGS_FILHIT_SHIFT)

/* custom status error */
#define MCP25XXFD_CAN_ERR_DATA7_MCP25XXFD_SERR_RX BIT(0)
#define MCP25XXFD_CAN_ERR_DATA7_MCP25XXFD_SERR_TX BIT(1)
#define MCP25XXFD_CAN_ERR_DATA7_MCP25XXFD_ECC	  BIT(2)

#endif /* __MCP25XXFD_REGS_H */