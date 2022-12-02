/*
 * Copyright (C) 2021-2022, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * This file provides a group of functions that are used to track PHY register
 * writes by intercepting io_write16 function calls.  Once the registers are
 * tracked, their value can be saved at a given time spot, and restored later
 * as required.  This implementation is useful to capture any PHY register
 * programing in any function during PHY initialization.
 */

#include <stdint.h>

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

/*
 * MAX_NUM_RET_REGS default Max number of retention registers
 *
 * This define is only used by the PhyInit Register interface to define the max
 * amount of registered that can be saved. The user may increase this variable
 * as desired if a larger number of registers need to be restored.
 */
#if STM32MP_DDR3_TYPE || STM32MP_DDR4_TYPE
#define MAX_NUM_RET_REGS	129
#elif STM32MP_LPDDR4_TYPE
#define MAX_NUM_RET_REGS	282
#endif /* STM32MP_LPDDR4_TYPE */

/*
 * Array of Address/value pairs used to store register values for the purpose
 * of retention restore.
 */
reg_addr_val_t retreglist[MAX_NUM_RET_REGS];

int numregsaved = 0;    /* Current Number of registers saved. */
int tracken = 1;        /* Enabled tracking of registers */

/*
 * Tags a register if tracking is enabled in the register
 * interface
 *
 * during PhyInit registers writes, keeps track of address
 * for the purpose of restoring the PHY register state during PHY
 * retention exit process.  Tracking can be turned on/off via the
 * ddrphy_phyinit_reginterface starttrack, stoptrack instructions. By
 * default tracking is always turned on.
 *
 * \return 0 on success.
 */
int ddrphy_phyinit_trackreg(uint32_t adr)
{
	int regindx = 0;

	/* Return if tracking is disabled */
	if (!tracken) {
		return 0;
	}

	/* Search register address within the array */
	for (regindx = 0; regindx < numregsaved; regindx++) {
		if (retreglist[regindx].address == adr) {
			/* Register found */
			return 0;
		}
	}

	/* Register not found, so add it. */
	if (numregsaved > MAX_NUM_RET_REGS) {
		ERROR("[ddrphy_phyinit_reginterface:ddrphy_phyinit_trackreg]\n");
		ERROR("Max Number of Restore Registers reached: %d.\n", numregsaved);
		ERROR("Please recompile PhyInit with larger MAX_NUM_RET_REG value.\n");
		return -1;
	}

	retreglist[regindx].address = adr;
	numregsaved++;

	return 0;
}

/*
 * Register interface function used to track, save and restore retention registers.
 *
 * ### Usage
 * Register tracking is enabled by calling:
 *
 *  \code
 *  ddrphy_phyinit_reginterface(starttrack,0,0);
 *  \endcode
 *
 * from this point on any call to ddrphy_phyinit_usercustom_io_write16() in
 * return will be capture by the register interface via a call to
 * ddrphy_phyinit_trackreg(). Tracking is disabled by calling:
 *
 *  \code
 *  ddrphy_phyinit_reginterface(stoptrack,0,0);
 *  \endcode
 *
 * On calling this function, register write via
 * ddrphy_phyinit_usercustom_io_write16 are no longer tracked until a
 * starttrack call is made.  Once all the register write are complete, saveRegs
 * command can be issue to save register values into the internal data array of
 * the register interface.  Upon retention exit restoreregs are command can be
 * used to issue register write commands to the PHY based on values stored in
 * the array.
 *  \code
 *   ddrphy_phyinit_reginterface(saveregs,0,0);
 *   ddrphy_phyinit_reginterface(restoreregs,0,0);
 *  \endcode
 * \return 0 on success.
 */
int ddrphy_phyinit_reginterface(reginstr myreginstr,
                                __attribute__((unused))uint32_t adr,
                                __attribute__((unused))uint16_t dat)
{
	if (myreginstr == saveregs) {
		int regindx;

		/*
		 * go through all the tracked registers, issue a register read and place
		 * the result in the data structure for future recovery.
		 */
		for (regindx = 0; regindx < numregsaved; regindx++) {
			uint16_t data;

			data = mmio_read_16((uintptr_t)(DDRPHYC_BASE +
							(4 * retreglist[regindx].address)));
			retreglist[regindx].value = data;
		}

		return 0;
	} else if (myreginstr == restoreregs) {
		int regindx;

		/*
		 * write PHY registers based on Address, Data value pairs stores in
		 * retreglist
		 */
		for (regindx = 0; regindx < numregsaved; regindx++) {
			mmio_write_16((uintptr_t)(DDRPHYC_BASE + 4 * retreglist[regindx].address),
				      retreglist[regindx].value);
		}

		return 0;
	} else if (myreginstr == starttrack) { /* Enable tracking */
		tracken = 1;
		return 0;
	} else if (myreginstr == stoptrack) { /* Disable tracking */
		tracken = 0;
		return 0;
	} else if (myreginstr == dumpregs) { /* Dump restore state to file. */
		/* TBD */
		return 0;
	} else if (myreginstr == importregs) { /* import register state from file. */
		/* TBD */
		return 0;
	} else {
		/* future instructions. */
		return -1;
	}
}
