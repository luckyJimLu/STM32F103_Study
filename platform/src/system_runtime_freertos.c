#include "system_runtime.h"

#include "FreeRTOS.h"
#include "app_task.h"
#include "bsp.h"
#include "task.h"

static void app_task_entry(void *parameter)
{
    (void)parameter;
    for (;;)
    {
        App_Process(SystemRuntime_GetTickMs());
        vTaskDelay(pdMS_TO_TICKS(CONFIG_APP_POLL_INTERVAL_MS));
    }
}

uint32_t SystemRuntime_GetTickMs(void)
{
    return HAL_GetTick();
}

void SystemRuntime_DelayMs(uint32_t delay_ms)
{
    vTaskDelay(pdMS_TO_TICKS(delay_ms));
}

void SystemRuntime_Start(void)
{
    /* Four pre-emption priority bits and no sub-priority bits. */
    SCB->AIRCR = (0x5FAUL << 16U) |
                 ((SCB->AIRCR & 0x0000F8FFUL) | (3UL << 8U));

    if (BSP_Init() != HAL_OK)
    {
        BSP_FatalError("board initialization failed");
    }
    App_Init();

    if (xTaskCreate(app_task_entry,
                    "app",
                    CONFIG_FREERTOS_APP_TASK_STACK_WORDS,
                    NULL,
                    CONFIG_FREERTOS_APP_TASK_PRIORITY,
                    NULL) != pdPASS)
    {
        BSP_FatalError("FreeRTOS application task creation failed");
    }

    vTaskStartScheduler();
    BSP_FatalError("FreeRTOS scheduler returned");
}
