/**
  ******************************************************************************
  * @file    bsp_led.c
  * @brief   LED Driver Implementation
  ******************************************************************************
  */

#include "bsp_led.h"

void BSP_LED_Init(void)
{
  /* Enable GPIOC clock */
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = LED0_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = 0x03; /* 50MHz */
  HAL_GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);

  /* Default Off (Active Low on most bluepill boards) */
  BSP_LED_Off();
}

void BSP_LED_On(void)
{
  HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_PIN, GPIO_PIN_RESET);
}

void BSP_LED_Off(void)
{
  HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_PIN, GPIO_PIN_SET);
}

void BSP_LED_Toggle(void)
{
  HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_PIN);
}
