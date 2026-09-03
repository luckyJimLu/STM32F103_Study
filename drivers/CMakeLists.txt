add_library(drivers_lib STATIC
    STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
)

if(CONFIG_DRIVER_HAL_RCC)
    target_sources(drivers_lib PRIVATE STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c)
endif()
if(CONFIG_DRIVER_HAL_GPIO)
    target_sources(drivers_lib PRIVATE STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c)
endif()
if(CONFIG_DRIVER_HAL_UART)
    target_sources(drivers_lib PRIVATE STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c)
endif()

target_include_directories(drivers_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Core/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F1xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Inc
)
target_link_libraries(drivers_lib PUBLIC project_config)
