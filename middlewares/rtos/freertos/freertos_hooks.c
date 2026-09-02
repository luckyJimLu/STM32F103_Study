/**
  ******************************************************************************
  * @file    freertos_hooks.c
  * @brief   FreeRTOS application hook functions for STM32F103
  *          Required when configUSE_MALLOC_FAILED_HOOK = 1
  *          and configCHECK_FOR_STACK_OVERFLOW = 2
  ******************************************************************************
  */

#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"

/* ---------------------------------------------------------------------------
 * vApplicationMallocFailedHook
 * Called when pvPortMalloc() returns NULL.
 * Must be defined when configUSE_MALLOC_FAILED_HOOK = 1.
 * --------------------------------------------------------------------------- */
void vApplicationMallocFailedHook(void)
{
    printf(">> [FreeRTOS] FATAL: Heap allocation failed!\r\n");
    taskDISABLE_INTERRUPTS();
    for (;;);
}

/* ---------------------------------------------------------------------------
 * vApplicationStackOverflowHook
 * Called when a task stack overflow is detected.
 * Must be defined when configCHECK_FOR_STACK_OVERFLOW >= 1.
 * --------------------------------------------------------------------------- */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    printf(">> [FreeRTOS] FATAL: Stack overflow in task [%s]!\r\n", pcTaskName);
    taskDISABLE_INTERRUPTS();
    for (;;);
}

/* ---------------------------------------------------------------------------
 * vApplicationIdleHook  (optional, configUSE_IDLE_HOOK = 0 by default)
 * --------------------------------------------------------------------------- */
__attribute__((weak)) void vApplicationIdleHook(void)
{
    /* Can be used for low-power sleep */
}

/* ---------------------------------------------------------------------------
 * vApplicationTickHook  (optional, configUSE_TICK_HOOK = 0 by default)
 * --------------------------------------------------------------------------- */
__attribute__((weak)) void vApplicationTickHook(void)
{
}
