/**
  ******************************************************************************
  * @file    stm32mp257f_eval.h
  * @author  MCD Application Team
  * @brief   This file contains definitions for STM32MP257CXX_EVAL:
  *          LEDs
  *          push-buttons
  *          COM ports
  *          hardware resources.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP257F_EVAL
#define STM32MP257F_EVAL

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp257f_eval_conf.h"
#include "stm32mp257f_eval_errno.h"
#include "stm32mp_util_conf.h"

#if (USE_BSP_COM_FEATURE > 0)
  #if (USE_COM_LOG > 0)
    #ifndef __GNUC__
      #include "stdio.h"
    #endif
  #endif
#endif

#if !defined (USE_BSP)
  #define USE_BSP
#endif

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32MP257F_EVAL
  * @{
  */

/** @addtogroup STM32MP257F_EVAL_LOW_LEVEL
  * @{
  */

/** @defgroup STM32MP257F_EVAL_LOW_LEVEL_Exported_Types Exported Types
  * @{
  */
typedef enum
{
  LED1 = 0U,
  LED_RED = LED1,
  LED2 = 1U,
  LED_GREEN = LED2,
  LED3 = 2U,
  LED_ORANGE = LED3,
  LED4 = 3U,
  LED_BLUE = LED4,
  LEDn
} Led_TypeDef;

typedef enum
{
  BUTTON_WAKEUP = 0U,
  BUTTON_USER1,
  BUTTON_USER2,
  BUTTON_TAMPER,
  BUTTONn
} Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0U,
  BUTTON_MODE_EXTI = 1U
} ButtonMode_TypeDef;

#if (USE_BSP_COM_FEATURE > 0)
typedef enum
{
  /* Define COM_VCP_CA35, COM_VCP_CM33, COM_CM0PLUS to match COM_USART[] table in stm32mp257f_eval.c
   * These values are to be used in examples
   */
  COM_VCP_CA35 = 0U,
  COM_VCP_CM33 = 1U,
  COM_CM0PLUS = 2U,
  /* Define COM1, COM2, COM3 aliases
   * These values are to be used in Validation applications
   * They allow to use same COM<n> whatever the used core
   * and avoid ifdefs in validation code
   */
#if defined(CORE_CA35)
  COM1 = COM_VCP_CA35,
  COM2 = COM_VCP_CM33,
  COM3 = COM_CM0PLUS,
#elif defined(CORE_CM33)
  COM1 = COM_VCP_CM33,
  COM2 = COM_VCP_CA35,
  COM3 = COM_CM0PLUS,
#elif defined(CORE_CM0PLUS)
  COM1 = COM_CM0PLUS,
  COM2 = COM_VCP_CA35,
  COM3 = COM_CM0PLUS,
#endif /* CORE_<...> */
  COMn
} COM_TypeDef;

typedef enum
{
  COM_STOPBITS_1     =   UART_STOPBITS_1,
  COM_STOPBITS_2     =   UART_STOPBITS_2,
} COM_StopBitsTypeDef;

typedef enum
{
  COM_PARITY_NONE     =  UART_PARITY_NONE,
  COM_PARITY_EVEN     =  UART_PARITY_EVEN,
  COM_PARITY_ODD      =  UART_PARITY_ODD,
}COM_ParityTypeDef;

typedef enum
{
  COM_HWCONTROL_NONE    =  UART_HWCONTROL_NONE,
  COM_HWCONTROL_RTS     =  UART_HWCONTROL_RTS,
  COM_HWCONTROL_CTS     =  UART_HWCONTROL_CTS,
  COM_HWCONTROL_RTS_CTS =  UART_HWCONTROL_RTS_CTS,
} COM_HwFlowCtlTypeDef;

typedef enum
{
  COM_WORDLENGTH_7B = UART_WORDLENGTH_7B,
  COM_WORDLENGTH_8B = UART_WORDLENGTH_8B,
  COM_WORDLENGTH_9B = UART_WORDLENGTH_9B,
} COM_WordLengthTypeDef;

typedef struct
{
  uint32_t              BaudRate;
  COM_WordLengthTypeDef WordLength;
  COM_StopBitsTypeDef   StopBits;
  COM_ParityTypeDef     Parity;
  COM_HwFlowCtlTypeDef  HwFlowCtl;
} COM_InitTypeDef;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
typedef struct
{
  void (* pMspInitCb)(UART_HandleTypeDef *);
  void (* pMspDeInitCb)(UART_HandleTypeDef *);
} BSP_COM_Cb_t;
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
#endif /* USE_BSP_COM_FEATURE */

