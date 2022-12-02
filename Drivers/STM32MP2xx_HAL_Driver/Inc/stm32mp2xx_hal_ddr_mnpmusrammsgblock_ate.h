/*
 * Copyright (C) 2021-2022, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _MNPMUSRAMMSGBLOCK_ATE_H
#define _MNPMUSRAMMSGBLOCK_ATE_H

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
// General defines
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

// Basic type typedefs

#include <stdint.h>

// ATE firmware revision

#define PMU_ATE_INTERNAL_REV0 0x0600
#define PMU_ATE_INTERNAL_REV1 0x2020


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
// Message block related defines
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

// TestsToRun encoding

#define REVISION_CHECK_TEST   0x0001
#define IMPEDANCE_CAL_TEST    0x0002
#define PLL_LOCK_TEST         0x0004
#define LCDL_LINEARITY_TEST   0x0008
#define AC_LOOPBACK_TEST      0x0010
#define DAT_1D_LOOPBACK_TEST  0x0020
#define DAT_2D_LOOPBACK_TEST  0x0040
#define BURN_IN_TEST          0x0080

// TestOptions encoding

#define TEST_OPTION_PLL_LOCK_INCREASE   0x0001
#define TEST_OPTION_PLL_RESET_INCREASE  0x0002
#define TEST_OPTION_PWR_SAVE_DISABLE    0x0004
#define TEST_OPTION_AC_PINS_PRBS        0x0008
#define TEST_OPTION_REG_RESTORE_DISABLE 0x0010
#define TEST_OPTION_DELAY_SET_DISABLE   0x8000


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
// Message Block definition for the ATE firmware
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

typedef struct _pmu_smb_ddr_1d_t {

  /////////////////////////////////////////
  // General ATE Firmware Inputs / Outputs
  /////////////////////////////////////////

  uint16_t TestsToRun;  // Byte Offset: 0x0 / CSR Address: 0x54000
                        // TestsToRun[0]    = DMEM / IMEM revision check
                        // TestsToRun[1]    = Impedance Calibration
                        // TestsToRun[2]    = PLL Lock
                        // TestsToRun[3]    = LCDL Linearity
                        // TestsToRun[4]    = Address / Command Loopback
                        // TestsToRun[5]    = Data Loopback 1D
                        // TestsToRun[6]    = Data Loopback 2D
                        // TestsToRun[7]    = Burn-In
                        // TestsToRun[15:8] = Reserved (must be written to 0)
  uint16_t PassFailResults;  // Byte Offset: 0x2 / CSR Address: 0x54001
                             // Bit value of 0 = fail / 1 = pass
                             // PassFailResults[0]    = DMEM / IMEM revision check
                             // PassFailResults[1]    = Impedance Calibration
                             // PassFailResults[2]    = PLL Lock
                             // PassFailResults[3]    = LCDL Linearity
                             // PassFailResults[4]    = Address / Command Loopback
                             // PassFailResults[5]    = Data Loopback 1D
                             // PassFailResults[6]    = Data Loopback 2D 
                             // PassFailResults[7]    = Burn-In
                             // PassFailResults[15:8] = Reserved (will be 0)
  uint16_t TestOptions;  // Byte Offset: 0x4 / CSR Address: 0x54002
                         // TestOptions[0]    = PLL lock time increase (must be written to 0 unless directed by Synopsys)
                         // TestOptions[1]    = PLL reset time increase (must be written to 0 unless directed by Synopsys)
                         // TestOptions[2]    = 0 - Power Savings features enabled; 1 - Power Savings features disabled.
                         // TestOptions[3]    = Requires TestOptions[2] to be set to 1; 
                         //                     0 - Normal A/C command signals on AC pins; 1 - PRBS signals on AC pins
                         // TestOptions[14:4] = Reserved (must be written to 0)
                         // TestOptions[15]   = Delay control - Causes the data loopback tests to not set delays for 
                         //                     elements that are not scanned as part of the test. Leaves these values 
                         //                     at user settings
  uint16_t Technology;  // Byte Offset: 0x6 / CSR Address: 0x54003
                        // Must be set to 0x0000 unless told otherwise for a given technology

  uint32_t AteImemRevision;  // Byte Offset: 0x8 / CSR Address: 0x54004
                             // PMU firmware revision ID of the IMEM image
                             // After ATE firmware is run, this address will contain 
                             // the revision ID of the ATE firmware's IMEM image. 
                             // Please reference this revision ID when filing support 
                             // cases with Synopsys.
  uint32_t AteDmemRevision;  // Byte Offset: 0xc / CSR Address: 0x54006
                             // PMU firmware revision ID of the DMEM image
                             // After ATE firmware is run, this address will contain 
                             // the revision ID of the ATE firmware's DMEM image. 
                             // Please reference this revision ID when filing support 
                             // cases with Synopsys.
  uint8_t  NumDbytes;  // Byte Offset: 0x10 / CSR Address: 0x54008
                       // Number of Dbytes in the PHY
  uint8_t  NumAnibs;  // Byte Offset: 0x11 / CSR Address: 0x54008
                      // Number of Anibs in the PHY
  uint8_t  NumBitsPerDbyte;  // Byte Offset: 0x12 / CSR Address: 0x54009
                             // 
  uint8_t  X4Mode;  // Byte Offset: 0x13 / CSR Address: 0x54009
                    // x4 Mode
                    //    0x0 = x8 mode
                    //    0x1 = x4 mode
  uint8_t  CalDrvStr0;  // Byte Offset: 0x14 / CSR Address: 0x5400a
                        // CalDrvStr0 Value
  uint8_t  Vref;  // Byte Offset: 0x15 / CSR Address: 0x5400a
                  // Value used to set CSR GlobalVrefInDac.
  uint16_t DfiClkFreq;  // Byte Offset: 0x16 / CSR Address: 0x5400b
                        // DFI Clock frequency in MHz
                        // For example enter 0x0320 for 800MHz.
  uint16_t TxImpedanceCtrl0;  // Byte Offset: 0x18 / CSR Address: 0x5400c
                           // See CSR TxImpedanceCtrl0 for description of contents.
  uint16_t TxImpedanceCtrl1;  // Byte Offset: 0x1a / CSR Address: 0x5400d
                           // See CSR TxImpedanceCtrl1 for description of contents.
  uint16_t TxImpedanceCtrl2;  // Byte Offset: 0x1c / CSR Address: 0x5400e
                           // See CSR TxImpedanceCtrl2 for description of contents.
  uint16_t ATxImpedance;  // Byte Offset: 0x1e / CSR Address: 0x5400f
                          // See CSR of the same name for description of contents.
  uint16_t MinLoopbackPower;  // Byte Offset: 0x20 / CSR Address: 0x54010
                              // Used by Data and AC Loopback tests to serialize testing of the dbytes/acx4 instances.
                              // That is, it tests one dbyte/acx4 at a time and configures unused dbytes/acx4 for 
                              // lower power. This trades off power for test execution time.


  ///////////////////////////////////////////////
  // Impedance Calibration Test Inputs
  ///////////////////////////////////////////////

  uint8_t  ContinuousCal;  // Byte Offset: 0x22 / CSR Address: 0x54011
                           // Continuous Calibration
                           //     0x0 = Do not do continuous calibration
                           //     0x1 = Do continuous calibration
  uint8_t  CalInterval;  // Byte Offset: 0x23 / CSR Address: 0x54011
                         // CalInterval of CalRate CSR used in continuous cal
                         //     See CalRate CSR description for more information.


  ///////////////////////////////////////////////
  // Pll Lock Test Inputs
  ///////////////////////////////////////////////

  uint8_t  PllLockCountMinimum;  // Byte Offset: 0x24 / CSR Address: 0x54012
                                 // The minimum number of times the PLL is found to be locked
                                 // for the test to pass.

  uint8_t  MemClkToggle;  // Byte Offset: 0x25 / CSR Address: 0x54012
                         // MEMCLK toggle
                         //      0x0 = MEMCLK does not toggle
                         //      0x1 = MEMCLK toggles at 2*DFICLK
                         //      0x2 = MEMCLK toggles at DFICLK / 2
                         //      0x3 = MEMCLK toggles at DFICLK / 4
                         //      0x4 = MEMCLK toggles at DFICLK / 8
                         //      0x5 = MEMCLK toggles at DFICLK / 16
                         //      0x6 = MEMCLK toggles at DFICLK / 24
                         //            All other values reserved.

  uint16_t MemClkTime;  // Byte Offset: 0x26 / CSR Address: 0x54013
                        // Time in microseconds to toggle MEMCLK
                        // Setting to 0xFFFF will cause
                        // the clock to run infinitely. The uC must be reset
                        // to stop if in the infinite mode.


  /////////////////////////////////////////
  // LCDL Linearity Test Inputs
  /////////////////////////////////////////

  uint16_t LcdlClksToRun;  // Byte Offset: 0x28 / CSR Address: 0x54014
                           // Clock cycles to run for each measurement
  uint16_t LcdlStartPhase;  // Byte Offset: 0x2a / CSR Address: 0x54015
                            // Start Phase (0-511 decimal)
  uint16_t LcdlEndPhase;  // Byte Offset: 0x2c / CSR Address: 0x54016
                          // End Phase (0-511 decimal)
  uint8_t  LcdlStride;  // Byte Offset: 0x2e / CSR Address: 0x54017
                        // Stride 1 to 100, 11 recommended
                        //      0x00 = Use recommended value of 11
                        // 0x01-0x64 = Use this value for stride
                        //             All other values reserved
  uint8_t  LcdlPassPercent;  // Byte Offset: 0x2f / CSR Address: 0x54017
                             // Percentage of spec values to consider pass / fail
                             //       100 (decimal) = 100% = matches spec
                             // Numbers smaller than 100 tighten the tolerance
                             // Numbers larger than 100 loosen the tolerance

  uint16_t LcdlObserveCfg[4];  // Byte Offset: 0x30 / CSR Address: 0x54018
                               // LCDL Linearity Plot - LCDL selection inputs


  /////////////////////////////////////////
  // AC Loopback Test Inputs
  /////////////////////////////////////////

  uint8_t  AcLoopLaneMask[6];  // Byte Offset: 0x38 / CSR Address: 0x5401c

  uint16_t AcLoopClksToRun;  // Byte Offset: 0x3e / CSR Address: 0x5401f
                             // Clock cycles to run AC loopback
  uint8_t  AcLoopDataRate;  // Byte Offset: 0x40 / CSR Address: 0x54020
                            // Data Rate 
                            //    0x0 = Single data rate pattern
                            //    0x1 = Dual data rate pattern

  uint8_t  AcLoopCoreLoopBk;  // Byte Offset: 0x41 / CSR Address: 0x54020
                              // Pad / Core loopback
                              //    0x0 = Pad loopback
                              //    0x1 = Core loopback
  uint8_t  AcMinEyeWidth;  // Byte Offset: 0x42 / CSR Address: 0x54021
                           // Required Eye width in the units of 1/32 UI
  uint8_t  Alignment0RSVD;  // Byte Offset: 0x43 / CSR Address: 0x54021
                            // Field to align following data fields. Must be written to 0.
                            // Reserved for future use. Must be written to 0.


  /////////////////////////////////////////
  // Data Loopback Test Inputs
  /////////////////////////////////////////

  uint16_t DatLoopClksToRun;  // Byte Offset: 0x44 / CSR Address: 0x54022
                              // Pattern length
  uint16_t DatLoopCoreLoopBk;  // Byte Offset: 0x46 / CSR Address: 0x54023
                               // Pad / Core loopback
                               //    0x0 = Pad loopback
                               //    0x1 = Core loopback
  uint16_t TxSlewRate;  // Byte Offset: 0x48 / CSR Address: 0x54024
                        // See CSR of the same name for description of contents.
  uint16_t DqDqsRcvCntrl;  // Byte Offset: 0x4a / CSR Address: 0x54025
                           // See CSR of the same name for description of contents.
  uint16_t TxDqsDly;  // Byte Offset: 0x4c / CSR Address: 0x54026
  uint16_t RxEnDly;  // Byte Offset: 0x4e / CSR Address: 0x54027
  uint16_t RxPBDly;  // Byte Offset: 0x50 / CSR Address: 0x54028
  uint16_t VrefDAC0;  // Byte Offset: 0x52 / CSR Address: 0x54029
                      // Vref used during the 1D data loopback measurement
                      // See CSR of the same name for description of contents.

  uint8_t  DatLoopCoarseStart;  // Byte Offset: 0x54 / CSR Address: 0x5402a
                                // Starting coarse value for the Data loopback search
  uint8_t  DatLoopCoarseEnd;  // Byte Offset: 0x55 / CSR Address: 0x5402a
                              // Ending coarse value for the Data loopback search
  uint8_t  DatLoopIncrement;  // Byte Offset: 0x56 / CSR Address: 0x5402b
                              // Value to increment delay by for the Data loopback search
                              // This value is in fine delay values.
  uint8_t  DatLoopMinEyeWidth;  // Byte Offset: 0x57 / CSR Address: 0x5402b
                                // Minimum Eye width for data loopback tests
  uint8_t  DatLoop2dByte;  // Byte Offset: 0x58 / CSR Address: 0x5402c
                           // Byte to test for 2D loopback
  uint8_t  DatLoop2dBit;  // Byte Offset: 0x59 / CSR Address: 0x5402c
                          // Bit to test for 2D loopback
  uint8_t  DatLoop2dVrefStart;  // Byte Offset: 0x5a / CSR Address: 0x5402d
                                // Initial value of Vref used during the 2D loopback measurement
  uint8_t  DatLoop2dVrefEnd;  // Byte Offset: 0x5b / CSR Address: 0x5402d
                              // Upper bound of Vref used during the 2D loopback measurement
  uint8_t  DatLoop2dVrefIncr;  // Byte Offset: 0x5c / CSR Address: 0x5402e
                               // Vref Increment size (1-63) for 2D loopback measurement

  uint8_t  RxEnbOffset;  // Byte Offset: 0x5d / CSR Address: 0x5402e
                         // Positive MemClk offset applied to RxEnb after training. Setting this
                         // to zero results in RxEnb being trained as it would in a real system.
                         // Non-zero value result in the initial DQS pulses being skipped. The
                         // number of pulses skipped is equal to the value set here. Setting this to
                         // non-zero values can improve the data loopback eye by skipping the initial
                         // DQS pulses, which can be narrower than normal because the bus is at its
                         // maximum idle value rather than active steady state.


  /////////////////////////////////////////
  // Impedance Calibration Test Results
  /////////////////////////////////////////

  uint16_t TxCalBinP;  // Byte Offset: 0x5e / CSR Address: 0x5402f
                       // Output from Impedance Calibration
  uint16_t TxCalBinN;  // Byte Offset: 0x60 / CSR Address: 0x54030
                       // Output from Impedance Calibration
                       // See CSR of the same name for description of contents.
  uint16_t CalPExt;  // Byte Offset: 0x62 / CSR Address: 0x54031
                     // Output from Impedance Calibration
                     // See CSR of the same name for description of contents.
  uint16_t CalNInt;  // Byte Offset: 0x64 / CSR Address: 0x54032
                     // Output from Impedance Calibration
                     // See CSR of the same name for description of contents.
  uint16_t CalCmpr5;  // Byte Offset: 0x66 / CSR Address: 0x54033
                      // Output from Impedance Calibration
                      // See CSR of the same name for description of contents.


  /////////////////////////////////////////
  // PLL / LCDL Test Results
  /////////////////////////////////////////

  uint16_t PLLResults;  // Byte Offset: 0x68 / CSR Address: 0x54034
                        // Contains the number of times the PLL was found to be locked
                        // Will be set to 0 if the PLL failed to lock

  uint16_t LcdlResults[10];  // Byte Offset: 0x6a / CSR Address: 0x54035
                             // Defined as LcdlResults[DbyteNum]
                             // Bit[LcdlNumber] will be set if the corresponding LCDL range check failed.
                             // The bit vector is indexed are:
                             //
                             //*15 = Dbyte RxClk1T
                             //*14 = Dbyte RxClk1C
                             //*13 = Dbyte RxClk0T
                             //*12 = Dbyte RxClk0C
                             // 11 = Dbyte RxEn1
                             // 10 = Dbyte RxEn0
                             // 9 = Dbyte TxLn9 (dqs-lower)
                             // 8 = Dbyte TxLn8 (dm/dqs-upper)
                             // 7 = Dbyte TxLn7 (dq7)
                             // 6 = Dbyte TxLn6 (dq6)
                             // 5 = Dbyte TxLn5 (dq5)
                             // 4 = Dbyte TxLn4 (dq4)
                             // 3 = Dbyte TxLn3 (dq3)
                             // 2 = Dbyte TxLn2 (dq2)
                             // 1 = Dbyte TxLn1 (dq1)
                             // 0 = Dbyte TxLn0 (dq0)
                             //
                             // Note that BDLs are not checked for range because they are not locked to the frequency.

  uint16_t LcdlResultsAcx4;  // Byte Offset: 0x7e / CSR Address: 0x5403f
                             // Bit[Acx4Num] will be set if the corresponding ACX4 LCDL range check failed.


  /////////////////////////////////////////
  // LCDL Linearity Test Results
  /////////////////////////////////////////

  uint16_t LcdlErrCnt[25][10];  // Byte Offset: 0x80 / CSR Address: 0x54040
                                // 
                                // Defined as: LcdlErrCnt[LcdlNumber][DbyteNum]
                                // Contains how many points failed linearity for each LCDL
                                // 
                                // where LcdlNumber is encoded as:
                                // 
                                //    0 = Dbyte TxLn0 (dq0)
                                //    1 = Dbyte TxLn1 (dq1)
                                //    2 = Dbyte TxLn2 (dq2)
                                //    3 = Dbyte TxLn3 (dq3)
                                //    4 = Dbyte TxLn4 (dq4)
                                //    5 = Dbyte TxLn5 (dq5)
                                //    6 = Dbyte TxLn6 (dq6)
                                //    7 = Dbyte TxLn7 (dq7)
                                //    8 = Dbyte TxLn8 (dm/dqs-upper)
                                //    9 = Dbyte TxLn9 (dqs-lower)
                                //   10 = Dbyte RxEn0
                                //   11 = Dbyte RxEn1
                                //   12 = Dbyte RxClk0T
                                //   13 = Dbyte RxClk1T
                                //   14 = Dbyte RxClk0C
                                //   15 = Dbyte RxClk1C
                                //   16 = Dbyte BDL RxLn0 (dq0)
                                //   17 = Dbyte BDL RxLn1 (dq1)
                                //   18 = Dbyte BDL RxLn2 (dq2)
                                //   19 = Dbyte BDL RxLn3 (dq3)
                                //   20 = Dbyte BDL RxLn4 (dq4)
                                //   21 = Dbyte BDL RxLn5 (dq5)
                                //   22 = Dbyte BDL RxLn6 (dq6)
                                //   23 = Dbyte BDL RxLn7 (dq7)
                                //   24 = Dbyte BDL RxLn8 (dbi)

  uint16_t LcdlErrCntByAcx4[12];  // Byte Offset: 0x274 / CSR Address: 0x5413a
                                  // 
                                  // Defined as: LcdlErrCntByAcx4[Acx4Num]
                                  // Contains how many points failed linearity for each LCDL


  uint16_t Lcdl_count_values[4][512];  // Byte Offset: 0x28c / CSR Address: 0x54146
                                       // LCDL Linearity Plotting  Ring Oscillator Edge Count Values


  /////////////////////////////////////////
  // AC Loopback Test Results
  /////////////////////////////////////////

  uint32_t Alignment1RSVD;  // Byte Offset: 0x128c / CSR Address: 0x54946
                            // Field to align following data fields. Must be written to 0.
                            // Reserved for future use. Must be written to 0.

  uint64_t AcLoopbackStuckatResults;  // Byte Offset: 0x1290 / CSR Address: 0x54948
                                      // Stuckat results. Each bit indicates whether that
                                      // lane failed stuckat testing. For example, if bit 4
                                      // is set to 1, it means that lane 4 (Acx4 instance 1,
                                      // lane 0) failed stuckat testing.

  uint64_t AcLoopbackBitmap[48];  // Byte Offset: 0x1298 / CSR Address: 0x5494c
                                  // Address / Command loopback eye bitmap indexed by lane
                                  // AcLoopbackBitmapByLane[LaneNumber]


  /////////////////////////////////////////
  // Data Loopback 1D Test Results
  /////////////////////////////////////////

  uint32_t Alignment2RSVD;  // Byte Offset: 0x1418 / CSR Address: 0x54a0c
                            // Field to align following data fields. Must be written to 0.
                            // Reserved for future use. Must be written to 0.

  uint16_t Alignment3RSVD;  // Byte Offset: 0x141c / CSR Address: 0x54a0e

  uint16_t DataLoopbackRxEnbVal[10][2];  // Byte Offset: 0x141e / CSR Address: 0x54a0f
                                         // Data loopback RxEnable value indexed by Dbyte and Nibble 
                                         // Defined as DataLoopbackRxEnbVal[DbyteNumber][NibbleNumber]
                                         // DataLoopbackRxEnbVal[DbyteNumber][0] is for DQ[3:0] for DbyteNumber
                                         // DataLoopbackRxEnbVal[DbyteNumber][1] is for DQ[7:4] and DM/DBI for DbyteNumber

  uint8_t  DataLoopbackCoarse[10][9];  // Byte Offset: 0x1446 / CSR Address: 0x54a23
                                       // Data loopback eye bitmap starting coarse value indexed by Dbyte and Lane 
                                       // Defined as DataLoopbackCoarse[DbyteNumber][LaneNumber]
                                       // DataLoopbackCoarse[DbyteNumber][7:0] are DQ[7:0] for DbyteNumber
                                       // DataLoopbackCoarse[DbyteNumber][8] is DM/DBI for DbyteNumber

  uint64_t DataLoopbackBitmap[10][9];  // Byte Offset: 0x14a0 / CSR Address: 0x54a50
                                       // Data loopback eye bitmap indexed by Dbyte and Lane 
                                       // Defined as DataLoopbackBitmap[DbyteNumber][LaneNumber]
                                       // DataLoopbackBitmap[DbyteNumber][7:0] are DQ[7:0] for DbyteNumber
                                       // DataLoopbackBitmap[DbyteNumber][8] is DM/DBI for DbyteNumber

 
  /////////////////////////////////////////
  // Data Loopback 2D Test Results
  /////////////////////////////////////////

  uint8_t  DatLoop2dVrefCoarse[128];  // Byte Offset: 0x1770 / CSR Address: 0x54bb8
                                      // Data Loopback bitmaps coarse starting value per Vref for specified DQ 
                                      // with DatLoop2dByte / DatLoop2dBit / DatLoop2dVrefIncr
                                      // Indexed by Vref stride index

  uint64_t DatLoop2dVrefBitmap[128];  // Byte Offset: 0x17f0 / CSR Address: 0x54bf8
                                      // Data Loopback bitmaps per Vref for specified DQ with 
                                      // DatLoop2dByte / DatLoop2dBit / DatLoop2dVrefIncr
                                      // Indexed by Vref stride index
   

} __attribute__ ((packed)) __attribute__ ((aligned(2))) pmu_smb_ddr_1d_t; // Structure size = 7144 bytes

#endif // _MNPMUSRAMMSGBLOCK_ATE_H
