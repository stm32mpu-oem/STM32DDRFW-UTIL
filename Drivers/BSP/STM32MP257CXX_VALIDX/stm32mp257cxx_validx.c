/**
  ******************************************************************************
  * @file    stm32mp257cxx_validx.c
  * @author  MCD Application Team
  * @brief   This file provides a set of firmware functions to manage
  *          LEDs
  *          push-buttons
  *          COM ports
  *          available on STM32MP257CXX-VALIDX board(MB170/4,5,6) from STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32mp257cxx_validx.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32MP257CXX_VALIDX
  * @{
  */

/** @defgroup STM32MP257CXX_VALIDX_LOW_LEVEL LOW LEVEL
  * @{
  */

/** @defgroup STM32MP257CXX_VALIDX_LOW_LEVEL_Private_TypesDefinitions  Private Types Definitions
  * @{
  */
typedef void (* BSP_EXTI_LineCallback) (void);
/**
  * @}
  */

/** @defgroup STM32MP257CXX_VALIDX_LOW_LEVEL_Private_FunctionPrototypes  Private Function Prototypes
  * @{
  */
#if ! defined (USE_STM32MP257CXX_UNIBOARD)
#if defined (CORE_CA35) || defined (CORE_CM33)
static void BUTTON_WAKEUP_EXTI_Callback(void);
#endif /* CORE_CA35 || CORE_CM33 */
#endif /* ! USE_STM32MP257CXX_UNIBOARD */
#if (USE_BSP_COM_FEATURE > 0)
static void USART_MspInit(UART_HandleTypeDef *huart);
static void USART_MspDeInit(UART_HandleTypeDef *huart);
#endif
/**
  * @}
  */

/** @defgroup STM32MP257CXX_VALIDX_LOW_LEVEL_Exported_Variables Exported Variables
  * @{
  */
EXTI_HandleTypeDef hpb_exti[BUTTONn];
#if (USE_BSP_COM_FEATURE > 0)
UART_HandleTypeDef hcom_uart[COMn];
USART_TypeDef* COM_USART[COMn] =
#if defined (USE_STM32MP257CXX_UNIBOARD)
                                 {COM_COMMON_UART, COM_COMMON_UART, COM_COMMON_UART};
#else /* USE_STM32MP257CXX_UNIBOARD */
#if defined (CORE_CA35) || defined (CORE_CM33)
                                 {COM_CA35_UART, COM_CM33_UART, COM_CM0PLUS_UART};
#elif defined (CORE_CM0PLUS) /* Core_M0Plus uses only COM_CM0PLUS */
                                 {0, 0, COM_CM0PLUS_UART};
#endif /* CORE_<...> */
#endif /* USE_STM32MP257CXX_UNIBOARD */

#endif
/**
  * @}
  */

/** @defgroup STM32MP257CXX_VALIDX_LOW_LEVEL_Private_Variables Private Variables
  * @{
  */
#if ! defined (USE_STM32MP257CXX_UNIBOARD)
#if defined (CORE_CA35) || defined (CORE_CM33)
static GPIO_TypeDef* LED_PORT[LEDn] = { LED1_GPIO_PORT,
                                        LED2_GPIO_PORT,
                                        LED3_GPIO_PORT,
                                        LED4_GPIO_PORT};

static const uint32_t LED_PIN[LEDn] = { LED1_PIN,
                                        LED2_PIN,
                                        LED3_PIN,
                                        LED4_PIN};

static const GPIO_PinState GPIO_LED_OFF[LEDn] = { GPIO_PIN_SET,
                                                  GPIO_PIN_RESET,
                                                  GPIO_PIN_RESET,
                                                  GPIO_PIN_RESET};

static const GPIO_PinState GPIO_LED_ON[LEDn] = { GPIO_PIN_RESET,
                                                 GPIO_PIN_SET,
                                                 GPIO_PIN_SET,
                                                 GPIO_PIN_SET};


static GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {BUTTON_WAKEUP_GPIO_PORT};
static const uint16_t BUTTON_PIN[BUTTONn] = {BUTTON_WAKEUP_PIN};
static const IRQn_Type BUTTON_IRQn[BUTTONn] = {BUTTON_WAKEUP_EXTI_IRQn};

