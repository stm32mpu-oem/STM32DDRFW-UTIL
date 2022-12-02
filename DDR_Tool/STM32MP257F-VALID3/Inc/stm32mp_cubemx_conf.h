/**
  ******************************************************************************
  * @file    stm32mp_cubemx_conf.h
  * @author  MCD Application Team
  * @brief   Header file of STM32CubeMX board configuration for STM32MP2xx.
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
#ifndef __STM32MP2XX_CUBEMX_CONF_H
#define __STM32MP2XX_CUBEMX_CONF_H

#include "stm32mp2xx_hal.h"

#define MX_MODEL         "STM32MP2XX"

/* UART related configuration */
#define MX_UART_BAUDRATE        115200
#define MX_UART_WORDLENGTH      UART_WORDLENGTH_8B
#define MX_UART_STOPBITS        UART_STOPBITS_1
#define MX_UART_PARITY          UART_PARITY_NONE
#define MX_UART_HWFLOWCTL       UART_HWCONTROL_NONE

/* PMIC related configuration */
#define MX_USE_PMIC         0

#endif /* __STM32MP2XX_CUBEMX_CONF_H */
