/**
  ******************************************************************************
  * @file    stm32f1xx_hal.c
  * @brief   HAL initialization and tick management.
  ******************************************************************************
  */

#include "stm32f1xx_hal.h"

volatile uint32_t uwTick = 0U;
static volatile uint32_t uwTickSuspended = 0U;

__attribute__((weak)) void HAL_MspInit(void)
{
}

__attribute__((weak)) void HAL_MspDeInit(void)
{
}

HAL_StatusTypeDef HAL_Init(void)
{
  /* Configure SysTick to generate interrupt every 1ms */
  SysTick_Config(SystemCoreClock / 1000U);

  /* Initialize Low Level Hardware */
  HAL_MspInit();

  return HAL_OK;
}

HAL_StatusTypeDef HAL_DeInit(void)
{
  HAL_MspDeInit();
  return HAL_OK;
}

void HAL_IncTick(void)
{
  if (uwTickSuspended == 0U)
  {
    uwTick += 1U;
  }
}

uint32_t HAL_GetTick(void)
{
  return uwTick;
}

void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a period to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += 1U;
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
}

void HAL_SuspendTick(void)
{
  uwTickSuspended = 1U;
}

void HAL_ResumeTick(void)
{
  uwTickSuspended = 0U;
}