#elif defined (CORE_CM0PLUS)
#warning "Core M0 can't manage LED in Validx Board"
#endif /* CORE_CA35 || CORE_CM33*/
#endif /* ! USE_STM32MP257CXX_UNIBOARD */

#if (USE_COM_LOG > 0)
/* define default active port to port dedicated to current Core
 * This is important for Validation applications which are not explicitly setting active log port */
static COM_TypeDef COM_ActiveLogPort = COM1;
#endif
#if (USE_BSP_COM_FEATURE > 0)
 #if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
  static uint32_t IsComMspCbValid[COMn] = {0};
 #endif
#endif

/**
  * @}
  */

/** @defgroup STM32MP257CXX_VALIDX_LOW_LEVEL_Exported_Functions Exported Functions
  * @{
  */

/**
  * @brief  This method returns the STM32MP257CXX VALIDX BSP Driver revision
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
int32_t BSP_GetVersion(void)
{
  return (int32_t)STM32MP257CXX_VALIDX_BSP_VERSION;
}

/**
  * @brief  This method returns the board name
  * @retval pointer to the board name string
  */
const uint8_t* BSP_GetBoardName(void)
{
  return (uint8_t*)STM32MP257CXX_VALIDX_BSP_BOARD_NAME;
}

/**
  * @brief  This method returns the board ID
  * @retval pointer to the board name string
  */
const uint8_t* BSP_GetBoardID(void)
{
  return (uint8_t*)STM32MP257CXX_VALIDX_BSP_BOARD_ID;
}

#if ! defined (USE_STM32MP257CXX_UNIBOARD)
#if defined (CORE_CA35) || defined (CORE_CM33)
/**
  * @brief  Configures LED on GPIO.
  * @param  Led LED to be configured.
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval BSP status
  */
int32_t BSP_LED_Init(Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;
  GPIO_InitTypeDef  GPIO_InitStruct;

  /* Enable the GPIO_LED clock */
  if (Led == LED1)
  {
    LED1_GPIO_CLK_ENABLE();
  }
  else if (Led == LED2)
  {
    LED2_GPIO_CLK_ENABLE();
  }
  else if (Led == LED3)
  {
    LED3_GPIO_CLK_ENABLE();
  }
  else if (Led == LED4)
  {
    LED4_GPIO_CLK_ENABLE();
  }

  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = LED_PIN[Led];
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

  HAL_GPIO_Init(LED_PORT[Led], &GPIO_InitStruct);

  /* By default, turn off LED */
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_LED_OFF[Led]);
 return ret;
}

/**
  * @brief  DeInit LEDs.
  * @param  Led LED to be configured.
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval BSP status
  */
int32_t  BSP_LED_DeInit(Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;
  GPIO_InitTypeDef  gpio_init_structure;

  /* DeInit the GPIO_LED pin */
  gpio_init_structure.Pin = LED_PIN [Led];
  /* Turn off LED */
  HAL_GPIO_WritePin (LED_PORT [Led], (uint16_t)LED_PIN[Led], GPIO_LED_OFF[Led]);
  HAL_GPIO_DeInit (LED_PORT [Led], gpio_init_structure.Pin);
  return ret;
}

/**
  * @brief  Turns selected LED On.
  * @param  Led LED to be set on
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval BSP status
  */
