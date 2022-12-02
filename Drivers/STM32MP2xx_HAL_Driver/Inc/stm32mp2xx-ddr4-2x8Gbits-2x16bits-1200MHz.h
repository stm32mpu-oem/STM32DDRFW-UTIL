// SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause
/*
 * Copyright (C) 2022, STMicroelectronics - All Rights Reserved
 */

/*
 * STM32MP257D/F VALID3 board configuration
 * DDR4 2x8Gbits 2x16bits 1200MHz
 *
 * References used:
 * - MT40A512M16LY-062EIT:E from MICRON
 * - NT5AD512M16C4-JRI from NANYA
 *
 * memclk	1199MHz 	(2x DFI clock) + range check
 * speed_bin	Worse		from JEDEC
 * width	32		32: full width / 16: half width
 * density	8Gbits		(per 16bit device)
 * addressing	RBC		row/bank interleaving
 * RDBI		No		Read DBI
 */

#ifndef STM32MP2XX_DDR4_2x8GBITS_2x16BITS_1200MHZ_H
#define STM32MP2XX_DDR4_2x8GBITS_2x16BITS_1200MHZ_H

#define DDR_MEM_NAME	"DDR4 2x8Gbits 2x16bits 1200MHz"
#define DDR_MEM_SPEED	1200000
#define DDR_MEM_SIZE	0x80000000

#define DDR_MSTR 0x01040010
#define DDR_MRCTRL0 0x00000030
#define DDR_MRCTRL1 0x00000000
#define DDR_MRCTRL2 0x00000000
#define DDR_DERATEEN 0x00000000
#define DDR_DERATEINT 0x0124B980
#define DDR_DERATECTL 0x00000000
#define DDR_PWRCTL 0x00000028
#define DDR_PWRTMG 0x00130001
#define DDR_HWLPCTL 0x00000002
#define DDR_RFSHCTL0 0x00210010
#define DDR_RFSHCTL1 0x00000000
#define DDR_RFSHCTL3 0x00000000
#define DDR_RFSHTMG 0x009200D2
#define DDR_RFSHTMG1 0x008C0000
#define DDR_CRCPARCTL0 0x00000000
#define DDR_CRCPARCTL1 0x00001000
#define DDR_INIT0 0xC0020002
#define DDR_INIT1 0x00010002
#define DDR_INIT2 0x00000D00
#define DDR_INIT3 0x09400103
#define DDR_INIT4 0x00180000
#define DDR_INIT5 0x00100004
#define DDR_INIT6 0x00080440
#define DDR_INIT7 0x0000080F
#define DDR_DIMMCTL 0x00000000
#define DDR_RANKCTL 0x0000066F
#define DDR_DRAMTMG0 0x11152815
#define DDR_DRAMTMG1 0x0004051E
#define DDR_DRAMTMG2 0x0609060D
#define DDR_DRAMTMG3 0x0050400C
#define DDR_DRAMTMG4 0x0904050A
#define DDR_DRAMTMG5 0x06060403
#define DDR_DRAMTMG6 0x02020005
#define DDR_DRAMTMG7 0x00000606
#define DDR_DRAMTMG8 0x04040C07
#define DDR_DRAMTMG9 0x0002040A
#define DDR_DRAMTMG10 0x001C180A
#define DDR_DRAMTMG11 0x4408021C
#define DDR_DRAMTMG12 0x0C020010
#define DDR_DRAMTMG13 0x1C200004
#define DDR_DRAMTMG14 0x000000A0
#define DDR_DRAMTMG15 0x00000000
#define DDR_ZQCTL0 0x01000040
#define DDR_ZQCTL1 0x2000492E
#define DDR_ZQCTL2 0x00000000
#define DDR_DFITMG0 0x038F8209
#define DDR_DFITMG1 0x00080303
#define DDR_DFILPCFG0 0x07004111
#define DDR_DFILPCFG1 0x000000F0
#define DDR_DFIUPD0 0xC0300018
#define DDR_DFIUPD1 0x005700B4
#define DDR_DFIUPD2 0x80000000
#define DDR_DFIMISC 0x00000041
#define DDR_DFITMG2 0x00000F09
#define DDR_DFITMG3 0x00000000
#define DDR_DBICTL 0x00000001
#define DDR_DFIPHYMSTR 0x80000000
#define DDR_ADDRMAP0 0x0000001F
#define DDR_ADDRMAP1 0x003F0909
#define DDR_ADDRMAP2 0x00000000
#define DDR_ADDRMAP3 0x00000000
#define DDR_ADDRMAP4 0x00001F1F
#define DDR_ADDRMAP5 0x070F0707
#define DDR_ADDRMAP6 0x07070707
#define DDR_ADDRMAP7 0x00000F0F
#define DDR_ADDRMAP8 0x00003F08
#define DDR_ADDRMAP9 0x07070707
#define DDR_ADDRMAP10 0x07070707
#define DDR_ADDRMAP11 0x00000007
#define DDR_ODTCFG 0x06000618
#define DDR_ODTMAP 0x00000001
#define DDR_SCHED 0x00000F00
#define DDR_SCHED1 0x000000FF
#define DDR_PERFHPR1 0x0F000001
#define DDR_PERFLPR1 0x0F00007F
#define DDR_PERFWR1 0x01000200
#define DDR_DBG0 0x00000000
#define DDR_DBG1 0x00000000
#define DDR_DBGCMD 0x00000000
#define DDR_SWCTL 0x00000002
#define DDR_POISONCFG 0x00000000
#define DDR_PCCFG 0x00000000
#define DDR_PCFGR_0 0x00004100
#define DDR_PCFGW_0 0x00004100
#define DDR_PCTRL_0 0x00000000
#define DDR_PCFGQOS0_0 0x00200007
#define DDR_PCFGQOS1_0 0x01000100
#define DDR_PCFGWQOS0_0 0x00000C07
#define DDR_PCFGWQOS1_0 0x02000200
#define DDR_PCFGR_1 0x00004100
#define DDR_PCFGW_1 0x00004100
#define DDR_PCTRL_1 0x00000000
#define DDR_PCFGQOS0_1 0x00200007
#define DDR_PCFGQOS1_1 0x01000180
#define DDR_PCFGWQOS0_1 0x00000C07
#define DDR_PCFGWQOS1_1 0x04000400

