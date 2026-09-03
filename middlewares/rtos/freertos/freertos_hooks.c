/**
  ******************************************************************************
  * @file    freertos_hooks.c
  * @brief   FreeRTOS application hook functions for STM32F103
  *          Required when configUSE_MALLOC_FAILED_HOOK = 1
  *          and configCHECK_FOR_STACK_OVERFLOW = 2
  ******************************************************************************
  */

#include "FreeRTOS.h"
#include "logger.h"
#include "stm32f1xx_hal.h"
#include "task.h"

extern void xPortSysTickHandler(void);
static uint32_t s_hal_tick_fraction;

/* HAL starts SysTick before the scheduler. Route it safely in both phases. */
void SysTick_Handler(void)
{
    if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED)
    {
        HAL_IncTick();
    }
    else
    {
        xPortSysTickHandler();
    }
}

/* ---------------------------------------------------------------------------
 * vApplicationMallocFailedHook
 * Called when pvPortMalloc() returns NULL.
 * Must be defined when configUSE_MALLOC_FAILED_HOOK = 1.
 * --------------------------------------------------------------------------- */
void vApplicationMallocFailedHook(void)
{
    LOG_FATAL("FREERTOS", "heap allocation failed");
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
#if defined(CONFIG_LOG_ENABLE)
    LOG_FATAL("FREERTOS", "stack overflow task=%s",
              pcTaskName != NULL ? pcTaskName : "unknown");
#else
    (void)pcTaskName;
#endif
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
 * vApplicationTickHook
 * --------------------------------------------------------------------------- */
__attribute__((weak)) void vApplicationTickHook(void)
{
    s_hal_tick_fraction += 1000U;
    while (s_hal_tick_fraction >= CONFIG_FREERTOS_TICK_RATE_HZ)
    {
        HAL_IncTick();
        s_hal_tick_fraction -= CONFIG_FREERTOS_TICK_RATE_HZ;
    }
}