int32_t  BSP_LED_On(Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;

  HAL_GPIO_WritePin (LED_PORT [Led], (uint16_t)LED_PIN [Led], GPIO_LED_ON[Led]);
  return ret;
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led LED to be set off
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval BSP status
  */
int32_t  BSP_LED_Off(Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;
  HAL_GPIO_WritePin (LED_PORT [Led], (uint16_t)LED_PIN [Led], GPIO_LED_OFF[Led]);
  return ret;
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led LED to be toggled
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval BSP status
  */
int32_t  BSP_LED_Toggle(Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;
  HAL_GPIO_TogglePin(LED_PORT[Led], (uint16_t)LED_PIN[Led]);
  return ret;
}
/**
  * @brief  Get the selected LED state.
  * @param  Led LED to be get its state
  *          This parameter can be one of the following values:
  *            @arg  LED1
  *            @arg  LED2
  *            @arg  LED3
  *            @arg  LED4
  * @retval LED status
  */
int32_t BSP_LED_GetState (Led_TypeDef Led)
{
  int32_t ret = BSP_ERROR_NONE;
  ret = (int32_t)HAL_GPIO_ReadPin (LED_PORT [Led], (uint16_t)LED_PIN [Led]);
  return ret;
}

/**
  * @brief  Configures button GPIO and EXTI Line.
  * @param  Button Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button
  * @param  ButtonMode Button mode
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_MODE_GPIO: Button will be used as simple IO
  *            @arg  BUTTON_MODE_EXTI: Button will be connected to EXTI line
  *                                    with interrupt generation capability
  * @retval BSP status
  */
int32_t  BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  GPIO_InitTypeDef gpio_init_structure;
  static BSP_EXTI_LineCallback ButtonCallback[BUTTONn] ={BUTTON_WAKEUP_EXTI_Callback};
  static uint32_t  BSP_BUTTON_PRIO [BUTTONn] ={BSP_BUTTON_WAKEUP_IT_PRIORITY};
  static const uint32_t BUTTON_EXTI_LINE[BUTTONn] ={BUTTON_WAKEUP_EXTI_LINE};
  /* Enable the BUTTON clock*/
  BUTTON_WAKEUP_GPIO_CLK_ENABLE();
  gpio_init_structure.Pin = BUTTON_PIN [Button];
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;

  if(ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    gpio_init_structure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(BUTTON_PORT [Button], &gpio_init_structure);
  }
  else /* (ButtonMode == BUTTON_MODE_EXTI) */
  {
    /* Configure Button pin as input with External interrupt */
    gpio_init_structure.Mode = GPIO_MODE_IT_RISING;

    HAL_GPIO_Init(BUTTON_PORT[Button], &gpio_init_structure);

    (void)HAL_EXTI_GetHandle(&hpb_exti[Button], BUTTON_EXTI_LINE[Button]);
    (void)HAL_EXTI_RegisterCallback(&hpb_exti[Button],  HAL_EXTI_COMMON_CB_ID, ButtonCallback[Button]);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
#if defined(CORE_CA35)
    IRQ_SetPriority((BUTTON_IRQn[Button]), BSP_BUTTON_PRIO[Button]);
    IRQ_Enable((BUTTON_IRQn[Button]));
#else
    HAL_NVIC_SetPriority((BUTTON_IRQn[Button]), BSP_BUTTON_PRIO[Button], 0x00);
    HAL_NVIC_EnableIRQ((BUTTON_IRQn[Button]));
#endif
  }
  return BSP_ERROR_NONE;
}

/**
  * @brief  Push Button DeInit.
  * @param  Button Button to be configured
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button
  * @note PB DeInit does not disable the GPIO clock
  * @retval BSP status
  */
int32_t BSP_PB_DeInit(Button_TypeDef Button)
{
  GPIO_InitTypeDef gpio_init_structure;

  gpio_init_structure.Pin = BUTTON_PIN[Button];
#if defined(CORE_CA35)
  IRQ_Disable((IRQn_Type)(BUTTON_IRQn[Button]));
#else
  HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
#endif
  HAL_GPIO_DeInit(BUTTON_PORT[Button], gpio_init_structure.Pin);

  return BSP_ERROR_NONE;
}

/**
  * @brief  Returns the selected button state.
  * @param  Button Button to be checked
  *          This parameter can be one of the following values:
  *            @arg  BUTTON_WAKEUP: Wakeup Push Button
  * @retval The Button GPIO pin value
  */
int32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @brief  This function handles Push-Button interrupt requests.
  * @param  Button Specifies the pin connected EXTI line
  * @retval None
  */
void BSP_PB_IRQHandler(Button_TypeDef Button)
{
  HAL_EXTI_IRQHandler(&hpb_exti[Button]);
}

/**
  * @brief  KEY EXTI line detection callbacks.
  * @retval None
  */
static void BUTTON_WAKEUP_EXTI_Callback(void)
{
  BSP_PB_Callback(BUTTON_WAKEUP);
}
/**
  * @brief  BSP Push Button callback
  * @param  Button Specifies the pin connected EXTI line
  * @retval None.
  */
__weak void BSP_PB_Callback(Button_TypeDef Button)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Button);
  /* This function should be implemented by the user application.
  It is called into this driver when an event on Button is triggered. */
}
#endif /* defined (CORE_CA35) || defined (CORE_CM33) */
#endif /* ! USE_STM32MP257CXX_UNIBOARD */

