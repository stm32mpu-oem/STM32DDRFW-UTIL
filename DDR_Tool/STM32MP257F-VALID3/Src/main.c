/**
  ******************************************************************************
  * @file    Templates/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body
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
#include "main.h"
#include "stm32mp_cubemx_conf.h"

/** @addtogroup STM32MP2xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* This project  as template implementation that User may integrate
     in his application, to enhance the performance in case of use of AXI interface
     with several masters. */

  /* STM32MP1xx HAL library initialization:
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  DDR_InitTypeDef iddr;

  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /*  Configure USART for logging messages  */
  UART_Config();

  /*****************************/
  /* Test environment settings */
  /*****************************/

  /* Configure the system power */
  SystemPower_Config();

  /* Init LED3 */
  BSP_LED_Init(LED_GREEN);

  /* Insert 1 second delay */
  HAL_Delay(1000);

  iddr.wakeup_from_standby = false;
  iddr.self_refresh = false;
  iddr.zdata = 0;
  iddr.clear_bkp = false;

  if (HAL_DDR_Init(&iddr) != HAL_OK)
  {
    printf("DDR Initialization KO\n\r");
    return 1;
  }

  /* Infinite loop */
  while (1)
  {
  /* Toggle LED3 ON */
  BSP_LED_Toggle(LED_GREEN);

  /* Insert 1 second delay */
  HAL_Delay(1000);

  /* Toggle LED3 OFF */
  BSP_LED_Toggle(LED_GREEN);
  }
}


