/**
  ******************************************************************************
  * @file    bsp_led.h
  * @brief   LED Driver Interface
  ******************************************************************************
  */

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f1xx_hal.h"

/* LED0 on PC13 (typical BluePill) or PB5/PE5 (typical Dev boards) */
#define LED0_GPIO_PORT        GPIOC
#define LED0_PIN              GPIO_PIN_13

void BSP_LED_Init(void);
void BSP_LED_On(void);
void BSP_LED_Off(void);
void BSP_LED_Toggle(void);

#endif /* __BSP_LED_H */
