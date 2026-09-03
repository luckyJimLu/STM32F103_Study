#ifndef BSP_H
#define BSP_H

#include "autoconf.h"
#include "stm32f1xx_hal.h"

#if defined(CONFIG_BSP_USING_LED)
#include "bsp_led.h"
#endif
#if defined(CONFIG_BSP_USING_KEY)
#include "bsp_key.h"
#endif
#if defined(CONFIG_BSP_USING_USART1)
#include "bsp_usart.h"
#endif

HAL_StatusTypeDef BSP_Init(void);
void BSP_FatalError(const char *reason) __attribute__((noreturn));

#endif
