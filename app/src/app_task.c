#include "app_task.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_config.h"
#include "bsp.h"

#if defined(CONFIG_APP_ENABLE_HEARTBEAT)
static uint32_t s_next_heartbeat_ms;

static bool time_reached(uint32_t now_ms, uint32_t deadline_ms)
{
    return (int32_t)(now_ms - deadline_ms) >= 0;
}
#endif

#if defined(CONFIG_APP_ENABLE_BUTTON_TASK)
static bool s_key_initialized;
static Key_StateTypeDef s_key_stable;
static Key_StateTypeDef s_key_candidate;
static uint32_t s_key_candidate_since_ms;
#endif

void App_Init(void)
{
#if defined(CONFIG_APP_ENABLE_HEARTBEAT)
    s_next_heartbeat_ms = CONFIG_APP_LED_BLINK_INTERVAL_MS;
#endif
#if defined(CONFIG_BSP_USING_USART1)
    printf(">> Application %u.%u.%u initialized.\r\n",
           APP_VERSION_MAJOR,
           APP_VERSION_MINOR,
           APP_VERSION_PATCH);
#endif
}

void App_Process(uint32_t now_ms)
{
#if defined(CONFIG_APP_ENABLE_HEARTBEAT)
    if (time_reached(now_ms, s_next_heartbeat_ms))
    {
        BSP_LED_Toggle();
        do
        {
            s_next_heartbeat_ms += CONFIG_APP_LED_BLINK_INTERVAL_MS;
        } while (time_reached(now_ms, s_next_heartbeat_ms));
    }
#else
    (void)now_ms;
#endif

#if defined(CONFIG_APP_ENABLE_BUTTON_TASK)
    const Key_StateTypeDef raw = BSP_KEY_GetState();

    if (!s_key_initialized)
    {
        s_key_initialized = true;
        s_key_stable = raw;
        s_key_candidate = raw;
        s_key_candidate_since_ms = now_ms;
    }
    else if (raw != s_key_candidate)
    {
        s_key_candidate = raw;
        s_key_candidate_since_ms = now_ms;
    }
    else if ((s_key_candidate != s_key_stable) &&
             ((uint32_t)(now_ms - s_key_candidate_since_ms) >=
              CONFIG_APP_KEY_DEBOUNCE_MS))
    {
        s_key_stable = s_key_candidate;
        if (s_key_stable == KEY_PRESSED)
        {
#if defined(CONFIG_BSP_USING_USART1)
            printf(">> KEY0 pressed.\r\n");
#endif
        }
    }
#endif
}
