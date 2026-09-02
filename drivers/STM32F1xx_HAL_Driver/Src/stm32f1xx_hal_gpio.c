/**
  ******************************************************************************
  * @file    stm32f1xx_hal_gpio.c
  * @brief   GPIO HAL module driver.
  ******************************************************************************
  */

#include "stm32f1xx_hal.h"

void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
  uint32_t pinpos = 0x00U, pos = 0x00U, currentpin = 0x00U;

  for (pinpos = 0x00U; pinpos < 16U; pinpos++)
  {
    pos = ((uint32_t)0x01U) << pinpos;
    currentpin = (GPIO_Init->Pin) & pos;

    if (currentpin == pos)
    {
      if (pinpos < 8U)
      {
        /* Low Register CRL */
        GPIOx->CRL &= ~(0x0FU << (pinpos * 4U));
        if (GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP)
        {
          GPIOx->CRL |= (0x03U << (pinpos * 4U)); /* Output PP 50MHz */
        }
        else if (GPIO_Init->Mode == GPIO_MODE_AF_PP)
        {
          GPIOx->CRL |= (0x0BU << (pinpos * 4U)); /* Alternate Function Output PP 50MHz */
        }
        else if (GPIO_Init->Mode == GPIO_MODE_INPUT)
        {
          if (GPIO_Init->Pull == GPIO_NOPULL)
          {
            /* Floating input: CNF=01, MODE=00 */
            GPIOx->CRL |= (0x04U << (pinpos * 4U));
          }
          else
          {
            /* Input with pull-up/pull-down: CNF=10, MODE=00 */
            GPIOx->CRL |= (0x08U << (pinpos * 4U));
            if (GPIO_Init->Pull == GPIO_PULLUP)
            {
              GPIOx->ODR |= (1U << pinpos);  /* Pull-up: ODR=1 */
            }
            else
            {
              GPIOx->ODR &= ~(1U << pinpos); /* Pull-down: ODR=0 */
            }
          }
        }

      }
      else
      {
        /* High Register CRH */
        uint32_t shift = (pinpos - 8U) * 4U;
        GPIOx->CRH &= ~(0x0FU << shift);
        if (GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP)
        {
          GPIOx->CRH |= (0x03U << shift); /* Output PP 50MHz */
        }
        else if (GPIO_Init->Mode == GPIO_MODE_AF_PP)
        {
          GPIOx->CRH |= (0x0BU << shift); /* AF PP 50MHz */
        }
        else if (GPIO_Init->Mode == GPIO_MODE_INPUT)
        {
          if (GPIO_Init->Pull == GPIO_NOPULL)
          {
            /* Floating input: CNF=01, MODE=00 */
            GPIOx->CRH |= (0x04U << shift);
          }
          else
          {
            /* Input with pull-up/pull-down: CNF=10, MODE=00 */
            GPIOx->CRH |= (0x08U << shift);
            if (GPIO_Init->Pull == GPIO_PULLUP)
            {
              GPIOx->ODR |= (1U << pinpos);  /* Pull-up: ODR=1 */
            }
            else
            {
              GPIOx->ODR &= ~(1U << pinpos); /* Pull-down: ODR=0 */
            }
          }
        }

      }
    }
  }
}

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  if ((GPIOx->IDR & GPIO_Pin) != 0U)
  {
    return GPIO_PIN_SET;
  }
  return GPIO_PIN_RESET;
}

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
  if (PinState != GPIO_PIN_RESET)
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin;
  }
  else
  {
    GPIOx->BRR = (uint32_t)GPIO_Pin;
  }
}

void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t odr = GPIOx->ODR;
  GPIOx->BSRR = ((odr & GPIO_Pin) << 16U) | (~odr & GPIO_Pin);
}