#if (USE_BSP_COM_FEATURE > 0)
/**
  * @brief  Configures COM port.
  * @param  COM COM port to be configured.
  *          This parameter can be COM1, COM2, COM3
  * @param  COM_Init Pointer to a UART_HandleTypeDef structure that contains the
  *                configuration information for the specified USART peripheral.
  * @retval BSP status
  */
int32_t BSP_COM_Init(COM_TypeDef COM, COM_InitTypeDef *COM_Init)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM >= COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Set the COM Instance */
     hcom_uart[COM].Instance = COM_USART[COM];

    /* Init the UART Msp */
#if (USE_HAL_UART_REGISTER_CALLBACKS == 0)
    USART_MspInit(&hcom_uart[COM]);
#else
    if(IsComMspCbValid[COM] == 0U)
    {
      if(BSP_COM_RegisterDefaultMspCallbacks(COM) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif

    if(MX_USART_Init(&hcom_uart[COM], COM_Init) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  DeInit COM port.
  * @param  COM COM port to be configured.
  *          This parameter can be COM1, COM2, COM3
  * @retval BSP status
  */
int32_t BSP_COM_DeInit(COM_TypeDef COM)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM >= COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* USART configuration */
    hcom_uart[COM].Instance = COM_USART[COM];

#if (USE_HAL_UART_REGISTER_CALLBACKS == 0)
    USART_MspDeInit(&hcom_uart[COM]);
#endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 0) */

    if(HAL_UART_DeInit(&hcom_uart[COM]) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  Configures COM<n> port.
  * @param  huart USART handle
  * @param  COM_Init Pointer to a UART_HandleTypeDef structure that contains the
  *                  configuration information for the specified USART peripheral.
  * @retval HAL error code
  */
__weak HAL_StatusTypeDef MX_USART_Init(UART_HandleTypeDef *huart, MX_UART_InitTypeDef *COM_Init)
{
  HAL_StatusTypeDef ErrorCode;

  /* USART configuration */
  huart->Init.BaudRate     = (uint32_t)COM_Init->BaudRate;
#if defined(USE_STM32MP257CXX_UNIBOARD) && ! defined(COM_UNIBOARD_WITH_UART5_RX)
  /* DON'T use UART RX on UNIBOARD because this config is dedicated for Autoboard
   * and we try to keep as many IOs available as possible
   */
  huart->Init.Mode         = UART_MODE_TX;
#else /* USE_STM32MP257CXX_UNIBOARD */
  huart->Init.Mode         = UART_MODE_TX_RX;
#endif /* USE_STM32MP257CXX_UNIBOARD */
  huart->Init.Parity       = (uint32_t)COM_Init->Parity;
  huart->Init.WordLength   = (uint32_t)COM_Init->WordLength;
  huart->Init.StopBits     = (uint32_t)COM_Init->StopBits;
  huart->Init.HwFlowCtl    = (uint32_t)COM_Init->HwFlowCtl;
  huart->Init.OverSampling = UART_OVERSAMPLING_8;
#if !defined (CORE_CM0PLUS)
  ErrorCode = HAL_UART_Init(huart);
#else
  /* Initialize the number of data to process during RX/TX ISR execution */
  huart->NbTxDataToProcess = 1;
  huart->NbRxDataToProcess = 1;
  /* Initialize the UART State */
  huart->gState = HAL_UART_STATE_READY;
  huart->RxState = HAL_UART_STATE_READY;
  ErrorCode = HAL_OK;
#endif /* !defined (CORE_CM0PLUS) */
  return ErrorCode;
}

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
/**
  * @brief Register Default COM Msp Callbacks
  * @param  COM COM port to be configured.
  * @retval BSP status
  */
int32_t BSP_COM_RegisterDefaultMspCallbacks(COM_TypeDef COM)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM >= COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    __HAL_UART_RESET_HANDLE_STATE(&hcom_uart[COM]);

    /* Register default MspInit/MspDeInit Callback */
    if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPINIT_CB_ID, USART_MspInit) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPDEINIT_CB_ID, USART_MspDeInit) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsComMspCbValid[COM] = 1U;
    }
  }

  /* BSP status */
  return ret;
}

