/**
  ******************************************************************************
  * @file    board.c
  * @brief   RT-Thread Nano Board Support File for STM32F103
  ******************************************************************************
  */

#include "bsp.h"

#if defined(RT_USING_NANO)

#define _STM32_SRAM_SIZE      20 /* 20KB for STM32F103C8 / 64KB for STM32F103ZE */
#define _STM32_SRAM_END       (0x20000000 + _STM32_SRAM_SIZE * 1024)

extern int __bss_end__;

void rt_hw_board_init(void)
{
  BSP_Init();

  /* SysTick configuration for RT-Thread (1ms per tick) */
  SysTick_Config(SystemCoreClock / 1000U);

  #if defined(RT_USING_HEAP)
  /* rt_system_heap_init((void*)&__bss_end__, (void*)_STM32_SRAM_END); */
  #endif
}

void SysTick_Handler(void)
{
#if defined(RT_USING_NANO)
  /* RT-Thread Nano tick processing */
  /* rt_interrupt_enter(); */
  /* rt_tick_increase();   */
  /* rt_interrupt_leave(); */
#else
  /* Bare-metal / HAL tick */
  HAL_IncTick();
#endif
}


void rt_hw_console_output(const char *str)
{
  BSP_USART1_SendString(str);
}

char rt_hw_console_getchar(void)
{
  return 0;
}

#endif
