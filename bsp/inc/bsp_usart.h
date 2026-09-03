/**
  ******************************************************************************
  * @file    bsp_usart.h
  * @brief   USART Driver Interface with printf retarget
  ******************************************************************************
  */

#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f1xx_hal.h"
#include <stdio.h>

HAL_StatusTypeDef BSP_USART1_Init(uint32_t baudrate);
void BSP_USART1_SendChar(char ch);
void BSP_USART1_SendString(const char *str);

#endif /* __BSP_USART_H */
