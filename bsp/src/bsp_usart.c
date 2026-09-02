/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @brief   USART Driver Implementation & Printf Retargeting
  ******************************************************************************
  */

#include "bsp_usart.h"

static UART_HandleTypeDef Uart1Handle;

void BSP_USART1_Init(uint32_t baudrate)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_USART1_CLK_ENABLE();

  /* Configure PA9 (TX) as Alternate Function Push-Pull */
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = 0x03;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Configure PA10 (RX) as Input Floating */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = 0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  Uart1Handle.Instance = USART1;
  Uart1Handle.Init.BaudRate = baudrate;
  Uart1Handle.Init.WordLength = 8;
  Uart1Handle.Init.StopBits = 1;
  Uart1Handle.Init.Parity = 0;
  Uart1Handle.Init.Mode = 3;
  Uart1Handle.Init.HwFlowCtl = 0;

  HAL_UART_Init(&Uart1Handle);
}

void BSP_USART1_SendChar(char ch)
{
  HAL_UART_Transmit(&Uart1Handle, (const uint8_t *)&ch, 1, 1000);
}

void BSP_USART1_SendString(const char *str)
{
  while (*str)
  {
    BSP_USART1_SendChar(*str++);
  }
}

/* Retarget _write for arm-none-eabi-gcc printf output */
int _write(int file, char *ptr, int len)
{
  (void)file;
  HAL_UART_Transmit(&Uart1Handle, (const uint8_t *)ptr, (uint16_t)len, 1000);
  return len;
}

int fputc(int ch, FILE *f)
{
  (void)f;
  BSP_USART1_SendChar((char)ch);
  return ch;
}
