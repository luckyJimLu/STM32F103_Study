/**
  ******************************************************************************
  * @file    stm32f1xx_hal_gpio.h
  * @brief   Header file of GPIO HAL module.
  ******************************************************************************
  */

#ifndef __STM32F1xx_HAL_GPIO_H
#define __STM32F1xx_HAL_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal_def.h"

#define GPIO_PIN_0                 ((uint16_t)0x0001)
#define GPIO_PIN_1                 ((uint16_t)0x0002)
#define GPIO_PIN_2                 ((uint16_t)0x0004)
#define GPIO_PIN_3                 ((uint16_t)0x0008)
#define GPIO_PIN_4                 ((uint16_t)0x0010)
#define GPIO_PIN_5                 ((uint16_t)0x0020)
#define GPIO_PIN_6                 ((uint16_t)0x0040)
#define GPIO_PIN_7                 ((uint16_t)0x0080)
#define GPIO_PIN_8                 ((uint16_t)0x0100)
#define GPIO_PIN_9                 ((uint16_t)0x0200)
#define GPIO_PIN_10                ((uint16_t)0x0400)
#define GPIO_PIN_11                ((uint16_t)0x0800)
#define GPIO_PIN_12                ((uint16_t)0x1000)
#define GPIO_PIN_13                ((uint16_t)0x2000)
#define GPIO_PIN_14                ((uint16_t)0x4000)
#define GPIO_PIN_15                ((uint16_t)0x8000)
#define GPIO_PIN_All               ((uint16_t)0xFFFF)

typedef enum
{
  GPIO_PIN_RESET = 0u,
  GPIO_PIN_SET
} GPIO_PinState;

typedef enum
{
  GPIO_MODE_INPUT = 0x00000000u,
  GPIO_MODE_OUTPUT_PP = 0x00000001u,
  GPIO_MODE_OUTPUT_OD = 0x00000011u,
  GPIO_MODE_AF_PP = 0x00000002u,
  GPIO_MODE_AF_OD = 0x00000012u,
  GPIO_MODE_ANALOG = 0x00000003u
} GPIO_Mode;

typedef struct
{
  uint32_t Pin;
  uint32_t Mode;
  uint32_t Pull;
  uint32_t Speed;
} GPIO_InitTypeDef;

void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_HAL_GPIO_H */
