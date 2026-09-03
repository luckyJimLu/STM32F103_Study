#include "bsp_key.h"

#include "product_config.h"
#include "stm32f1xx_hal.h"

#if !PRODUCT_HAS_KEY0
#error "BSP key driver enabled for a product without KEY0"
#endif

void BSP_KEY_Init(void)
{
    GPIO_InitTypeDef init = {0};
    PRODUCT_KEY0_GPIO_CLOCK();
    init.Pin = PRODUCT_KEY0_PIN;
    init.Mode = GPIO_MODE_INPUT;
    init.Pull = PRODUCT_KEY0_PULL;
    HAL_GPIO_Init(PRODUCT_KEY0_GPIO_PORT, &init);
}

Key_StateTypeDef BSP_KEY_GetState(void)
{
    return HAL_GPIO_ReadPin(PRODUCT_KEY0_GPIO_PORT, PRODUCT_KEY0_PIN) ==
                   PRODUCT_KEY0_ACTIVE_STATE
               ? KEY_PRESSED
               : KEY_RELEASED;
}
