/**
  ******************************************************************************
  * @file    stm32f1xx_hal_uart.c
  * @brief   UART HAL module driver.
  ******************************************************************************
  */

#include "stm32f1xx_hal.h"

HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)
{
  if (huart == NULL || huart->Instance == NULL || huart->Init.BaudRate == 0U)
  {
    return HAL_ERROR;
  }

  uint32_t pclk = SystemCoreClock;
  if (huart->Instance == USART2 || huart->Instance == USART3)
  {
    pclk = SystemCoreClock / 2U; /* APB1 prescaler is fixed to /2. */
  }

  huart->Instance->BRR =
      (pclk + (huart->Init.BaudRate / 2U)) / huart->Init.BaudRate;

  /* Enable USART, TX and RX */
  huart->Instance->CR1 = (1U << USART_CR1_UE_Pos) | (1U << USART_CR1_TE_Pos) | (1U << USART_CR1_RE_Pos);
  huart->Lock = HAL_UNLOCKED;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  if (huart == NULL || pData == NULL || Size == 0)
  {
    return HAL_ERROR;
  }

  __HAL_LOCK(huart);

  for (uint16_t i = 0; i < Size; i++)
  {
    uint32_t tickstart = HAL_GetTick();
    while (!(huart->Instance->SR & (1U << USART_SR_TXE_Pos)))
    {
      if (Timeout != 0xFFFFFFFFU && (HAL_GetTick() - tickstart) >= Timeout)
      {
        __HAL_UNLOCK(huart);
        return HAL_TIMEOUT;
      }
    }
    huart->Instance->DR = (uint16_t)pData[i];
  }

  __HAL_UNLOCK(huart);
  return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  if (huart == NULL || pData == NULL || Size == 0)
  {
    return HAL_ERROR;
  }

  for (uint16_t i = 0; i < Size; i++)
  {
    uint32_t tickstart = HAL_GetTick();
    while (!(huart->Instance->SR & (1U << USART_SR_RXNE_Pos)))
    {
      if (Timeout != 0xFFFFFFFFU && (HAL_GetTick() - tickstart) >= Timeout)
      {
        return HAL_TIMEOUT;
      }
    }
    pData[i] = (uint8_t)(huart->Instance->DR & 0xFFU);
  }

  return HAL_OK;
}