/**
  * @}
  */

/** @defgroup STM32MP257F_EVAL_LOW_LEVEL_Exported_Constants Exported Constants
  * @{
  */
/**
  * @brief  Define for STM32MP257F EVAL board
  */
#if !defined (USE_STM32MP257F_EV1)
#define USE_STM32MP257F_EV1
#endif
/**
  * @brief STM32MP257F EVAL BSP Driver version number VX.Y.Z
  */
#define STM32MP257F_EV1_BSP_VERSION_MAIN   (0x00) /*!< [31:24] main version */
#define STM32MP257F_EV1_BSP_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define STM32MP257F_EV1_BSP_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define STM32MP257F_EV1_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define STM32MP257F_EV1_BSP_VERSION        ((STM32MP257F_EV1_BSP_VERSION_MAIN << 24)\
                                                |(STM32MP257F_EV1_BSP_VERSION_SUB1 << 16)\
                                                |(STM32MP257F_EV1_BSP_VERSION_SUB2 << 8 )\
                                                |(STM32MP257F_EV1_BSP_VERSION_RC))
#define STM32MP257F_EV1_BSP_BOARD_NAME  "STM32MP257F-EV1";
#define STM32MP257F_EV1_BSP_BOARD_ID    "MB1936-A01";

/** @defgroup STM32MP257F_EVAL_LOW_LEVEL_LED EVAL LOW LEVEL LED
  * @{
  */
#if defined (CORE_CA35) || defined (CORE_CM33)
#define LED1_GPIO_PORT                   GPIOH
#define LED1_PIN                         GPIO_PIN_4
#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOH_CLK_ENABLE()
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOH_CLK_DISABLE()

#if defined (USE_STM32MP257F_EV1)
#define LED2_GPIO_PORT                   GPIOD
#define LED2_PIN                         GPIO_PIN_8
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOD_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOD_CLK_DISABLE()

#define LED3_GPIO_PORT                   GPIOJ
#define LED3_PIN                         GPIO_PIN_6
#define LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOJ_CLK_ENABLE()
#define LED3_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOJ_CLK_DISABLE()

#define LED4_GPIO_PORT                   GPIOJ
#define LED4_PIN                         GPIO_PIN_7
#define LED4_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOJ_CLK_ENABLE()
#define LED4_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOJ_CLK_DISABLE()

#else
#error "Please define target board"
#endif /* USE_STM32MP257F_EV1 */
#elif defined (CORE_CM0PLUS)

/* Core M0 can't manage LED in EVX Board */
#endif /* CORE_CA35 || CORE_CM33 */
/**
  * @}
  */

/** @defgroup STM32MP257F_EVAL_LOW_LEVEL_BUTTON LOW LEVEL BUTTON
  * @{
  */
/* Button state */
#define BUTTON_RELEASED                    0U
#define BUTTON_PRESSED                     1U
/**
  * @brief Wakeup push-button
  */
#if defined (CORE_CA35) || defined (CORE_CM33)
#define BUTTON_WAKEUP_PIN                   GPIO_PIN_6
#define BUTTON_WAKEUP_GPIO_PORT             GPIOI
#define BUTTON_WAKEUP_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOI_CLK_ENABLE()
#define BUTTON_WAKEUP_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOI_CLK_DISABLE()
#define BUTTON_WAKEUP_EXTI_IRQn             EXTI2_2_IRQn
#define BUTTON_WAKEUP_EXTI_LINE             EXTI2_LINE_2
#endif
/**
  * @brief USER1 push-button
  */
#if defined (CORE_CA35) || defined (CORE_CM33)
#define BUTTON_USER1_PIN                   GPIO_PIN_2
#define BUTTON_USER1_GPIO_PORT             GPIOD
#define BUTTON_USER1_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()
#define BUTTON_USER1_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOD_CLK_DISABLE()
#define BUTTON_USER1_EXTI_IRQn             EXTI2_2_IRQn
#define BUTTON_USER1_EXTI_LINE             EXTI2_LINE_2
#endif
/**
  * @brief USER2 push-button
  */
