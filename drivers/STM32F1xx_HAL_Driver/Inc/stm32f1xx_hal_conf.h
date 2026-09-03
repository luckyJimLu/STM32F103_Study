/**
  ******************************************************************************
  * @file    stm32f1xx_hal_conf.h
  * @brief   HAL configuration file.
  ******************************************************************************
  */

#ifndef __STM32F1xx_HAL_CONF_H
#define __STM32F1xx_HAL_CONF_H

#include "autoconf.h"
#include "product_config.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define HAL_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED

#if !defined  (HSE_VALUE)
  #define HSE_VALUE    PRODUCT_HSE_VALUE_HZ
#endif

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    8000000U /*!< Value of the Internal oscillator in Hz*/
#endif

#define  TICK_INT_PRIORITY            ((uint32_t)0x0FU) /*!< tick interrupt priority */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_rcc.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_uart.h"

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_HAL_CONF_H */
