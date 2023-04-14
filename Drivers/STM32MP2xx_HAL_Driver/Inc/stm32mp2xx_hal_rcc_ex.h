/**
  ******************************************************************************
  * @file    stm32mp25_hal_rcc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL Extended  module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_HAL_RCC_EX_H
#define STM32MP2xx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup RCCEx
  * @{
  */

/** @defgroup RCCEx_RCC_BootCx RCC BootCx
  * @{
  */
#define RCC_BOOT_C1                     RCC_STBYBOOTCR_CPU1_HW_BEN
#define RCC_BOOT_C2                     RCC_STBYBOOTCR_CPU2_HW_BEN

#define IS_RCC_BOOT_CORE(CORE)          (((CORE) == RCC_BOOT_C1)  || \
                                         ((CORE) == RCC_BOOT_C2)  || \
                                         ((CORE) == (RCC_BOOT_C1 | RCC_BOOT_C2) ))

/**
  * @}
  */

/** @defgroup RCCEx_RCC_XBar RCC XBar Div
  * @{
  */
#define IS_RCC_XBARDIV(__DIV__) ((((__DIV__) >=    1UL) && ((__DIV__) <=    64UL)) || \
                                 (((__DIV__) >=    2UL) && ((__DIV__) <=   128UL) && (((__DIV__) %    2UL) == 0UL)) || \
                                 (((__DIV__) >=    4UL) && ((__DIV__) <=   256UL) && (((__DIV__) %    4UL) == 0UL)) || \
                                 (((__DIV__) >= 1024UL) && ((__DIV__) <= 65536UL) && (((__DIV__) % 1024UL) == 0UL)))

#define IS_RCC_D3_SOURCE(SOURCE) (((SOURCE) == RCC_D3SOURCE_MSI) || ((SOURCE) == RCC_D3SOURCE_LSI) || \
                                  ((SOURCE) == RCC_D3SOURCE_LSE))

/**
  * @}
  */

#if defined(CORE_CA35)
/* CA35SS Clock Lock time outs */
#define PLL1_LOCK_TIMEOUT_VALUE    (2U)    /* 2 ms (minimum Tick + 1) but real lock time is less than one tick */
#define CHGCLK_TIMEOUT_VALUE       (2U)    /* 2 ms (minimum Tick + 1) but real lock time is less than one tick */

#define SSCG_ON                   0x1U
#define FRAC_ON                   0x1U
#define A35_SOURCE_PLL1           0x0U
#define A35_SOURCE_EXT            0x1U
#endif /* CORE_CA35 */

/** @defgroup RCC_PLL_State  RCC PLL State
  * @{
  */
#define RCC_PLL_OFF                  0x00000000U
#define RCC_PLL_ON                   0x00000001U

/**
  * @}
  */

/** @defgroup RCC_PLL_Mode  RCC PLL Mode
  * @{
  */
#define RCC_PLL_SPREAD_SPECTRUM 0x01U
/**
  * @}
  */

/** @defgroup RCC_PLL_Spread_Spectrum_Mode  RCC PLL Spread Spectrum mode
  * @{
  */
#define RCC_PLL_CENTERSPREAD    0x00U
#define RCC_PLL_DOWNSPREAD      0x01U
/**
  * @}
  */

/** @defgroup RCC_PLL_Clock_Source  RCC PLL Clock Source
  * @{
  */
#define RCC_PLLSOURCE_HSI       0x00000000U
#define RCC_PLLSOURCE_HSE       0x00000001U
#define RCC_PLLSOURCE_MSI       0x00000002U
/**
  * @}
  */

/** @defgroup RCC_D3_Clock_Source  RCC D3 Clock Source
  * @{
  */