#if defined (CORE_CA35) || defined (CORE_CM33)
#define BUTTON_USER2_PIN                   GPIO_PIN_8
#define BUTTON_USER2_GPIO_PORT             GPIOG
#define BUTTON_USER2_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOG_CLK_ENABLE()
#define BUTTON_USER2_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOG_CLK_DISABLE()
#define BUTTON_USER2_EXTI_IRQn             EXTI2_2_IRQn
#define BUTTON_USER2_EXTI_LINE             EXTI2_LINE_2
#endif
/**
  * @brief TAMPER push-button
  */
#if defined (CORE_CA35) || defined (CORE_CM33)
#define BUTTON_TAMPER_PIN                   GPIO_PIN_8
#define BUTTON_TAMPER_GPIO_PORT             GPIOI
#define BUTTON_TAMPER_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOI_CLK_ENABLE()
#define BUTTON_TAMPER_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOI_CLK_DISABLE()
#define BUTTON_TAMPER_EXTI_IRQn             EXTI2_2_IRQn
#define BUTTON_TAMPER_EXTI_LINE             EXTI2_LINE_2
#endif
/**
  * @}
  */

/** @defgroup STM32MP257F_EVAL_LOW_LEVEL_COM LOW LEVEL COM
  * @{
  */
#if (USE_BSP_COM_FEATURE > 0)
/**
  * @brief Definition for COM port1, connected to USART2
  */
#if defined (CORE_CA35) || defined (CORE_CM33)

/*********************** COM_CA35 ******************************/
#if (UTIL_UART_INSTANCE == UTIL_USART1)
  #define COM_CA35_UART                       USART1
  #define COM_CA35_CLK_ENABLE()             __HAL_RCC_USART1_CLK_ENABLE()
  #define COM_CA35_CLK_DISABLE()            __HAL_RCC_USART1_CLK_DISABLE()
#elif (UTIL_UART_INSTANCE == UTIL_USART2)
  #define COM_CA35_UART                       USART2
  #define COM_CA35_CLK_ENABLE()             __HAL_RCC_USART2_CLK_ENABLE()
  #define COM_CA35_CLK_DISABLE()            __HAL_RCC_USART2_CLK_DISABLE()
#elif (UTIL_UART_INSTANCE == UTIL_USART3)
  #define COM_CA35_UART                       USART3
  #define COM_CA35_CLK_ENABLE()             __HAL_RCC_USART3_CLK_ENABLE()
  #define COM_CA35_CLK_DISABLE()            __HAL_RCC_USART3_CLK_DISABLE()
#elif (UTIL_UART_INSTANCE == UTIL_UART4)
  #define COM_CA35_UART                       UART4
  #define COM_CA35_CLK_ENABLE()             __HAL_RCC_UART4_CLK_ENABLE()
  #define COM_CA35_CLK_DISABLE()            __HAL_RCC_UART4_CLK_DISABLE()
#elif (UTIL_UART_INSTANCE == UTIL_UART5)
  #define COM_CA35_UART                       UART5
  #define COM_CA35_CLK_ENABLE()             __HAL_RCC_UART5_CLK_ENABLE()
  #define COM_CA35_CLK_DISABLE()            __HAL_RCC_UART5_CLK_DISABLE()
#elif (UTIL_UART_INSTANCE == UTIL_USART6)
  #define COM_CA35_UART                       USART6
  #define COM_CA35_CLK_ENABLE()             __HAL_RCC_USART6_CLK_ENABLE()
  #define COM_CA35_CLK_DISABLE()            __HAL_RCC_USART6_CLK_DISABLE()
#elif (UTIL_UART_INSTANCE == UTIL_UART7)
  #define COM_CA35_UART                       UART7
  #define COM_CA35_CLK_ENABLE()             __HAL_RCC_UART7_CLK_ENABLE()
  #define COM_CA35_CLK_DISABLE()            __HAL_RCC_UART7_CLK_DISABLE()
#elif (UTIL_UART_INSTANCE == UTIL_UART8)
  #define COM_CA35_UART                       UART8
  #define COM_CA35_CLK_ENABLE()             __HAL_RCC_UART8_CLK_ENABLE()
  #define COM_CA35_CLK_DISABLE()            __HAL_RCC_UART8_CLK_DISABLE()
#elif (UTIL_UART_INSTANCE == UTIL_UART9)
  #define COM_CA35_UART                       UART9
  #define COM_CA35_CLK_ENABLE()             __HAL_RCC_UART9_CLK_ENABLE()
  #define COM_CA35_CLK_DISABLE()            __HAL_RCC_UART9_CLK_DISABLE()
