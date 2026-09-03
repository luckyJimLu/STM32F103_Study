#include "bsp.h"

#include <stdio.h>

#include "product_config.h"
#include "system_mode.h"

HAL_StatusTypeDef BSP_Init(void)
{
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
    printf("\r\n========================================\r\n");
    printf(" Product : %s\r\n", PRODUCT_DISPLAY_NAME);
    printf(" System  : %s\r\n", SYSTEM_NAME_STRING);
    printf(" Clock   : %lu MHz\r\n",
           (unsigned long)(SystemCoreClock / 1000000U));
    printf("========================================\r\n");
#endif
    return HAL_OK;
}

void BSP_FatalError(const char *reason)
{
#if defined(CONFIG_BSP_USING_USART1)
    printf(">> [FATAL] %s\r\n", reason != NULL ? reason : "unknown error");
#else
    (void)reason;
#endif
    __disable_irq();
    for (;;)
    {
        __WFI();
    }
}
