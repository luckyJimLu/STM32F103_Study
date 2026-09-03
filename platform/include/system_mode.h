#ifndef SYSTEM_MODE_H
#define SYSTEM_MODE_H

#include "autoconf.h"

#define SYSTEM_MODE_BAREMETAL 0
#define SYSTEM_MODE_RTTHREAD  1
#define SYSTEM_MODE_FREERTOS  2

#if defined(CONFIG_RTOS_RTTHREAD)
#define SYSTEM_MODE SYSTEM_MODE_RTTHREAD
#define SYSTEM_NAME_STRING "RT-Thread Nano"
#elif defined(CONFIG_RTOS_FREERTOS)
#define SYSTEM_MODE SYSTEM_MODE_FREERTOS
#define SYSTEM_NAME_STRING "FreeRTOS"
#elif defined(CONFIG_RTOS_NONE)
#define SYSTEM_MODE SYSTEM_MODE_BAREMETAL
#define SYSTEM_NAME_STRING "Bare-metal"
#else
#error "No operating system was selected by Kconfig"
#endif

#endif
