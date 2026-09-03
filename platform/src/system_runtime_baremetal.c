#include "system_runtime.h"

#include "app_task.h"
#include "bsp.h"
#include "logger.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}

uint32_t SystemRuntime_GetTickMs(void)
{
    return HAL_GetTick();
}

void SystemRuntime_DelayMs(uint32_t delay_ms)
{
    HAL_Delay(delay_ms);
}

void SystemRuntime_Start(void)
{
    if (BSP_Init() != HAL_OK)
    {
        BSP_FatalError("board initialization failed");
    }

    LOG_INFO("RUNTIME", "starting bare-metal super loop");
    App_Init();
    for (;;)
    {
        App_Process(SystemRuntime_GetTickMs());
    }
}
