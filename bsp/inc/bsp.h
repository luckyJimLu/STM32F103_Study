/**
  ******************************************************************************
  * @file    bsp.h
  * @brief   Board Support Package Top Header
  ******************************************************************************
  */

#ifndef __BSP_H
#define __BSP_H

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"


void BSP_Init(void);

#endif /* __BSP_H */
