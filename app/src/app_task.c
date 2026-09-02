/**
  ******************************************************************************
  * @file    app_task.c
  * @brief   Application tasks & logic implementation
  ******************************************************************************
  */

#include "main.h"

void App_Init(void)
{
  printf(">> App Initialized successfully.\r\n");
}

void App_Loop(void)
{
  /* Toggle LED as heartbeat */
  BSP_LED_Toggle();
  HAL_Delay(APP_LED_BLINK_INTERVAL_MS);

  /* Check button input */
  if (BSP_KEY_GetState() == KEY_PRESSED)
  {
    printf(">> Key Pressed! Heartbeat pulse.\r\n");
  }
}
