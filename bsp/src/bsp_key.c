/**
  ******************************************************************************
  * @file    bsp_key.c
  * @brief   Key/Button Driver Implementation
  ******************************************************************************
  */

#include "bsp_key.h"

void BSP_KEY_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = KEY0_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL; /* External pull-down on board */
  HAL_GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);
}

Key_StateTypeDef BSP_KEY_GetState(void)
{
  if (HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_PIN) == GPIO_PIN_SET)
  {
    HAL_Delay(10); /* Debounce */
    if (HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_PIN) == GPIO_PIN_SET)
    {
      return KEY_PRESSED;
    }
  }
  return KEY_RELEASED;
}