#define DDR_UIB_DRAMTYPE 0x00000000
#define DDR_UIB_DIMMTYPE 0x00000004
#define DDR_UIB_LP4XMODE 0x00000000
#define DDR_UIB_NUMDBYTE 0x00000004
#define DDR_UIB_NUMACTIVEDBYTEDFI0 0x00000004
#define DDR_UIB_NUMACTIVEDBYTEDFI1 0x00000000
#define DDR_UIB_NUMANIB 0x00000008
#define DDR_UIB_NUMRANK_DFI0 0x00000001
#define DDR_UIB_NUMRANK_DFI1 0x00000001
#define DDR_UIB_DRAMDATAWIDTH 0x00000010
#define DDR_UIB_NUMPSTATES 0x00000001
#define DDR_UIB_FREQUENCY_0 0x000004AF
#define DDR_UIB_PLLBYPASS_0 0x00000000
#define DDR_UIB_DFIFREQRATIO_0 0x00000001
#define DDR_UIB_DFI1EXISTS 0x00000001
#define DDR_UIB_TRAIN2D 0x00000000
#define DDR_UIB_HARDMACROVER 0x00000003
#define DDR_UIB_READDBIENABLE_0 0x00000000
#define DDR_UIB_DFIMODE 0x00000000

#define DDR_UIA_LP4RXPREAMBLEMODE_0 0x00000000
#define DDR_UIA_LP4POSTAMBLEEXT_0 0x00000000
#define DDR_UIA_D4RXPREAMBLELENGTH_0 0x00000000
#define DDR_UIA_D4TXPREAMBLELENGTH_0 0x00000000
#define DDR_UIA_EXTCALRESVAL 0x00000000
#define DDR_UIA_IS2TTIMING_0 0x00000000
#define DDR_UIA_ODTIMPEDANCE_0 0x00000035
#define DDR_UIA_TXIMPEDANCE_0 0x00000028
#define DDR_UIA_ATXIMPEDANCE 0x00000028
#define DDR_UIA_MEMALERTEN 0x00000000
#define DDR_UIA_MEMALERTPUIMP 0x00000000
#define DDR_UIA_MEMALERTVREFLEVEL 0x00000000
#define DDR_UIA_MEMALERTSYNCBYPASS 0x00000000
#define DDR_UIA_DISDYNADRTRI_0 0x00000001
#define DDR_UIA_PHYMSTRTRAININTERVAL_0 0x00000000
#define DDR_UIA_PHYMSTRMAXREQTOACK_0 0x00000000
#define DDR_UIA_WDQSEXT 0x00000000
#define DDR_UIA_CALINTERVAL 0x00000009
#define DDR_UIA_CALONCE 0x00000000
#define DDR_UIA_LP4RL_0 0x00000000
#define DDR_UIA_LP4WL_0 0x00000000
#define DDR_UIA_LP4WLS_0 0x00000000
#define DDR_UIA_LP4DBIRD_0 0x00000000
#define DDR_UIA_LP4DBIWR_0 0x00000000
#define DDR_UIA_LP4NWR_0 0x00000000
#define DDR_UIA_LP4LOWPOWERDRV 0x00000000
#define DDR_UIA_DRAMBYTESWAP 0x00000000
#define DDR_UIA_RXENBACKOFF 0x00000000
#define DDR_UIA_TRAINSEQUENCECTRL 0x00000000
#define DDR_UIA_SNPSUMCTLOPT 0x00000000
#define DDR_UIA_SNPSUMCTLF0RC5X_0 0x00000000
#define DDR_UIA_TXSLEWRISEDQ_0 0x0000000F
#define DDR_UIA_TXSLEWFALLDQ_0 0x0000000F
#define DDR_UIA_TXSLEWRISEAC 0x0000000F
#define DDR_UIA_TXSLEWFALLAC 0x0000000F
#define DDR_UIA_DISABLERETRAINING 0x00000001
#define DDR_UIA_DISABLEPHYUPDATE 0x00000000
#define DDR_UIA_ENABLEHIGHCLKSKEWFIX 0x00000000
#define DDR_UIA_DISABLEUNUSEDADDRLNS 0x00000001
#define DDR_UIA_PHYINITSEQUENCENUM 0x00000000
#define DDR_UIA_ENABLEDFICSPOLARITYFIX 0x00000000
#define DDR_UIA_PHYVREF 0x0000005E
#define DDR_UIA_SEQUENCECTRL_0 0x0000031F

