/**
  ******************************************************************************
  * @file    bsp_key.h
  * @brief   Key/Button Driver Interface
  ******************************************************************************
  */

#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f1xx_hal.h"

#define KEY0_GPIO_PORT        GPIOA
#define KEY0_PIN              GPIO_PIN_0

typedef enum
{
  KEY_RELEASED = 0,
  KEY_PRESSED  = 1
} Key_StateTypeDef;

void BSP_KEY_Init(void);
Key_StateTypeDef BSP_KEY_GetState(void);

#endif /* __BSP_KEY_H */
