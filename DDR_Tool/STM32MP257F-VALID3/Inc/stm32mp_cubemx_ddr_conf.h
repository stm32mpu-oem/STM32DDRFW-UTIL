/**
  ******************************************************************************
  * @file    stm32mp_cubemx_conf.h
  * @author  MCD Application Team
  * @brief   Header file of STM32CubeMX DDR configuration for STM32MP2xx.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP_CUBEMX_DDR_CONF_H
#define __STM32MP_CUBEMX_DDR_CONF_H

#if (STM32MP_DDR4_TYPE && (DDR_SIZE_Gb == 16))
  #include "stm32mp2xx-ddr4-2x8Gbits-2x16bits-template.h"
#elif (STM32MP_DDR3_TYPE && (DDR_SIZE_Gb == 8))
  #include "stm32mp2xx-ddr3-2x4Gbits-2x16bits-template.h"
#elif (STM32MP_LPDDR4_TYPE && (DDR_SIZE_Gb == 16))
  #include "stm32mp2xx-lpddr4-1x16Gbits-1x32bits-template.h"
#else
  #error "no DDR settings defined."
#endif

#endif /* __STM32MP_CUBEMX_DDR_CONF_H */