#define DDR_UIM_MR0_0 0x00000940
#define DDR_UIM_MR1_0 0x00000103
#define DDR_UIM_MR2_0 0x00000018
#define DDR_UIM_MR3_0 0x00000000
#define DDR_UIM_MR4_0 0x00000008
#define DDR_UIM_MR5_0 0x00000440
#define DDR_UIM_MR6_0 0x0000080F
#define DDR_UIM_MR11_0 0x00000000
#define DDR_UIM_MR12_0 0x00000000
#define DDR_UIM_MR13_0 0x00000000
#define DDR_UIM_MR14_0 0x00000000
#define DDR_UIM_MR22_0 0x00000000

#define DDR_UIS_SWIZZLE_0 0x0000000C
#define DDR_UIS_SWIZZLE_1 0x00000005
#define DDR_UIS_SWIZZLE_2 0x00000013
#define DDR_UIS_SWIZZLE_3 0x0000001A
#define DDR_UIS_SWIZZLE_4 0x00000009
#define DDR_UIS_SWIZZLE_5 0x00000003
#define DDR_UIS_SWIZZLE_6 0x00000001
#define DDR_UIS_SWIZZLE_7 0x00000019
#define DDR_UIS_SWIZZLE_8 0x00000007
#define DDR_UIS_SWIZZLE_9 0x00000004
#define DDR_UIS_SWIZZLE_10 0x0000000A
#define DDR_UIS_SWIZZLE_11 0x0000000D
#define DDR_UIS_SWIZZLE_12 0x00000014
#define DDR_UIS_SWIZZLE_13 0x00000000
#define DDR_UIS_SWIZZLE_14 0x00000000
#define DDR_UIS_SWIZZLE_15 0x00000000
#define DDR_UIS_SWIZZLE_16 0x00000000
#define DDR_UIS_SWIZZLE_17 0x00000000
#define DDR_UIS_SWIZZLE_18 0x00000006
#define DDR_UIS_SWIZZLE_19 0x0000000B
#define DDR_UIS_SWIZZLE_20 0x00000000
#define DDR_UIS_SWIZZLE_21 0x00000000
#define DDR_UIS_SWIZZLE_22 0x00000000
#define DDR_UIS_SWIZZLE_23 0x00000008
#define DDR_UIS_SWIZZLE_24 0x00000002
#define DDR_UIS_SWIZZLE_25 0x00000018
#define DDR_UIS_SWIZZLE_26 0x1A13050C
#define DDR_UIS_SWIZZLE_27 0x19010309
#define DDR_UIS_SWIZZLE_28 0x0D0A0407
#define DDR_UIS_SWIZZLE_29 0x00000014
#define DDR_UIS_SWIZZLE_30 0x000B0600
#define DDR_UIS_SWIZZLE_31 0x02080000
#define DDR_UIS_SWIZZLE_32 0x00000018
#define DDR_UIS_SWIZZLE_33 0x00000000
#define DDR_UIS_SWIZZLE_34 0x00000000
#define DDR_UIS_SWIZZLE_35 0x00000000
#define DDR_UIS_SWIZZLE_36 0x00000000
#define DDR_UIS_SWIZZLE_37 0x00000000
#define DDR_UIS_SWIZZLE_38 0x00000000
#define DDR_UIS_SWIZZLE_39 0x00000000
#define DDR_UIS_SWIZZLE_40 0x00000000
#define DDR_UIS_SWIZZLE_41 0x00000000
#define DDR_UIS_SWIZZLE_42 0x00000000
#define DDR_UIS_SWIZZLE_43 0x00000000

#define DDR_PLL_SOURCE RCC_PLLSOURCE_HSE
#define DDR_PLL_MODE 0
#define DDR_PLL_FBDIV 59
#define DDR_PLL_FREFDIV 1
#define DDR_PLL_FRACIN 0xF3B8CA
#define DDR_PLL_POSTDIV1 4
#define DDR_PLL_POSTDIV2 1
#define DDR_PLL_STATE RCC_PLL_ON
#define DDR_PLL_SSM_MODE RCC_PLL_CENTERSPREAD
#define DDR_PLL_SSM_SPREAD 0
#define DDR_PLL_SSM_DIVVAL 0

#endif
