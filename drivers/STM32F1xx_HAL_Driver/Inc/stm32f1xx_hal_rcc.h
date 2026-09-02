/**
  ******************************************************************************
  * @file    stm32f1xx_hal_rcc.h
  * @brief   Header file of RCC HAL module.
  ******************************************************************************
  */

#ifndef __STM32F1xx_HAL_RCC_H
#define __STM32F1xx_HAL_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal_def.h"

#define __HAL_RCC_GPIOA_CLK_ENABLE()   do { RCC->APB2ENR |= (1U << 2); } while(0U)
#define __HAL_RCC_GPIOB_CLK_ENABLE()   do { RCC->APB2ENR |= (1U << 3); } while(0U)
#define __HAL_RCC_GPIOC_CLK_ENABLE()   do { RCC->APB2ENR |= (1U << 4); } while(0U)
#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { RCC->APB2ENR |= (1U << 5); } while(0U)
#define __HAL_RCC_GPIOE_CLK_ENABLE()   do { RCC->APB2ENR |= (1U << 6); } while(0U)
#define __HAL_RCC_USART1_CLK_ENABLE()  do { RCC->APB2ENR |= (1U << 14); } while(0U)
#define __HAL_RCC_USART2_CLK_ENABLE()  do { RCC->APB1ENR |= (1U << 17); } while(0U)
#define __HAL_RCC_USART3_CLK_ENABLE()  do { RCC->APB1ENR |= (1U << 18); } while(0U)

void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_HAL_RCC_H */
