/**
  ******************************************************************************
  * @file    stpmic2_reg.c
  * @author  MCD Application Team
  * @brief   This file provides unitary register function to control the STPMIC2
  *          driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stpmic2_reg.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @addtogroup STPMIC2
  * @brief     This file provides a set of functions needed to drive the
  *            STPMIC2 Power Management Unit.
  * @{
  */

/**
  * @brief  Read STPMIC2 component registers
  * @param  ctx component contex
  * @param  reg Register to read from
  * @param  pdata Pointer to data buffer
  * @param  length Number of data to read
  * @retval Component status
  */
int32_t stpmic2_read_reg(stpmic2_ctx_t *ctx, uint16_t reg, uint8_t *pdata, uint16_t length)
{
  return ctx->ReadReg(ctx->handle, reg, pdata, length);
}

/**
  * @brief  Write STPMIC2 component registers
  * @param  ctx component contex
  * @param  reg Register to write to
  * @param  pdata Pointer to data buffer
  * @param  length Number of data to write
  * @retval Component status
  */
int32_t stpmic2_write_reg(stpmic2_ctx_t *ctx, uint16_t reg, uint8_t *pdata, uint16_t length)
{
  return ctx->WriteReg(ctx->handle, reg, pdata, length);
}

/**
  * @brief  Set STPMIC2 component registers
  * @param  ctx component contex
  * @param  reg Register to write to
  * @param  value data to write
  * @retval Component status
  */
int32_t stpmic2_register_set(stpmic2_ctx_t *ctx, uint16_t reg, uint8_t value)
{
  return 0;
}
/**
  * @brief  Update STPMIC2 component registers
  * @param  ctx component contex
  * @param  reg Register to write to
  * @param  pvalue Pointer to data to write
  * @retval Component status
  */
int32_t stpmic2_register_get(stpmic2_ctx_t *ctx, uint16_t reg, uint8_t *pvalue)
{
  return 0;
}
/**
  * @brief  Update STPMIC2 component registers
  * @param  ctx component contex
  * @param  reg Register to write to
  * @param  pvalue Pointer to data buffer
  * @param  mask data mask
  * @retval Component status
  */
int32_t stpmic2_register_update(stpmic2_ctx_t *ctx, uint16_t reg, uint8_t pvalue, uint8_t mask)
{
  return 0;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
