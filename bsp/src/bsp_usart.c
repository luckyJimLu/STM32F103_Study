#include "bsp_usart.h"

#include "product_config.h"

static UART_HandleTypeDef s_console_uart;

HAL_StatusTypeDef BSP_USART1_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef init = {0};
    PRODUCT_CONSOLE_GPIO_CLOCK();
    PRODUCT_CONSOLE_UART_CLOCK();

    init.Pin = PRODUCT_CONSOLE_TX_PIN;
    init.Mode = GPIO_MODE_AF_PP;
    init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PRODUCT_CONSOLE_GPIO_PORT, &init);

    init.Pin = PRODUCT_CONSOLE_RX_PIN;
    init.Mode = GPIO_MODE_INPUT;
    init.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PRODUCT_CONSOLE_GPIO_PORT, &init);

    s_console_uart.Instance = PRODUCT_CONSOLE_UART;
    s_console_uart.Init.BaudRate = baudrate;
    s_console_uart.Init.WordLength = UART_WORDLENGTH_8B;
    s_console_uart.Init.StopBits = UART_STOPBITS_1;
    s_console_uart.Init.Parity = UART_PARITY_NONE;
    s_console_uart.Init.Mode = UART_MODE_TX_RX;
    s_console_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    return HAL_UART_Init(&s_console_uart);
}

void BSP_USART1_SendChar(char ch)
{
    (void)HAL_UART_Transmit(&s_console_uart, (const uint8_t *)&ch, 1, 1000);
}

void BSP_USART1_SendString(const char *str)
{
    while ((str != NULL) && (*str != '\0'))
    {
        BSP_USART1_SendChar(*str++);
    }
}

int _write(int file, char *ptr, int len)
{
    (void)file;
    (void)HAL_UART_Transmit(&s_console_uart,
                            (const uint8_t *)ptr,
                            (uint16_t)len,
                            1000);
    return len;
}

int fputc(int ch, FILE *stream)
{
    (void)stream;
    BSP_USART1_SendChar((char)ch);
    return ch;
}