/*
Component              | Parent  |   Frequency     | Status | Comment                           |
                       |         |                 | Note: the status is given before EN gate   |
-----------------------|---------|-----------------|--------|-----------------------------------|
LSI                    |N.A.     |    0.032000 MHz |   ON   | Mandatory for IWDG, DAC
  DAC                  |LSI      |    0.032000 MHz |   ON   |
LSE                    |N.A.     |    0.032768 MHz |   ON   | Mandatory for TEMP
  CEC                  |LSE      |    0.032768 MHz |   ON   |
HSI                    |N.A.     |   64.000000 MHz |   ON   |
  MCO1                 |HSI      |   64.000000 MHz |   OFF  |
HSE                    |N.A.     |   24.000000 MHz |   ON   |
  DSIPLL               |HSE      |  125.000000 MHz |   OFF  | DSI DPHY PLL max frequency
    BLCLK              |DSIPLL   |  125.000000 MHz |   OFF  | DSI lanebyte clock
  RTCDIV               |HSE      |    0.923077 MHz |   ON   |
    RTC                |RTCDIV   |    0.923077 MHz |   ON   |
  PLL1                 |HSE      | 1296.000000 MHz |   ON   |
    PLL1P              |PLL1     |  648.000000 MHz |   ON   |
      Cortex-A7        |PLL1P    |  648.000000 MHz |   ON   |
        MCO2           |Cortex-A7|  648.000000 MHz |   OFF  |
  PLL2                 |HSE      | 1056.000000 MHz |   ON   |
    PLL2P              |PLL2     |  264.000000 MHz |   ON   |
      AXI              |PLL2P    |  264.000000 MHz |   ON   |
        FMC            |AXI      |  264.000000 MHz |   ON   | NAND flash
        QSPI           |AXI      |  264.000000 MHz |   ON   | NOR flash
        AHB5           |AXI      |  264.000000 MHz |   ON   |
          HASH1        |AHB5     |  264.000000 MHz |   ON   |
          GPIOZ        |AHB5     |  264.000000 MHz |   ON   |
        AHB6           |AXI      |  264.000000 MHz |   ON   |
          USBH         |AHB6     |  264.000000 MHz |   ON   | USB Host hub (Type A)
          APB4         |AHB6     |  132.000000 MHz |   ON   |
            STGEN      |APB4     |  132.000000 MHz |   ON   |
          APB5         |AHB6     |   66.000000 MHz |   ON   | Needs to be <67MHz for BSEC
            BSEC       |APB5     |   66.000000 MHz |   ON   |
            ETZPC      |APB5     |   66.000000 MHz |   ON   |
            TZC400     |APB5     |   66.000000 MHz |   ON   |
            I2C4       |APB5     |   66.000000 MHz |   ON   | PMIC
            SPI6       |APB5     |   66.000000 MHz |   ON   |
            USART1     |APB5     |   66.000000 MHz |   ON   |
        DEBUG          |AXI      |  132.000000 MHz |   ON   | JTAG & Coresight
    PLL2Q              |PLL2     |  528.000000 MHz |   ON   |
      GPU              |PLL2Q    |  528.000000 MHz |   ON   |
    PLL2R              |PLL2     |  528.000000 MHz |   ON   |
      DDR              |PLL2R    |  528.000000 MHz |   ON   | DDR3
  PLL3                 |HSE      |  688.000000 MHz |   ON   |
    PLL3P              |PLL3     |  172.000000 MHz |   ON   |
      MLAHB            |PLL3P    |  172.000000 MHz |   ON   | <200MHz
        Cortex-M4      |MLAHB    |  172.000000 MHz |   ON   |
        MCUSRAM        |MLAHB    |  172.000000 MHz |   ON   |
        AHB1           |MLAHB    |  172.000000 MHz |   ON   | <200MHz
          DMA1/2       |AHB1     |  172.000000 MHz |   ON   |
        AHB2           |MLAHB    |  172.000000 MHz |   ON   | <200MHz
        APB1           |MLAHB    |   86.000000 MHz |   ON   |
          I2C2         |APB1     |   86.000000 MHz |   ON   | RPI2ID, USBHub, AudCodec,Cam, MFX, Disp, Eth
          I2C5         |APB1     |   86.000000 MHz |   ON   | RPI2
          UART4        |APB1     |   86.000000 MHz |   ON   | Linux console
          USART3       |APB1     |   86.000000 MHz |   ON   | RPI2
        TIM2           |MLAHB    |  172.000000 MHz |   ON   | TIMG1
        TIM12          |MLAHB    |  172.000000 MHz |   ON   | TIMG1
        APB2           |MLAHB    |   86.000000 MHz |   ON   |
        TIM8           |MLAHB    |  172.000000 MHz |   ON   | TIMG2
        APB3           |MLAHB    |   86.000000 MHz |   ON   |
        AHB3           |MLAHB    |  172.000000 MHz |   ON   | <200MHz
          DCMI         |AHB3     |  172.000000 MHz |   ON   | Camera
        AHB4           |MLAHB    |  172.000000 MHz |   ON   | <200MHz
          PWR          |AHB4     |  172.000000 MHz |   ON   |
          RCC          |AHB4     |  172.000000 MHz |   ON   |
          EXTI         |AHB4     |  172.000000 MHz |   ON   |
    PLL3Q              |PLL3     |   49.142857 MHz |   ON   |
      SPDIF            |PLL3Q    |   49.142857 MHz |   ON   | SPDIF RX
      DFSDM            |PLL3Q    |   49.142857 MHz |   ON   | Digital micro
      SAI2             |PLL3Q    |   49.142857 MHz |   ON   | AudCodec 48kHz (use PLL4Q 79MHz for 44.1kHz)
      SAI4             |PLL3Q    |   49.142857 MHz |   ON   | SPDIF TX 48kHz (use PLL4Q 79MHz for 44.1kHz)
    PLL3R              |PLL3     |  172.000000 MHz |   ON   |
      SDMMC1           |PLL3R    |  172.000000 MHz |   ON   | µSD card
      SDMMC2           |PLL3R    |  172.000000 MHz |   ON   | eMMC
      SDMMC3           |PLL3R    |  172.000000 MHz |   ON   | Wifi
  PLL4                 |HSE      |  632.000000 MHz |   ON   |
    PLL4P              |PLL4     |  126.400002 MHz |   ON   |
    PLL4Q              |PLL4     |   79.000000 MHz |   ON   |
      LCD              |PLL4Q    |   79.000000 MHz |   ON   | LTDC & DSI display pixel clock
      ADC              |PLL4Q    |   79.000000 MHz |   ON   | Use ADC internal divider to be <72MHz
      FDCAN            |PLL4Q    |   79.000000 MHz |   ON   |
    PLL4R              |PLL4     |   63.200001 MHz |   ON   |
  USBPHYC              |HSE      |   24.000000 MHz |   ON   | USB PHY Ctrl for USB Host and OTG
    USBPLL             |USBPHYC  |   48.000000 MHz |   ON   |
      USBO             |USBPLL   |   48.000000 MHz |   ON   | USB OTG (micro AB)
CSI                    |N.A.     |    4.000000 MHz |   ON   | Mandatory for IO compensation
ck_per                 |N.A.     |    0.000000 MHz |   OFF  |
ETH                    |N.A.     |    0.000000 MHz |   OFF  | ETH clocked by RGMII PHY on EVAL
-----------------------|---------|-----------------|--------|-----------------------------------*/
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_PLLInitTypeDef RCC_Pll1InitStruct = {0};
  RCC_PLLInitTypeDef RCC_Pll4InitStruct = {0};
  RCC_PLLInitTypeDef RCC_Pll5InitStruct = {0};
  RCC_PLLInitTypeDef RCC_Pll6InitStruct = {0};
  RCC_PLLInitTypeDef RCC_Pll7InitStruct = {0};
  RCC_PLLInitTypeDef RCC_Pll8InitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Reset clocks to a known state */
  HAL_RCC_DeInit();

  /* Enable all available oscillators*/
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE |
                                     RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
  RCC_OscInitStruct.LSEDriveValue = RCC_LSEDRIVE_MEDIUMHIGH;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    /* HAL RCC configuration error */
    Error_Handler();
  }

  /* 1000MHz */
  RCC_Pll1InitStruct.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_Pll1InitStruct.PLLMode = 0;
  RCC_Pll1InitStruct.FBDIV = 25;
  RCC_Pll1InitStruct.FREFDIV = 1;
  RCC_Pll1InitStruct.POSTDIV1 = 1;
  RCC_Pll1InitStruct.POSTDIV2 = 1;
  RCC_Pll1InitStruct.PLLState = RCC_PLL_ON;

  /* 1200MHz */
  RCC_Pll4InitStruct.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_Pll4InitStruct.PLLMode = 0;
  RCC_Pll4InitStruct.FBDIV = 60;
  RCC_Pll4InitStruct.FREFDIV = 2;
  RCC_Pll4InitStruct.POSTDIV1 = 1;
  RCC_Pll4InitStruct.POSTDIV2 = 1;
  RCC_Pll4InitStruct.PLLState = RCC_PLL_ON;

  /* 532MHz */
  RCC_Pll5InitStruct.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_Pll5InitStruct.PLLMode = 0;
  RCC_Pll5InitStruct.FBDIV = 53;
  RCC_Pll5InitStruct.FREFDIV = 4;
  RCC_Pll5InitStruct.FRACIN = 3355500;
  RCC_Pll5InitStruct.POSTDIV1 = 1;
  RCC_Pll5InitStruct.POSTDIV2 = 1;
  RCC_Pll5InitStruct.PLLState = RCC_PLL_ON;

  /* 500MHz */
  RCC_Pll6InitStruct.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_Pll6InitStruct.PLLMode = 0;
  RCC_Pll6InitStruct.FBDIV = 25;
  RCC_Pll6InitStruct.FREFDIV = 1;
  RCC_Pll6InitStruct.POSTDIV1 = 2;
  RCC_Pll6InitStruct.POSTDIV2 = 1;
  RCC_Pll6InitStruct.PLLState = RCC_PLL_ON;

  /* 491.5MHz */
  RCC_Pll7InitStruct.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_Pll7InitStruct.PLLMode = 0;
  RCC_Pll7InitStruct.FBDIV = 49;
  RCC_Pll7InitStruct.FREFDIV = 2;
  RCC_Pll7InitStruct.FRACIN = 2516600;
  RCC_Pll7InitStruct.POSTDIV1 = 2;
  RCC_Pll7InitStruct.POSTDIV2 = 1;
  RCC_Pll7InitStruct.PLLState = RCC_PLL_ON;

  /* 451.5MHz */
  RCC_Pll8InitStruct.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_Pll8InitStruct.PLLMode = 0;
  RCC_Pll8InitStruct.FBDIV = 45;
  RCC_Pll8InitStruct.FREFDIV = 2;
  RCC_Pll8InitStruct.FRACIN = 2516600;
  RCC_Pll8InitStruct.POSTDIV1 = 2;
  RCC_Pll8InitStruct.POSTDIV2 = 1;
  RCC_Pll8InitStruct.PLLState = RCC_PLL_ON;

  /* Feed A35 on another source than PLL1 */
  HAL_RCCEx_CA35SS_SetCA35SSClockSource(A35_SOURCE_EXT);

  if (HAL_RCCEx_CA35SS_PLL1Config(&RCC_Pll1InitStruct) != HAL_OK)
  {
    printf("SystemClock_Config: Failed to enable PLL1.\n\r");
    printf("SystemClock_Config: Staying on external clock.\n\r");
    while (1);
  }

  /* Switch back A35 on PLL1 */
  HAL_RCCEx_CA35SS_SetCA35SSClockSource(A35_SOURCE_PLL1);

  if (HAL_RCCEx_PLL4Config(&RCC_Pll4InitStruct) != HAL_OK)
  {
    printf("SystemClock_Config: Failed to enable PLL4.\n\r");
    while (1);
  }

  if (HAL_RCCEx_PLL5Config(&RCC_Pll5InitStruct) != HAL_OK)
  {
    printf("SystemClock_Config: Failed to enable PLL5.\n\r");
    while (1);
  }

  if (HAL_RCCEx_PLL6Config(&RCC_Pll6InitStruct) != HAL_OK)
  {
    printf("SystemClock_Config: Failed to enable PLL6.\n\r");
    while (1);
  }

  if (HAL_RCCEx_PLL7Config(&RCC_Pll7InitStruct) != HAL_OK)
  {
    printf("SystemClock_Config: Failed to enable PLL7.\n\r");
    while (1);
  }

  if (HAL_RCCEx_PLL8Config(&RCC_Pll8InitStruct) != HAL_OK)
  {
    printf("SystemClock_Config: Failed to enable PLL8.\n\r");
    while (1);
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_ICN_HS_MCU | RCC_CLOCKTYPE_ICN_LS_MCU |
                                RCC_CLOCKTYPE_ICN_SDMMC | RCC_CLOCKTYPE_ICN_DDR |
                                RCC_CLOCKTYPE_ICN_DISPLAY | RCC_CLOCKTYPE_ICN_HCL |
                                RCC_CLOCKTYPE_ICN_NIC | RCC_CLOCKTYPE_ICN_VID |
                                RCC_CLOCKTYPE_ICN_APB1 | RCC_CLOCKTYPE_ICN_APB2 |
                                RCC_CLOCKTYPE_ICN_APB3 | RCC_CLOCKTYPE_ICN_APB4 |
                                RCC_CLOCKTYPE_ICN_APBDBG;

  RCC_ClkInitStruct.ICN_HS_MCU.XBAR_ClkSrc = RCC_XBAR_CLKSRC_PLL4;
  RCC_ClkInitStruct.ICN_HS_MCU.Div = 3;
  RCC_ClkInitStruct.ICN_SDMMC.XBAR_ClkSrc = RCC_XBAR_CLKSRC_PLL4;
  RCC_ClkInitStruct.ICN_SDMMC.Div = 6;
  RCC_ClkInitStruct.ICN_DDR.XBAR_ClkSrc = RCC_XBAR_CLKSRC_PLL4;
  RCC_ClkInitStruct.ICN_DDR.Div = 2;
  RCC_ClkInitStruct.ICN_DISPLAY.XBAR_ClkSrc = RCC_XBAR_CLKSRC_PLL4;
  RCC_ClkInitStruct.ICN_DISPLAY.Div = 4;
  RCC_ClkInitStruct.ICN_HCL.XBAR_ClkSrc = RCC_XBAR_CLKSRC_PLL4;
  RCC_ClkInitStruct.ICN_HCL.Div = 4;
  RCC_ClkInitStruct.ICN_NIC.XBAR_ClkSrc = RCC_XBAR_CLKSRC_PLL4;
  RCC_ClkInitStruct.ICN_NIC.Div = 3;
  RCC_ClkInitStruct.ICN_VID.XBAR_ClkSrc = RCC_XBAR_CLKSRC_PLL4;
  RCC_ClkInitStruct.ICN_VID.Div = 2;
  RCC_ClkInitStruct.ICN_LSMCU_Div = RCC_LSMCU_DIV2;
  RCC_ClkInitStruct.APB1_Div = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2_Div = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB3_Div = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB4_Div = RCC_APB4_DIV1;
  RCC_ClkInitStruct.APBDBG_Div = RCC_APBDBG_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, 0) != HAL_OK)
  {
    /* HAL RCC configuration error */
    Error_Handler();
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

#ifdef __GNUC__
/* With GCC/RAISONANCE, small log_info (option LD Linker->Libraries->Small log_info
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __attribute__(( weak )) __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int __attribute__(( weak )) fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#if defined (__LOG_UART_IO_) || defined (__LOG_TRACE_IO_)
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
#if defined (__LOG_UART_IO_)
extern UART_HandleTypeDef huart;
  HAL_UART_Transmit(&huart, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
#endif
#if defined (__LOG_TRACE_IO_)
	log_buff(ch);
#endif
	return ch;
}
#endif

/**
  * @}
  */

/**
  * @}
  */