/**
  * @brief  Register COM<n> Msp Callback registering
  * @param  COM COM port to be configured.
  * @param  Callbacks     pointer to COM MspInit/MspDeInit callback functions
  * @retval BSP status
  */
int32_t BSP_COM_RegisterMspCallbacks(COM_TypeDef COM, BSP_COM_Cb_t *Callback)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM >= COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    __HAL_UART_RESET_HANDLE_STATE(&hcom_uart[COM]);

    /* Register MspInit/MspDeInit Callbacks */
    if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPINIT_CB_ID, Callback->pMspInitCb) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPDEINIT_CB_ID, Callback->pMspDeInitCb) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsComMspCbValid[COM] = 1U;
    }
  }

  /* BSP status */
  return ret;
}
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

#if (USE_COM_LOG > 0)
/**
  * @brief  Select the active COM port.
  * @param  COM COM port to be activated.
  *          This parameter can be COM1, COM2, COM3
  * @retval BSP status
  */
int32_t BSP_COM_SelectLogPort(COM_TypeDef COM)
{
  if(COM_ActiveLogPort != COM)
  {
    COM_ActiveLogPort = COM;
  }
  return BSP_ERROR_NONE;
}

#ifdef __GNUC__
int __io_putchar (int ch)
#else
int fputc (int ch, FILE *f)
#endif /* __GNUC__ */
{
  (void)HAL_UART_Transmit (&hcom_uart[COM_ActiveLogPort], (uint8_t *) &ch, 1, COM_POLL_TIMEOUT);
  return ch;
}

#ifdef __GNUC__
int __io_getchar(void)
{
  uint8_t ch = 0;
    HAL_UART_Receive(&hcom_uart[COM_ActiveLogPort], (uint8_t *)&ch, 1, COM1_RX_TIMEOUT);
    return ch;
}
#endif /* __GNUC__ */
#endif /* USE_COM_LOG */
#endif /* USE_BSP_COM_FEATURE */

/** @defgroup STM32MP257CXX_VALIDX_LOW_LEVEL_Private_Functions Private Functions
  * @{
  */

#if (USE_BSP_COM_FEATURE > 0)
/**
  * @brief  Initializes UART MSP.
  * @param  huart UART handle
  * @retval None
  */
static void USART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef gpio_init_structure;

  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;
  gpio_init_structure.Pull = GPIO_PULLUP;

#if defined (CORE_CA35) || defined (CORE_CM33)
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

#if defined(USE_STM32MP257CXX_UNIBOARD)
  if (huart->Instance == COM_COMMON_UART)
  {
  /* USART5 clock config */
    PeriphClkInit.XBAR_Channel = RCC_PERIPHCLK_UART3_5;

    /* Enable USART and GPIOs clocks */
    COM_COMMON_CLK_ENABLE();
    COM_COMMON_TX_GPIO_CLK_ENABLE();

    /* Configure USART Tx as alternate function */
    gpio_init_structure.Pin = COM_COMMON_TX_PIN;
    gpio_init_structure.Alternate = COM_COMMON_TX_AF;
    HAL_GPIO_Init(COM_COMMON_TX_GPIO_PORT, &gpio_init_structure);

#if defined(COM_UNIBOARD_WITH_UART5_RX)
    /* Use UART RX on UNIBOARD only if explicitly enabled
     * because this config is dedicated for Autoboard
     * and we try to keep as many IOs available as possible
     */
     COM_COMMON_RX_GPIO_CLK_ENABLE();
    /* Configure USART Rx as alternate function */
    gpio_init_structure.Pin = COM_COMMON_RX_PIN;
    gpio_init_structure.Alternate = COM_COMMON_RX_AF;
    HAL_GPIO_Init(COM_COMMON_RX_GPIO_PORT, &gpio_init_structure);
#endif /* COM_UNIBOARD_WITH_UART5_RX */
  }
