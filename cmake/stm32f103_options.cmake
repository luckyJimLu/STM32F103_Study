# ==============================================================================
# stm32f103_options.cmake - Project Configuration Macros & Kconfig Integration
# ==============================================================================

# 1. Load Kconfig generated options if available
if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/kconfig.cmake")
    include("${CMAKE_SOURCE_DIR}/cmake/kconfig.cmake")
    message(STATUS ">> [Kconfig] Loaded configuration from cmake/kconfig.cmake")
endif()

# 2. Chip Model selection. An explicit preset/-D value takes precedence over Kconfig.
if(NOT DEFINED CHIP_TYPE OR CHIP_TYPE STREQUAL "")
    if(CONFIG_CHIP_STM32F103ZE)
        set(CHIP_TYPE "STM32F103xE" CACHE STRING "Target STM32F103 family")
    elseif(CONFIG_CHIP_STM32F103CB)
        set(CHIP_TYPE "STM32F103xB" CACHE STRING "Target STM32F103 family")
    else()
        set(CHIP_TYPE "STM32F103xB" CACHE STRING "Target STM32F103 family")
    endif()
endif()

# 3. RTOS selection. An explicit preset/-D value takes precedence over Kconfig.
if(NOT DEFINED USE_RTOS OR USE_RTOS STREQUAL "")
    if(CONFIG_RTOS_RTTHREAD)
        set(USE_RTOS "RTTHREAD" CACHE STRING "Select RTOS")
    elseif(CONFIG_RTOS_FREERTOS)
        set(USE_RTOS "FREERTOS" CACHE STRING "Select RTOS")
    else()
        set(USE_RTOS "NONE" CACHE STRING "Select RTOS")
    endif()
endif()

# 4. Third-party options from Kconfig
if(CONFIG_USING_CJSON)
    set(ENABLE_CJSON ON CACHE INTERNAL "cJSON")
endif()
if(CONFIG_USING_SEGGER_RTT)
    set(ENABLE_SEGGER_RTT ON CACHE INTERNAL "SEGGER RTT")
endif()

# Export definitions to compiler
add_compile_definitions(${CHIP_TYPE})
add_compile_definitions(USE_HAL_DRIVER)

if(USE_RTOS STREQUAL "RTTHREAD")
    add_compile_definitions(RT_USING_NANO)
    add_compile_definitions(CONFIG_USE_RTTHREAD=1)
    message(STATUS ">> [RTOS Mode] Enabled RT-Thread Nano")
elseif(USE_RTOS STREQUAL "FREERTOS")
    add_compile_definitions(CONFIG_USE_FREERTOS=1)
    message(STATUS ">> [RTOS Mode] Enabled FreeRTOS")
else()
    add_compile_definitions(CONFIG_USE_BAREMETAL=1)
    message(STATUS ">> [RTOS Mode] Enabled Bare-metal")
endif()

# Select Linker script and Startup ASM
if(CHIP_TYPE STREQUAL "STM32F103xB")
    set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/linker/STM32F103C8Tx_FLASH.ld")
    set(STARTUP_ASM   "${CMAKE_SOURCE_DIR}/drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xb.s")
elseif(CHIP_TYPE STREQUAL "STM32F103xE")
    set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/linker/STM32F103ZETx_FLASH.ld")
    set(STARTUP_ASM   "${CMAKE_SOURCE_DIR}/drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xe.s")
endif()

message(STATUS ">> [Chip Type] ${CHIP_TYPE}")
message(STATUS ">> [Linker Script] ${LINKER_SCRIPT}")
