/**
  ******************************************************************************
  * @file    stm32f1xx_hal_rcc.c
  * @brief   RCC HAL module driver.
  ******************************************************************************
  */

#include "stm32f1xx_hal.h"

void SystemClock_Config(void)
{
  /* Basic 72MHz System Clock Configuration using 8MHz HSE */
  /* HSE ON */
  RCC->CR |= (1U << 16);
  while (!(RCC->CR & (1U << 17)));

  /* FLASH Latency: 2 wait states */
  *((volatile uint32_t *)(0x40022000)) = 0x12;

  /* PLL: HSE * 9 = 72MHz */
  RCC->CFGR &= ~((0x0F << 18) | (1U << 16));
  RCC->CFGR |= (0x07 << 18) | (1U << 16);

  /* Enable PLL */
  RCC->CR |= (1U << 24);
  while (!(RCC->CR & (1U << 25)));

  /* AHB Prescaler /1, APB1 /2, APB2 /1 */
  RCC->CFGR &= ~((0x0F << 4) | (0x07 << 8) | (0x07 << 11));
  RCC->CFGR |= (0x04 << 8);

  /* Select PLL as SYSCLK */
  RCC->CFGR &= ~(0x03);
  RCC->CFGR |= 0x02;
  while ((RCC->CFGR & (0x0C)) != 0x08);

  SystemCoreClockUpdate();
}