#else /* USE_STM32MP257CXX_UNIBOARD */
  if (huart->Instance == COM_CA35_UART)
  {
    /* USART2 clock config */
    PeriphClkInit.XBAR_Channel = RCC_PERIPHCLK_UART2_4;

    /* Enable USART clock */
    COM_CA35_TX_GPIO_CLK_ENABLE();
    COM_CA35_RX_GPIO_CLK_ENABLE();
    COM_CA35_CLK_ENABLE();
    /* Configure USART Tx as alternate function */
    gpio_init_structure.Pin = COM_CA35_TX_PIN;
    gpio_init_structure.Alternate = COM_CA35_TX_AF;
    HAL_GPIO_Init(COM_CA35_TX_GPIO_PORT, &gpio_init_structure);

    /* Configure USART Rx as alternate function */
    gpio_init_structure.Pin = COM_CA35_RX_PIN;
    gpio_init_structure.Alternate = COM_CA35_RX_AF;
    HAL_GPIO_Init(COM_CA35_RX_GPIO_PORT, &gpio_init_structure);
  }
  else if (huart->Instance == COM_CM33_UART)
  {
  /* USART5 or UART8 clock config */
#if defined(USE_STM32MP257CXX_VALID1) || defined(USE_STM32MP257CXX_VALID3)
    PeriphClkInit.XBAR_Channel = RCC_PERIPHCLK_UART3_5;
#else
    PeriphClkInit.XBAR_Channel = RCC_PERIPHCLK_UART7_8;
#endif /* USE_STM32MP257CXX_VALID1 & 3*/

    /* Enable USART clock */
    COM_CM33_TX_GPIO_CLK_ENABLE();
    COM_CM33_RX_GPIO_CLK_ENABLE();
    COM_CM33_CLK_ENABLE();

    /* Configure USART Tx as alternate function */
    gpio_init_structure.Pin = COM_CM33_TX_PIN;
    gpio_init_structure.Alternate = COM_CM33_TX_AF;
    HAL_GPIO_Init(COM_CM33_TX_GPIO_PORT, &gpio_init_structure);

    /* Configure USART Rx as alternate function */
    gpio_init_structure.Pin = COM_CM33_RX_PIN;
    gpio_init_structure.Alternate = COM_CM33_RX_AF;
    HAL_GPIO_Init(COM_CM33_RX_GPIO_PORT, &gpio_init_structure);
  }
  else if (huart->Instance == COM_CM0PLUS_UART)
  {
    /* LPUART clock config */
    PeriphClkInit.XBAR_Channel = RCC_PERIPHCLK_LPUART1;

    /* Enable Backup domain access */
    HAL_PWR_EnableBkUpD3Access();

    /* Enable USART clock */
    COM_CM0PLUS_TX_GPIO_CLK_ENABLE();
    COM_CM0PLUS_RX_GPIO_CLK_ENABLE();
    COM_CM0PLUS_CLK_ENABLE();

    /* Configure USART Tx as alternate function */
    gpio_init_structure.Pin = COM_CM0PLUS_TX_PIN;
    gpio_init_structure.Alternate = COM_CM0PLUS_TX_AF;
    HAL_GPIO_Init(COM_CM0PLUS_TX_GPIO_PORT, &gpio_init_structure);

    /* Configure USART Rx as alternate function */
    gpio_init_structure.Pin = COM_CM0PLUS_RX_PIN;
    gpio_init_structure.Alternate = COM_CM0PLUS_RX_AF;
    HAL_GPIO_Init(COM_CM0PLUS_RX_GPIO_PORT, &gpio_init_structure);
  }
#endif /* USE_STM32MP257CXX_UNIBOARD */

  /* Start HSE Oscillator to use it for UART source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while (1);
  }

  /* Set HSE as source clock for UART COM */
  PeriphClkInit.XBAR_ClkSrc = RCC_XBAR_CLKSRC_HSE;
  PeriphClkInit.Div = 1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    while (1);
  }

#elif defined(CORE_CM0PLUS)
  HAL_PWR_EnableBkUpAccess();
  /* Configure USART Tx as alternate function */
  gpio_init_structure.Pin = COM_CM0PLUS_TX_PIN;
  gpio_init_structure.Alternate = COM_CM0PLUS_TX_AF;
  HAL_GPIO_Init(COM_CM0PLUS_TX_GPIO_PORT, &gpio_init_structure);

  /* Configure USART Rx as alternate function */
  gpio_init_structure.Pin = COM_CM0PLUS_RX_PIN;
  gpio_init_structure.Alternate = COM_CM0PLUS_RX_AF;
  HAL_GPIO_Init(COM_CM0PLUS_RX_GPIO_PORT, &gpio_init_structure);
