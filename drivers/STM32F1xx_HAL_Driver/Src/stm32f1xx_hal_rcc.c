/**
  ******************************************************************************
  * @file    stm32f1xx_hal_rcc.c
  * @brief   RCC HAL module driver.
  ******************************************************************************
  */

#include "stm32f1xx_hal.h"

void SystemClock_Config(void)
{
  uint32_t timeout;

  /* HSE ON */
  RCC->CR |= (1U << 16);

  /* Wait for HSE ready with timeout (~500ms at 8MHz HSI) */
  timeout = 5000000U;
  while (!(RCC->CR & (1U << 17)))
  {
    if (--timeout == 0U)
    {
      /* HSE startup failed – fall back to HSI at 8MHz */
      return;
    }
  }

  /* FLASH Latency: 2 wait states for 72MHz */
  *((volatile uint32_t *)(0x40022000)) = 0x12;

  /* PLL: HSE as source, multiply by 9 → 72MHz */
  RCC->CFGR &= ~((0x0FU << 18) | (1U << 16));
  RCC->CFGR |=  ((0x07U << 18) | (1U << 16));  /* PLLMUL=9, PLLSRC=HSE */

  /* AHB Prescaler /1, APB1 /2, APB2 /1 */
  RCC->CFGR &= ~((0x0FU << 4) | (0x07U << 8) | (0x07U << 11));
  RCC->CFGR |=  (0x04U << 8);  /* PPRE1 = /2 (APB1 max 36MHz) */

  /* Enable PLL */
  RCC->CR |= (1U << 24);

  /* Wait for PLL ready with timeout */
  timeout = 5000000U;
  while (!(RCC->CR & (1U << 25)))
  {
    if (--timeout == 0U)
    {
      return;
    }
  }

  /* Select PLL as SYSCLK */
  RCC->CFGR &= ~(0x03U);
  RCC->CFGR |=  0x02U;

  /* Wait until PLL is used as system clock */
  timeout = 5000000U;
  while ((RCC->CFGR & 0x0CU) != 0x08U)
  {
    if (--timeout == 0U)
    {
      return;
    }
  }

  SystemCoreClockUpdate();
}

