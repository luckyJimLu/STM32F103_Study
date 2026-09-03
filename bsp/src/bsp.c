#include "bsp.h"

#include "logger.h"
#include "product_config.h"
#include "system_mode.h"

#if defined(CONFIG_LOG_ENABLE)
static void bsp_log_output(const char *data, uint16_t length)
{
    BSP_USART1_SendBuffer(data, length);
}

static const char *bsp_reset_reason(uint32_t reset_flags)
{
    if ((reset_flags & RCC_CSR_LPWRRSTF) != 0U)
    {
        return "low-power";
    }
    if ((reset_flags & RCC_CSR_WWDGRSTF) != 0U)
    {
        return "window-watchdog";
    }
    if ((reset_flags & RCC_CSR_IWDGRSTF) != 0U)
    {
        return "independent-watchdog";
    }
    if ((reset_flags & RCC_CSR_SFTRSTF) != 0U)
    {
        return "software";
    }
    if ((reset_flags & RCC_CSR_PORRSTF) != 0U)
    {
        return "power-on";
    }
    if ((reset_flags & RCC_CSR_PINRSTF) != 0U)
    {
        return "reset-pin";
    }
    return "unknown";
}
#endif

HAL_StatusTypeDef BSP_Init(void)
{
#if defined(CONFIG_LOG_ENABLE)
    const uint32_t reset_flags = RCC->CSR;
#endif

    if (HAL_Init() != HAL_OK)
    {
        return HAL_ERROR;
    }
    if (SystemClock_Config() != HAL_OK)
    {
        return HAL_ERROR;
    }
    if (SysTick_Config(SystemCoreClock / 1000U) != 0U)
    {
        return HAL_ERROR;
    }

#if defined(CONFIG_BSP_USING_LED)
    BSP_LED_Init();
#endif
#if defined(CONFIG_BSP_USING_KEY)
    BSP_KEY_Init();
#endif
#if defined(CONFIG_BSP_USING_USART1)
    if (BSP_USART1_Init(CONFIG_BSP_USART1_BAUDRATE) != HAL_OK)
    {
        return HAL_ERROR;
    }
#if defined(CONFIG_LOG_ENABLE)
    Logger_Init(bsp_log_output, HAL_GetTick);
    LOG_INFO("BOOT", "reset=%s flags=0x%08lX",
             bsp_reset_reason(reset_flags),
             (unsigned long)reset_flags);
    LOG_INFO("BOOT", "product=%s system=%s",
             PRODUCT_DISPLAY_NAME,
             SYSTEM_NAME_STRING);
    LOG_INFO("BOOT", "clock=%luHz flash=%luKB ram=%luKB",
             (unsigned long)SystemCoreClock,
             (unsigned long)(PRODUCT_FLASH_BYTES / 1024U),
             (unsigned long)(PRODUCT_RAM_BYTES / 1024U));
    LOG_INFO("UART", "%s tx=%s rx=%s baud=%u format=8N1",
             PRODUCT_CONSOLE_NAME_STRING,
             PRODUCT_CONSOLE_TX_STRING,
             PRODUCT_CONSOLE_RX_STRING,
             (unsigned int)CONFIG_BSP_USART1_BAUDRATE);
    LOG_INFO("LOGGER", "ready level=%u buffer=%u bytes",
             (unsigned int)CONFIG_LOG_LEVEL,
             (unsigned int)CONFIG_LOG_BUFFER_SIZE);
    RCC->CSR |= RCC_CSR_RMVF;
#endif
#endif

#if defined(CONFIG_BSP_USING_LED)
    LOG_INFO("BSP", "LED heartbeat output initialized");
#endif
#if defined(CONFIG_BSP_USING_KEY)
    LOG_INFO("BSP", "KEY0 input initialized with debounce support");
#endif
    return HAL_OK;
}

void BSP_FatalError(const char *reason)
{
#if defined(CONFIG_LOG_ENABLE)
    LOG_FATAL("SYSTEM", "%s", reason != NULL ? reason : "unknown error");
#else
    (void)reason;
#endif
    __disable_irq();
    for (;;)
    {
        __WFI();
    }
}
