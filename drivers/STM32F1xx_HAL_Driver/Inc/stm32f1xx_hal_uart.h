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

/* UART Word Length */
#define UART_WORDLENGTH_8B          0x00000000U
#define UART_WORDLENGTH_9B          0x00001000U

/* UART Stop Bits */
#define UART_STOPBITS_1             0x00000000U
#define UART_STOPBITS_2             0x00002000U

/* UART Parity */
#define UART_PARITY_NONE            0x00000000U
#define UART_PARITY_EVEN            0x00000400U
#define UART_PARITY_ODD             0x00000600U

/* UART Transfer Mode */
#define UART_MODE_RX                0x00000004U
#define UART_MODE_TX                0x00000008U
#define UART_MODE_TX_RX             0x0000000CU

/* UART Hardware Flow Control */
#define UART_HWCONTROL_NONE         0x00000000U
#define UART_HWCONTROL_RTS          0x00000100U
#define UART_HWCONTROL_CTS          0x00000200U
#define UART_HWCONTROL_RTS_CTS      0x00000300U


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
