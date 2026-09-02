/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * STM32F103 HAL-based configuration.
 * Derived from Keil-template-FreeRTOS project by lujingjing.
 *
 * Adapted for CMake + arm-none-eabi-gcc build:
 *   - Removed SPL includes (sys.h / usart.h)
 *   - Added stm32f1xx.h (HAL-based device header)
 *   - Enabled software timers, trace facility, assert
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* STM32F1xx HAL device header (provides SystemCoreClock, __NVIC_PRIO_BITS) */
#include "stm32f1xx.h"

/* ============================================================
 *  Assertion
 * ============================================================ */
#define vAssertCalled(file, line)  do { (void)(file); (void)(line); __asm volatile("BKPT #0"); } while(0)
#define configASSERT(x)            if ((x) == 0) vAssertCalled(__FILE__, __LINE__)

/* ============================================================
 *  Scheduler settings
 * ============================================================ */
#define configUSE_PREEMPTION                    1   /* 抢占式调度 */
#define configUSE_TIME_SLICING                  1   /* 同优先级时间片轮转 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1   /* 硬件 CLZ 快速选优先级 */
#define configUSE_TICKLESS_IDLE                 0   /* 低功耗 tickless（暂关闭）*/
#define configUSE_QUEUE_SETS                    1   /* 队列集 */

/* ============================================================
 *  Clock / Tick
 * ============================================================ */
#define configCPU_CLOCK_HZ                      (SystemCoreClock)   /* 72 MHz */
#define configTICK_RATE_HZ                      ((TickType_t)1000)  /* 1 ms 节拍 */

/* ============================================================
 *  Task settings
 * ============================================================ */
#define configMAX_PRIORITIES                    (32)
#define configMINIMAL_STACK_SIZE                ((uint16_t)130)     /* 最小栈（字 word 单位）*/
#define configMAX_TASK_NAME_LEN                 (16)
#define configUSE_16_BIT_TICKS                  0   /* 32-bit TickType_t */
#define configIDLE_SHOULD_YIELD                 1   /* 空闲任务让出 CPU */

/* ============================================================
 *  Task notifications / IPC
 * ============================================================ */
#define configUSE_TASK_NOTIFICATIONS            1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES   1
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configQUEUE_REGISTRY_SIZE               8

/* ============================================================
 *  Memory allocation
 * ============================================================ */
#define configSUPPORT_STATIC_ALLOCATION         0
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configTOTAL_HEAP_SIZE                   ((size_t)(20 * 1024))  /* 20 KB heap */
#define configAPPLICATION_ALLOCATED_HEAP        0

/* ============================================================
 *  Stack overflow & malloc fail detection
 * ============================================================ */
#define configCHECK_FOR_STACK_OVERFLOW          2   /* 方法2（栈末尾填充检测）*/
#define configUSE_MALLOC_FAILED_HOOK            1   /* 内存申请失败回调 */

/* ============================================================
 *  Hook functions
 * ============================================================ */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configUSE_APPLICATION_TASK_TAG          0

/* ============================================================
 *  Run-time stats / trace
 * ============================================================ */
#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1

/* ============================================================
 *  Co-routines (legacy, not recommended for new code)
 * ============================================================ */
#define configUSE_CO_ROUTINES                   0
#define configMAX_CO_ROUTINE_PRIORITIES         (2)

/* ============================================================
 *  Software timers
 * ============================================================ */
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            (configMINIMAL_STACK_SIZE * 2)

/* ============================================================
 *  INCLUDE_* optional API
 * ============================================================ */
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_xTimerPendFunctionCall          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     1
#define INCLUDE_xTaskGetIdleTaskHandle          1

/* ============================================================
 *  Cortex-M3 interrupt priority configuration
 *  STM32F103: 4-bit priority, NVIC_PRIO_BITS = 4
 * ============================================================ */
#ifdef __NVIC_PRIO_BITS
    #define configPRIO_BITS                     __NVIC_PRIO_BITS        /* = 4 */
#else
    #define configPRIO_BITS                     4
#endif

/* Lowest priority (numerically highest value with 4-bit NVIC) */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15
/* Highest priority allowed to call FreeRTOS FromISR APIs */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

#define configKERNEL_INTERRUPT_PRIORITY     \
    (configLIBRARY_LOWEST_INTERRUPT_PRIORITY      << (8 - configPRIO_BITS))  /* 0xF0 */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))  /* 0x50 */

/* ============================================================
 *  Map FreeRTOS interrupt handler names to CMSIS handler names
 *  (used in port.c, must match startup vector table)
 * ============================================================ */
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