#elif (UTIL_UART_INSTANCE == UTIL_LPUART1)
  #define COM_CA35_UART                       LPUART1
  #define COM_CA35_CLK_ENABLE()             __HAL_RCC_LPUART1_CLK_ENABLE()
  #define COM_CA35_CLK_DISABLE()            __HAL_RCC_LPUART1_CLK_DISABLE()
#else
  #error "unknown UTIL_UART_INSTANCE definition."
#endif

#define COM_CA35_TX_PIN                     UTIL_UART_TX_PIN

#if (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOA)
  #define COM_CA35_TX_GPIO_PORT             GPIOA
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOB)
  #define COM_CA35_TX_GPIO_PORT             GPIOB
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOC)
  #define COM_CA35_TX_GPIO_PORT             GPIOC
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOC_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOD)
  #define COM_CA35_TX_GPIO_PORT             GPIOD
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOD_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOE)
  #define COM_CA35_TX_GPIO_PORT             GPIOE
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOE_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOE_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOF)
  #define COM_CA35_TX_GPIO_PORT             GPIOF
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOF_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOF_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOG)
  #define COM_CA35_TX_GPIO_PORT             GPIOG
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOG_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOG_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOH)
  #define COM_CA35_TX_GPIO_PORT             GPIOH
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOH_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOH_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOI)
  #define COM_CA35_TX_GPIO_PORT             GPIOI
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOI_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOI_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOJ)
  #define COM_CA35_TX_GPIO_PORT             GPIOJ
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOJ_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOJ_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOK)
  #define COM_CA35_TX_GPIO_PORT             GPIOK
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOK_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOK_CLK_DISABLE()
#elif (UTIL_UART_TX_GPIO_PORT == UTIL_GPIOZ)
  #define COM_CA35_TX_GPIO_PORT             GPIOZ
  #define COM_CA35_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOZ_CLK_ENABLE()
  #define COM_CA35_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOZ_CLK_DISABLE()
#else
  #error "unknown UTIL_UART_TX_GPIO_PORT definition."
#endif

#define COM_CA35_TX_AF                      UTIL_UART_TX_AF

#define COM_CA35_RX_PIN                     UTIL_UART_RX_PIN

#if (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOA)
  #define COM_CA35_RX_GPIO_PORT             GPIOA
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOB)
  #define COM_CA35_RX_GPIO_PORT             GPIOB
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOC)
  #define COM_CA35_RX_GPIO_PORT             GPIOC
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOC_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOD)
  #define COM_CA35_RX_GPIO_PORT             GPIOD
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOD_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOE)
  #define COM_CA35_RX_GPIO_PORT             GPIOE
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOE_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOE_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOF)
  #define COM_CA35_RX_GPIO_PORT             GPIOF
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOF_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOF_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOG)
  #define COM_CA35_RX_GPIO_PORT             GPIOG
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOG_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOG_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOH)
  #define COM_CA35_RX_GPIO_PORT             GPIOH
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOH_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOH_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOI)
  #define COM_CA35_RX_GPIO_PORT             GPIOI
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOI_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOI_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOJ)
  #define COM_CA35_RX_GPIO_PORT             GPIOJ
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOJ_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOJ_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOK)
  #define COM_CA35_RX_GPIO_PORT             GPIOK
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOK_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOK_CLK_DISABLE()
#elif (UTIL_UART_RX_GPIO_PORT == UTIL_GPIOZ)
  #define COM_CA35_RX_GPIO_PORT             GPIOZ
  #define COM_CA35_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOZ_CLK_ENABLE()
  #define COM_CA35_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOZ_CLK_DISABLE()
#else
  #error "unknown UTIL_UART_RX_GPIO_PORT definition."
#endif

#define COM_CA35_RX_AF                      UTIL_UART_RX_AF

/*********************** COM_CM33 ******************************/
#define COM_CM33_UART                       UART5 // VALID1/3
#define COM_CM33_CLK_ENABLE()               __HAL_RCC_UART5_CLK_ENABLE()
#define COM_CM33_CLK_DISABLE()              __HAL_RCC_UART5_CLK_DISABLE()