#define RCC_D3SOURCE_MSI       0x00000000U
#define RCC_D3SOURCE_LSI       RCC_D3DCR_D3PERCKSEL_0
#define RCC_D3SOURCE_LSE       RCC_D3DCR_D3PERCKSEL_1
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Types RCCEx Exported Types
  * @{
  */

/**
  * @brief  RCC PLL configuration structure definition
  */
typedef struct
{
  uint32_t id;          /*!< The PLL id from 2 to 8       */
  uint32_t PLLSource;   /*!< The new source of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Clock_Source                */
  uint8_t  PLLState;    /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_State                       */
  uint8_t  PLLMode;     /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Mode                        */
  uint8_t  FREFDIV;
  uint16_t FBDIV;
  uint32_t FRACIN;
  uint32_t POSTDIV1;
  uint32_t POSTDIV2;
  uint32_t SSM_Mode;     /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Spread_Spectrum_Mode        */

  uint32_t SSM_SPREAD;
  uint32_t SSM_DIVVAL;
} RCC_PLLInitTypeDef;

#define RCC_PeriphCLKInitTypeDef        RCC_FlexgenTypeDef

/**
  * @}
  */

/**
  * @brief Clock observer structure definition.
  */
typedef struct
{
  uint32_t      Enable;         /*!< To enable or disable the oberver */
  uint32_t      RCC_MCOx;       /*!< To select the MCO instance */
  uint32_t      RCC_MCOSource;  /*!< To select the MCO source */
  uint32_t      RCC_MCODiv;     /*!< To select the MCO division factor */
  uint32_t      ObsDiv;         /*!< To select the observer division factor */
  uint32_t      ObsInv;         /*!< To select the observer inversion */
  uint32_t      ObsType;        /*!< To select oscillator or flexgen observation */
  uint32_t      ClockType;      /*!< To select the internal or external clock */
} RCC_ObserverTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Constants RCCEx Exported Constants
  * @{
  */

/** @defgroup RCCEx_ConfigureClockObserver  RCCEx Configure Clock Observer
  * @{
  */
#define RCC_FLEXGEN0                    0U
#define RCC_FLEXGEN1                    1U
#define RCC_FLEXGEN2                    2U
#define RCC_FLEXGEN3                    3U
#define RCC_FLEXGEN4                    4U
#define RCC_FLEXGEN5                    5U
#define RCC_FLEXGEN6                    6U
#define RCC_HSICK                       0U
#define RCC_HSECK                       1U
#define RCC_MSICK                       2U
#define RCC_PLL4REF                     5U
#define RCC_PLL5REF                     6U
#define RCC_PLL6REF                     7U
#define RCC_PLL7REF                     8U
#define RCC_PLL8REF                     9U
#define RCC_PLL1REF                     10U
#define RCC_PLL2REF                     11U
#define RCC_PLL3REF                     12U
#define RCC_PLL4OUT                     64U
#define RCC_PLL5OUT                     65U
#define RCC_PLL6OUT                     66U
#define RCC_PLL7OUT                     67U
#define RCC_PLL8OUT                     68U
#define RCC_HSIKER                      128U
#define RCC_HSEKER                      129U
#define RCC_MSIKER                      130U
#define RCC_SPDIF                       131U
#define RCC_I2S                         132U
#define RCC_LSICK                       133U
#define RCC_LSECK                       134U
#define RCC_XBARFSM                     135U
#define RCC_ICN_P_RCC                   136U

#define RCC_PLL1DIV42                   0U
#define RCC_PLL2DIV4                    1U
#define RCC_PLL3DIV2                    2U
#define RCC_USB2PHY1                    3U
#define RCC_USB2PHY2                    4U
#define RCC_USB3PCIEPHY                 5U
#define RCC_LVDSPHY                     6U
#define RCC_DSIPHY                      7U

#define RCC_FLEXGEN_OBS        0x00000000U
#define RCC_OSC_OBS            0x00000001U
#define RCC_INTERNAL_OBS       0x00000001U
#define RCC_EXTERNAL_OBS       0x00000002U
#define RCC_CLOCKOBS_OFF        0x00000000U
#define RCC_CLOCKOBS_ON         0x00000001U
#define RCC_CLOCKOBS_NOT_INV    0x00000000U
#define RCC_CLOCKOBS_INV        0x00000001U

#define RCC_OBS_DIV1           0x00000000U
#define RCC_OBS_DIV2           0x00000001U
#define RCC_OBS_DIV4           0x00000002U
#define RCC_OBS_DIV8           0x00000003U
#define RCC_OBS_DIV16          0x00000004U
#define RCC_OBS_DIV32          0x00000005U
#define RCC_OBS_DIV64          0x00000006U
#define RCC_OBS_DIV128         0x00000007U
/**
  * @}
  */

/** @defgroup RCCEx_Periph_Clock_Selection  RCCEx Periph Clock Selection
  * @{
  */
#define RCC_PERIPHCLK_LPTIM1_2          7U
#define RCC_PERIPHCLK_UART2_4           8U
#define RCC_PERIPHCLK_UART3_5           9U
#define RCC_PERIPHCLK_SPI2_3            10U
#define RCC_PERIPHCLK_SPDIFRX           11U
#define RCC_PERIPHCLK_I2C1_2            12U
#define RCC_PERIPHCLK_I3C1_2            12U
#define RCC_PERIPHCLK_I2C3_5            13U
#define RCC_PERIPHCLK_I3C3              13U
#define RCC_PERIPHCLK_I2C4_6            14U
#define RCC_PERIPHCLK_I2C7              15U
#define RCC_PERIPHCLK_SPI1              16U
#define RCC_PERIPHCLK_SPI4_5            17U
#define RCC_PERIPHCLK_SPI6_7            18U
#define RCC_PERIPHCLK_USART1            19U
#define RCC_PERIPHCLK_USART6            20U
#define RCC_PERIPHCLK_UART7_8           21U
#define RCC_PERIPHCLK_UART9             22U
#define RCC_PERIPHCLK_SAI1_MDF1         23U
#define RCC_PERIPHCLK_SAI2              24U
#define RCC_PERIPHCLK_SAI3_4            25U
#define RCC_PERIPHCLK_FDCAN             26U
#define RCC_PERIPHCLK_LTDC              27U
#define RCC_PERIPHCLK_DSIPHY            28U
#define RCC_PERIPHCLK_DCMIPP            29U
#define RCC_PERIPHCLK_CSITXESC          30U
#define RCC_PERIPHCLK_CSIPHY            31U
#define RCC_PERIPHCLK_LVDSPHY           32U
#define RCC_PERIPHCLK_STGEN             33U
#define RCC_PERIPHCLK_USB3PCIEPHY       34U
#define RCC_PERIPHCLK_USBTC             35U
#define RCC_PERIPHCLK_I3C4              36U
#define RCC_PERIPHCLK_SPI8              37U
#define RCC_PERIPHCLK_I2C8              38U
#define RCC_PERIPHCLK_LPUART1           39U
#define RCC_PERIPHCLK_LPTIM3            40U
#define RCC_PERIPHCLK_LPTIM4_5          41U
#define RCC_PERIPHCLK_ADF1              42U
#define RCC_PERIPHCLK_TSDBG             43U
#define RCC_PERIPHCLK_TPIU              44U
#define RCC_PERIPHCLK_ATB               45U
#define RCC_PERIPHCLK_ADC12             46U
#define RCC_PERIPHCLK_ADC3              47U
#define RCC_PERIPHCLK_OSPI1             48U
#define RCC_PERIPHCLK_OSPI2             49U
#define RCC_PERIPHCLK_FMC               50U
#define RCC_PERIPHCLK_SDMMC1            51U
#define RCC_PERIPHCLK_SDMMC2            52U
#define RCC_PERIPHCLK_SDMMC3            53U
#define RCC_PERIPHCLK_ETH1_ETHSW        54U
#define RCC_PERIPHCLK_ETH2              55U
#define RCC_PERIPHCLK_ETH1PTP_ETH2PTP   56U
#define RCC_PERIPHCLK_USB2PHY1          57U
#define RCC_PERIPHCLK_USB2PHY2          58U
#define RCC_PERIPHCLK_ICN_M_GPU         59U
#define RCC_PERIPHCLK_ETHSWREF          60U
#define RCC_PERIPHCLK_MCO1              61U
#define RCC_PERIPHCLK_MCO2              62U
#define RCC_PERIPHCLK_CPU1_EXT2F        63U
#define RCC_PERIPHCLK_TIM1              64U
#define RCC_PERIPHCLK_TIM2              65U
#define RCC_PERIPHCLK_TIM3              66U
#define RCC_PERIPHCLK_TIM4              67U
#define RCC_PERIPHCLK_TIM5              68U
#define RCC_PERIPHCLK_TIM6              69U
#define RCC_PERIPHCLK_TIM7              70U
#define RCC_PERIPHCLK_TIM8              71U
#define RCC_PERIPHCLK_TIM10             72U
#define RCC_PERIPHCLK_TIM11             73U
#define RCC_PERIPHCLK_TIM12             74U
#define RCC_PERIPHCLK_TIM13             75U
#define RCC_PERIPHCLK_TIM14             76U
#define RCC_PERIPHCLK_TIM15             77U
#define RCC_PERIPHCLK_TIM16             78U
#define RCC_PERIPHCLK_TIM17             79U
#define RCC_PERIPHCLK_TIM20             80U
/**
  * @}
  */

/** @defgroup RCCEx_FrequencyCalculator_ReferenceClockSelection  RCCEx FCALC Reference Clock Selection
  * @{
  */
#define RCC_FCALC_PLL4REFCLOCK       0U
#define RCC_FCALC_PLL5REFCLOCK       1U
#define RCC_FCALC_PLL6REFCLOCK       2U
#define RCC_FCALC_PLL7REFCLOCK       3U
#define RCC_FCALC_PLL8REFCLOCK       4U
/**
  * @}
  */

/** @defgroup RCCEx_FrequencyCalculator_ObservationClockSelection  RCCEx FCALC Observation Clock Selection
  * @{
  */
#define RCC_FCALC_INTOBSCLK_HSI_CK          0x000
#define RCC_FCALC_INTOBSCLK_HSE_CK          0x001
#define RCC_FCALC_INTOBSCLK_MSI_CK          0x002

#define RCC_FCALC_INTOBSCLK_PLL4REF_CK      0x005
#define RCC_FCALC_INTOBSCLK_PLL5REF_CK      0x006
#define RCC_FCALC_INTOBSCLK_PLL6REF_CK      0x007
#define RCC_FCALC_INTOBSCLK_PLL7REF_CK      0x008
#define RCC_FCALC_INTOBSCLK_PLL8REF_CK      0x009
#define RCC_FCALC_INTOBSCLK_PLL1REF_CK      0x00A
#define RCC_FCALC_INTOBSCLK_PLL2REF_CK      0x00B
#define RCC_FCALC_INTOBSCLK_PLL3REF_CK      0x00C

#define RCC_FCALC_INTOBSCLK_PLL4OUT_CK      0x040
#define RCC_FCALC_INTOBSCLK_PLL5OUT_CK      0x041
#define RCC_FCALC_INTOBSCLK_PLL6OUT_CK      0x042
#define RCC_FCALC_INTOBSCLK_PLL7OUT_CK      0x043
#define RCC_FCALC_INTOBSCLK_PLL8OUT_CK      0x044

#define RCC_FCALC_INTOBSCLK_HSI_KER_CK      0x080
#define RCC_FCALC_INTOBSCLK_HSE_KER_CK      0x081
#define RCC_FCALC_INTOBSCLK_MSI_KER_CK      0x082
#define RCC_FCALC_INTOBSCLK_SPDIF_SYMB_CK   0x083
#define RCC_FCALC_INTOBSCLK_I2S_CK          0x084
#define RCC_FCALC_INTOBSCLK_LSI_CK          0x085
#define RCC_FCALC_INTOBSCLK_LSE_CK          0x086
#define RCC_FCALC_INTOBSCLK_CK_XBAR_FSM     0x087
#define RCC_FCALC_INTOBSCLK_CK_ICN_P_RCC    0x088

#define RCC_FCALC_INTOBSCLK_FINDDIV0        0x0C0
#define RCC_FCALC_INTOBSCLK_FINDDIV1        0x0C1
#define RCC_FCALC_INTOBSCLK_FINDDIV2        0x0C2
#define RCC_FCALC_INTOBSCLK_FINDDIV3        0x0C3
#define RCC_FCALC_INTOBSCLK_FINDDIV4        0x0C4
#define RCC_FCALC_INTOBSCLK_FINDDIV5        0x0C5
#define RCC_FCALC_INTOBSCLK_FINDDIV6        0x0C6
#define RCC_FCALC_INTOBSCLK_FINDDIV7        0x0C7
#define RCC_FCALC_INTOBSCLK_FINDDIV8        0x0C8
#define RCC_FCALC_INTOBSCLK_FINDDIV9        0x0C9
#define RCC_FCALC_INTOBSCLK_FINDDIV10       0x0CA
#define RCC_FCALC_INTOBSCLK_FINDDIV11       0x0CB
#define RCC_FCALC_INTOBSCLK_FINDDIV12       0x0CC
#define RCC_FCALC_INTOBSCLK_FINDDIV13       0x0CD
#define RCC_FCALC_INTOBSCLK_FINDDIV14       0x0CE
#define RCC_FCALC_INTOBSCLK_FINDDIV15       0x0CF
#define RCC_FCALC_INTOBSCLK_FINDDIV16       0x0D0
#define RCC_FCALC_INTOBSCLK_FINDDIV17       0x0D1
#define RCC_FCALC_INTOBSCLK_FINDDIV18       0x0D2
#define RCC_FCALC_INTOBSCLK_FINDDIV19       0x0D3
#define RCC_FCALC_INTOBSCLK_FINDDIV20       0x0D4
#define RCC_FCALC_INTOBSCLK_FINDDIV21       0x0D5
#define RCC_FCALC_INTOBSCLK_FINDDIV22       0x0D6
#define RCC_FCALC_INTOBSCLK_FINDDIV23       0x0D7
#define RCC_FCALC_INTOBSCLK_FINDDIV24       0x0D8
#define RCC_FCALC_INTOBSCLK_FINDDIV25       0x0D9
#define RCC_FCALC_INTOBSCLK_FINDDIV26       0x0DA
#define RCC_FCALC_INTOBSCLK_FINDDIV27       0x0DB
#define RCC_FCALC_INTOBSCLK_FINDDIV28       0x0DC
#define RCC_FCALC_INTOBSCLK_FINDDIV29       0x0DD
#define RCC_FCALC_INTOBSCLK_FINDDIV30       0x0DE
#define RCC_FCALC_INTOBSCLK_FINDDIV31       0x0DF
#define RCC_FCALC_INTOBSCLK_FINDDIV32       0x0E0
#define RCC_FCALC_INTOBSCLK_FINDDIV33       0x0E1
#define RCC_FCALC_INTOBSCLK_FINDDIV34       0x0E2
#define RCC_FCALC_INTOBSCLK_FINDDIV35       0x0E3
#define RCC_FCALC_INTOBSCLK_FINDDIV36       0x0E4
#define RCC_FCALC_INTOBSCLK_FINDDIV37       0x0E5
#define RCC_FCALC_INTOBSCLK_FINDDIV38       0x0E6
#define RCC_FCALC_INTOBSCLK_FINDDIV39       0x0E7
#define RCC_FCALC_INTOBSCLK_FINDDIV40       0x0E8
#define RCC_FCALC_INTOBSCLK_FINDDIV41       0x0E9
#define RCC_FCALC_INTOBSCLK_FINDDIV42       0x0EA
#define RCC_FCALC_INTOBSCLK_FINDDIV43       0x0EB
#define RCC_FCALC_INTOBSCLK_FINDDIV44       0x0EC
#define RCC_FCALC_INTOBSCLK_FINDDIV45       0x0ED
#define RCC_FCALC_INTOBSCLK_FINDDIV46       0x0EE
#define RCC_FCALC_INTOBSCLK_FINDDIV47       0x0EF
#define RCC_FCALC_INTOBSCLK_FINDDIV48       0x0F0
#define RCC_FCALC_INTOBSCLK_FINDDIV49       0x0F1
#define RCC_FCALC_INTOBSCLK_FINDDIV50       0x0F2
#define RCC_FCALC_INTOBSCLK_FINDDIV51       0x0F3
#define RCC_FCALC_INTOBSCLK_FINDDIV52       0x0F4
#define RCC_FCALC_INTOBSCLK_FINDDIV53       0x0F5
#define RCC_FCALC_INTOBSCLK_FINDDIV54       0x0F6
#define RCC_FCALC_INTOBSCLK_FINDDIV55       0x0F7
#define RCC_FCALC_INTOBSCLK_FINDDIV56       0x0F8
#define RCC_FCALC_INTOBSCLK_FINDDIV57       0x0F9
#define RCC_FCALC_INTOBSCLK_FINDDIV58       0x0FA
#define RCC_FCALC_INTOBSCLK_FINDDIV59       0x0FB
#define RCC_FCALC_INTOBSCLK_FINDDIV60       0x0FC
#define RCC_FCALC_INTOBSCLK_FINDDIV61       0x0FD
#define RCC_FCALC_INTOBSCLK_FINDDIV62       0x0FE
#define RCC_FCALC_INTOBSCLK_FINDDIV63       0x0FF

#define RCC_FCALC_EXTOBSCLK_PLL1DIV42       0x100
#define RCC_FCALC_EXTOBSCLK_PLL2DIV4        0x101
#define RCC_FCALC_EXTOBSCLK_PLL3DIV2        0x102
#define RCC_FCALC_EXTOBSCLK_USB2PHY1PLL     0x103
#define RCC_FCALC_EXTOBSCLK_USB2PHY2PLL     0x104
#define RCC_FCALC_EXTOBSCLK_USB3PCIEPHYPLL  0x105
#define RCC_FCALC_EXTOBSCLK_LVDSPHYPLL      0x106
#define RCC_FCALC_EXTOBSCLK_DSIPHYPLL       0x107
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RCCEx_Exported_Macros RCCEx Exported Macros
  * @{
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCCEx_Exported_Functions
  * @{
  */

/** @addtogroup RCCEx_Exported_Functions_Group1
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);
uint32_t          HAL_RCCEx_GetTimerCLKFreq(uint32_t TimerId);

#if defined(CORE_CA35)
HAL_StatusTypeDef HAL_RCCEx_CA35SS_SetCA35SSClockSource(uint32_t source);
HAL_StatusTypeDef HAL_RCCEx_CA35SS_GetCA35SSClockSource(uint32_t *source);
#endif /* CORE_CA35 */

HAL_StatusTypeDef HAL_RCCEx_SetD3ClockSource(uint32_t source);
uint32_t HAL_RCCEx_GetD3ClockSource(void);

#if defined(CORE_CA35)
HAL_StatusTypeDef HAL_RCCEx_CA35SS_PLL1Config(const RCC_PLLInitTypeDef *pll_config);
#endif /* CORE_CA35 */
HAL_StatusTypeDef HAL_RCCEx_PLL2Config(RCC_PLLInitTypeDef *pll_config);
HAL_StatusTypeDef HAL_RCCEx_PLL3Config(RCC_PLLInitTypeDef *pll_config);
HAL_StatusTypeDef HAL_RCCEx_PLL4Config(RCC_PLLInitTypeDef *pll_config);
HAL_StatusTypeDef HAL_RCCEx_PLL5Config(RCC_PLLInitTypeDef *pll_config);
HAL_StatusTypeDef HAL_RCCEx_PLL6Config(RCC_PLLInitTypeDef *pll_config);
HAL_StatusTypeDef HAL_RCCEx_PLL7Config(RCC_PLLInitTypeDef *pll_config);
HAL_StatusTypeDef HAL_RCCEx_PLL8Config(RCC_PLLInitTypeDef *pll_config);

#if defined(CORE_CA35)
void              HAL_RCCEx_CA35SS_GetPLL1Config(RCC_PLLInitTypeDef *pll_config);
#endif /* CORE_CA35 */
void              HAL_RCCEx_GetPLL2Config(RCC_PLLInitTypeDef  *pll_config);
void              HAL_RCCEx_GetPLL3Config(RCC_PLLInitTypeDef  *pll_config);
void              HAL_RCCEx_GetPLL4Config(RCC_PLLInitTypeDef  *pll_config);
void              HAL_RCCEx_GetPLL5Config(RCC_PLLInitTypeDef  *pll_config);
void              HAL_RCCEx_GetPLL6Config(RCC_PLLInitTypeDef  *pll_config);
void              HAL_RCCEx_GetPLL7Config(RCC_PLLInitTypeDef  *pll_config);
void              HAL_RCCEx_GetPLL8Config(RCC_PLLInitTypeDef  *pll_config);

#if defined(CORE_CA35)
uint32_t          HAL_RCCEx_CA35SS_GetPLL1ClockFreq(void);
#endif /* CORE_CA35 */
uint32_t          HAL_RCCEx_GetPLL2ClockFreq(void);
uint32_t          HAL_RCCEx_GetPLL3ClockFreq(void);
uint32_t          HAL_RCCEx_GetPLL4ClockFreq(void);
uint32_t          HAL_RCCEx_GetPLL5ClockFreq(void);
uint32_t          HAL_RCCEx_GetPLL6ClockFreq(void);
uint32_t          HAL_RCCEx_GetPLL7ClockFreq(void);
uint32_t          HAL_RCCEx_GetPLL8ClockFreq(void);

int HAL_RCCEx_MeasureClockFreq(uint32_t clk_id, uint32_t ref_id, uint32_t *freq);

#if defined(CORE_CA35)
void HAL_RCCEx_EnableBootCore(uint32_t RCC_BootCx);
void HAL_RCCEx_DisableBootCore(uint32_t RCC_BootCx);
void HAL_RCCEx_HoldBootMCU(void);
void HAL_RCCEx_BootMCU(void);
#endif /* CORE_CA35 */
/**
  * @}
  */

/** @addtogroup RCCEx_Exported_Functions_Group2
  * @{
  */

HAL_StatusTypeDef HAL_RCCEx_EnableLSECSS(void);
HAL_StatusTypeDef HAL_RCCEx_DisableLSECSS(void);
void              HAL_RCCEx_EnableHSECSS(void);
void              HAL_RCCEx_DisableHSECSS(void);
void              HAL_RCCEx_LSECSS_IRQHandler(void);
void              HAL_RCCEx_LSECSS_Callback(void);
void              HAL_RCCEx_ConfigureClockObserver(uint32_t PeriphClk, RCC_ObserverTypeDef *OBSConf);

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

#endif /* STM32MP2xx_HAL_RCC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
