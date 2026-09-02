/**
  ******************************************************************************
  * @file    main.c
  * @brief   Main program entry point with macro-driven RTOS support
  ******************************************************************************
  */

#include "main.h"

int main(void)
{
#if defined(CONFIG_USE_RTTHREAD)
  /* RT-Thread Nano initialization is handled by components/board */
  printf(">> Starting RT-Thread Nano OS...\r\n");
  App_Init();
  while (1)
  {
    App_Loop();
  }
#elif defined(CONFIG_USE_FREERTOS)
  /* FreeRTOS initialization */
  BSP_Init();
  printf(">> Starting FreeRTOS Scheduler...\r\n");
  App_Init();
  /* vTaskStartScheduler(); */
  while (1)
  {
    App_Loop();
  }
#else
  /* Default: Bare-metal execution */
  BSP_Init();
  printf(">> Running in Bare-metal mode...\r\n");
  App_Init();

  while (1)
  {
    App_Loop();
  }
#endif
}
