#include "bsp_led.h"

#include "product_config.h"
#include "stm32f1xx_hal.h"

void BSP_LED_Init(void)
{
    GPIO_InitTypeDef init = {0};
    PRODUCT_LED0_GPIO_CLOCK();
    init.Pin = PRODUCT_LED0_PIN;
    init.Mode = GPIO_MODE_OUTPUT_PP;
    init.Speed = PRODUCT_LED0_GPIO_SPEED;
    HAL_GPIO_Init(PRODUCT_LED0_GPIO_PORT, &init);
    BSP_LED_Off();
}

void BSP_LED_On(void)
{
    HAL_GPIO_WritePin(PRODUCT_LED0_GPIO_PORT,
                      PRODUCT_LED0_PIN,
                      PRODUCT_LED0_ACTIVE_STATE);
}

void BSP_LED_Off(void)
{
    HAL_GPIO_WritePin(PRODUCT_LED0_GPIO_PORT,
                      PRODUCT_LED0_PIN,
                      PRODUCT_LED0_INACTIVE_STATE);
}

void BSP_LED_Toggle(void)
{
    HAL_GPIO_TogglePin(PRODUCT_LED0_GPIO_PORT, PRODUCT_LED0_PIN);
}
