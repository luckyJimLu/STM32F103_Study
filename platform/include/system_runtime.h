#ifndef SYSTEM_RUNTIME_H
#define SYSTEM_RUNTIME_H

#include <stdint.h>

void SystemRuntime_Start(void) __attribute__((noreturn));
uint32_t SystemRuntime_GetTickMs(void);
void SystemRuntime_DelayMs(uint32_t delay_ms);

#endif