#define COM_CM33_TX_PIN                     GPIO_PIN_9
#define COM_CM33_TX_GPIO_PORT               GPIOG
#define COM_CM33_TX_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOG_CLK_ENABLE()
#define COM_CM33_TX_GPIO_CLK_DISABLE()      __HAL_RCC_GPIOG_CLK_DISABLE()
#define COM_CM33_TX_AF                      GPIO_AF5_UART5

#define COM_CM33_RX_PIN                     GPIO_PIN_10
#define COM_CM33_RX_GPIO_PORT               GPIOG
#define COM_CM33_RX_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOG_CLK_ENABLE()
#define COM_CM33_RX_GPIO_CLK_DISABLE()      __HAL_RCC_GPIOG_CLK_DISABLE()
#define COM_CM33_RX_AF                      GPIO_AF5_UART5

#endif /* CORE_CA35 || CORE_CM33 */

/*********************** COM_CM0PLUS ******************************/
#define COM_CM0PLUS_UART                    LPUART1
#define COM_CM0PLUS_CLK_ENABLE()            __HAL_RCC_LPUART1_CLK_ENABLE()
#define COM_CM0PLUS_CLK_DISABLE()           __HAL_RCC_LPUART1_CLK_DISABLE()

#define COM_CM0PLUS_TX_PIN                  GPIO_PIN_7
#define COM_CM0PLUS_TX_GPIO_PORT            GPIOZ
#define COM_CM0PLUS_TX_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOZ_CLK_ENABLE()
#define COM_CM0PLUS_TX_GPIO_CLK_DISABLE()   __HAL_RCC_GPIOZ_CLK_DISABLE()
#define COM_CM0PLUS_TX_AF                   GPIO_AF6_LPUART1

#define COM_CM0PLUS_RX_PIN                  GPIO_PIN_8
#define COM_CM0PLUS_RX_GPIO_PORT            GPIOZ
#define COM_CM0PLUS_RX_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOZ_CLK_ENABLE()
#define COM_CM0PLUS_RX_GPIO_CLK_DISABLE()   __HAL_RCC_GPIOZ_CLK_DISABLE()
#define COM_CM0PLUS_RX_AF                   GPIO_AF6_LPUART1

#define COM_POLL_TIMEOUT              1000
#define COM1_RX_TIMEOUT               HAL_MAX_DELAY
#define MX_UART_InitTypeDef COM_InitTypeDef
#endif
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup STM32MP257F_EVAL_LOW_LEVEL_Exported_Variables
  * @{
  */
extern EXTI_HandleTypeDef hpb_exti[];
#if (USE_BSP_COM_FEATURE > 0)
extern UART_HandleTypeDef hcom_uart[];
extern USART_TypeDef* COM_USART[];
#endif

/**
  * @}
  */

/** @addtogroup STM32MP257F_EVAL_LOW_LEVEL_Exported_Functions
  * @{
  */
int32_t BSP_GetVersion(void);
const uint8_t* BSP_GetBoardName(void);
const uint8_t* BSP_GetBoardID(void);

int32_t BSP_LED_Init(Led_TypeDef Led);
int32_t BSP_LED_DeInit(Led_TypeDef Led);
int32_t BSP_LED_On(Led_TypeDef Led);
int32_t BSP_LED_Off(Led_TypeDef Led);
int32_t BSP_LED_Toggle(Led_TypeDef Led);
int32_t BSP_LED_GetState (Led_TypeDef Led);
int32_t BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
int32_t BSP_PB_DeInit(Button_TypeDef Button);
int32_t BSP_PB_GetState(Button_TypeDef Button);
void    BSP_PB_Callback(Button_TypeDef Button);
#if (USE_BSP_COM_FEATURE > 0)
int32_t  BSP_COM_Init(COM_TypeDef COM, COM_InitTypeDef *COM_Init);
int32_t  BSP_COM_DeInit(COM_TypeDef COM);
#if (USE_COM_LOG > 0)
int32_t  BSP_COM_SelectLogPort (COM_TypeDef COM);
#endif

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
int32_t BSP_COM_RegisterDefaultMspCallbacks(COM_TypeDef COM);
int32_t BSP_COM_RegisterMspCallbacks(COM_TypeDef COM, BSP_COM_Cb_t *Callback);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
HAL_StatusTypeDef MX_USART_Init(UART_HandleTypeDef *huart, MX_UART_InitTypeDef *COM_Init);
#endif /* USE_BSP_COM_FEATURE */

void BSP_PB_IRQHandler(Button_TypeDef Button);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32257CXX_EVX */
