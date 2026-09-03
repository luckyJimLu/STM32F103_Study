#include "system_runtime.h"

#include "app_task.h"
#include "bsp.h"
#include "logger.h"
#include "rthw.h"
#include "rtthread.h"

static struct rt_thread s_app_thread;
static rt_uint8_t s_app_thread_stack[CONFIG_RT_APP_THREAD_STACK_SIZE];
static uint32_t s_hal_tick_fraction;

static void app_thread_entry(void *parameter)
{
    (void)parameter;
    for (;;)
    {
        App_Process(SystemRuntime_GetTickMs());
        rt_thread_mdelay(CONFIG_APP_POLL_INTERVAL_MS);
    }
}

void rt_hw_board_init(void)
{
    if (BSP_Init() != HAL_OK)
    {
        BSP_FatalError("board initialization failed");
    }
    SysTick_Config(SystemCoreClock / CONFIG_RT_TICK_PER_SECOND);
}

void SysTick_Handler(void)
{
    s_hal_tick_fraction += 1000U;
    while (s_hal_tick_fraction >= CONFIG_RT_TICK_PER_SECOND)
    {
        HAL_IncTick();
        s_hal_tick_fraction -= CONFIG_RT_TICK_PER_SECOND;
    }
    rt_interrupt_enter();
    rt_tick_increase();
    rt_interrupt_leave();
}

void rt_hw_console_output(const char *str)
{
#if defined(CONFIG_BSP_USING_USART1)
    BSP_USART1_SendString(str);
#else
    (void)str;
#endif
}

char rt_hw_console_getchar(void)
{
    return 0;
}

uint32_t SystemRuntime_GetTickMs(void)
{
    return HAL_GetTick();
}

void SystemRuntime_DelayMs(uint32_t delay_ms)
{
    rt_thread_mdelay((rt_int32_t)delay_ms);
}

void SystemRuntime_Start(void)
{
    rt_err_t result;
    rt_base_t level = rt_hw_interrupt_disable();

    rt_hw_board_init();
    rt_show_version();
    rt_system_timer_init();
    rt_system_scheduler_init();
    LOG_INFO("RUNTIME", "RT-Thread init tick=%uHz app_stack=%u bytes",
             (unsigned int)CONFIG_RT_TICK_PER_SECOND,
             (unsigned int)CONFIG_RT_APP_THREAD_STACK_SIZE);
    App_Init();

    result = rt_thread_init(&s_app_thread,
                            "app",
                            app_thread_entry,
                            RT_NULL,
                            s_app_thread_stack,
                            sizeof(s_app_thread_stack),
                            CONFIG_RT_APP_THREAD_PRIORITY,
                            CONFIG_RT_APP_THREAD_TIMESLICE);
    if (result != RT_EOK)
    {
        rt_hw_interrupt_enable(level);
        BSP_FatalError("RT-Thread application thread creation failed");
    }

    rt_thread_startup(&s_app_thread);
    LOG_INFO("RUNTIME", "RT-Thread app thread created; starting scheduler");
    rt_system_timer_thread_init();
    rt_thread_idle_init();
    rt_system_scheduler_start();
    BSP_FatalError("RT-Thread scheduler returned");
}
