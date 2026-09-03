/* RT-Thread Nano Configuration for STM32F103 */

#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

#include "autoconf.h"

#if CONFIG_RT_APP_THREAD_PRIORITY >= CONFIG_RT_THREAD_PRIORITY_MAX
#error "RT-Thread application priority must be below RT_THREAD_PRIORITY_MAX"
#endif

/* RT-Thread Kernel */
#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_MAX CONFIG_RT_THREAD_PRIORITY_MAX
#define RT_TICK_PER_SECOND CONFIG_RT_TICK_PER_SECOND
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4


/* Inter-Thread communication */
#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */
/* Static application threads keep Nano deterministic on the 20KB C8 target. */

/* Console & FinSH */
#if defined(CONFIG_BSP_USING_USART1)
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart1"
#endif

#endif /* RT_CONFIG_H__ */
