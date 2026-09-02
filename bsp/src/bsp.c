/**
  ******************************************************************************
  * @file    bsp.c
  * @brief   Board Support Package Top Initialization
  ******************************************************************************
  */

#include "bsp.h"

void BSP_Init(void)
{
  /* 1. Initialize HAL and Systick */
  HAL_Init();

  /* 2. Configure System Clock (72MHz) */
  SystemClock_Config();

  /* 3. Initialize Board Peripherals */
  BSP_LED_Init();
  BSP_KEY_Init();
  BSP_USART1_Init(115200);

  printf("\r\n========================================\r\n");
  printf("  STM32F103 Embedded Study Project\r\n");
  printf("  Build System : CMake + Ninja\r\n");
  printf("  System Clock : %lu MHz\r\n", (unsigned long)(SystemCoreClock / 1000000U));
  printf("========================================\r\n\r\n");
}