#warning "Core M0 can't manage RCC clock config"
#endif /* CORE_CA35 || CORE_CM33 */
}

/**
  * @brief  Initialize USART6 Msp part
  * @param  huart UART handle
  * @retval None
  */
static void USART_MspDeInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef          gpio_init_structure;

#if defined (CORE_CA35) || defined (CORE_CM33)
#if defined(USE_STM32MP257CXX_UNIBOARD)
  if (huart->Instance == COM_COMMON_UART)
  {
    /* COM GPIO pin configuration */
    gpio_init_structure.Pin  = COM_COMMON_TX_PIN;
    HAL_GPIO_DeInit(COM_COMMON_TX_GPIO_PORT, gpio_init_structure.Pin);

#if defined(COM_UNIBOARD_WITH_UART5_RX)
    /* Use UART RX on UNIBOARD only if explicitly enabled
     * because this config is dedicated for Autoboard
     * and we try to keep as many IOs available as possible
     */
    gpio_init_structure.Pin  = COM_COMMON_RX_PIN;
    HAL_GPIO_DeInit(COM_COMMON_RX_GPIO_PORT, gpio_init_structure.Pin);
#endif /* COM_UNIBOARD_WITH_UART5_RX */
    /* Disable USART clock */
    COM_COMMON_CLK_DISABLE();
  }
#else /* USE_STM32MP257CXX_UNIBOARD */
  if (huart->Instance == COM_CA35_UART)
  {
    /* COM GPIO pin configuration */
    gpio_init_structure.Pin  = COM_CA35_TX_PIN;
    HAL_GPIO_DeInit(COM_CA35_TX_GPIO_PORT, gpio_init_structure.Pin);

    gpio_init_structure.Pin  = COM_CA35_RX_PIN;
    HAL_GPIO_DeInit(COM_CA35_RX_GPIO_PORT, gpio_init_structure.Pin);

    /* Disable USART clock */
    COM_CA35_CLK_DISABLE();
  }
  else if (huart->Instance == COM_CM33_UART)
  {
    /* COM GPIO pin configuration */
    gpio_init_structure.Pin  = COM_CM33_TX_PIN;
    HAL_GPIO_DeInit(COM_CM33_TX_GPIO_PORT, gpio_init_structure.Pin);

    gpio_init_structure.Pin  = COM_CM33_RX_PIN;
    HAL_GPIO_DeInit(COM_CM33_RX_GPIO_PORT, gpio_init_structure.Pin);

    /* Disable USART clock */
    COM_CM33_CLK_DISABLE();
  }
  else if (huart->Instance == COM_CM0PLUS_UART)
  {
    /* COM GPIO pin configuration */
    gpio_init_structure.Pin  = COM_CM0PLUS_TX_PIN;
    HAL_GPIO_DeInit(COM_CM0PLUS_TX_GPIO_PORT, gpio_init_structure.Pin);

    gpio_init_structure.Pin  = COM_CM0PLUS_RX_PIN;
    HAL_GPIO_DeInit(COM_CM0PLUS_RX_GPIO_PORT, gpio_init_structure.Pin);

    /* Disable USART clock */
    COM_CM0PLUS_CLK_DISABLE();
  }
#endif /* USE_STM32MP257CXX_UNIBOARD */

#elif defined(CORE_CM0PLUS)
  /* COM GPIO pin configuration */
  gpio_init_structure.Pin  = COM_CM0PLUS_TX_PIN;
  HAL_GPIO_DeInit(COM_CM0PLUS_TX_GPIO_PORT, gpio_init_structure.Pin);

  gpio_init_structure.Pin  = COM_CM0PLUS_RX_PIN;
  HAL_GPIO_DeInit(COM_CM0PLUS_RX_GPIO_PORT, gpio_init_structure.Pin);
#warning "Core M0 can't manage RCC clock config"
#endif /* CORE_CA35 || CORE_CM33 */
}
#endif /* USE_BSP_COM_FEATURE */

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