/**
  ******************************************************************************
  * @file    stm32f1xx_hal_uart.h
  * @brief   Header file of UART HAL module.
  ******************************************************************************
  */

#ifndef __STM32F1xx_HAL_UART_H
#define __STM32F1xx_HAL_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal_def.h"

typedef struct
{
  uint32_t BaudRate;
  uint32_t WordLength;
  uint32_t StopBits;
  uint32_t Parity;
  uint32_t Mode;
  uint32_t HwFlowCtl;
  uint32_t OverSampling;
} UART_InitTypeDef;

typedef struct __UART_HandleTypeDef
{
  USART_TypeDef                 *Instance;
  UART_InitTypeDef              Init;
  uint8_t                       *pTxBuffPtr;
  uint16_t                      TxXferSize;
  volatile uint16_t             TxXferCount;
  uint8_t                       *pRxBuffPtr;
  uint16_t                      RxXferSize;
  volatile uint16_t             RxXferCount;
  HAL_LockTypeDef               Lock;
} UART_HandleTypeDef;

HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_HAL_UART_H */
