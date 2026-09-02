# ==============================================================================
# drivers/CMakeLists.txt - CMSIS & STM32F1xx HAL Drivers
# ==============================================================================

add_library(drivers_lib STATIC)

target_include_directories(drivers_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Core/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F1xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Inc/Legacy
)

# Collect HAL Driver Sources
file(GLOB_RECURSE HAL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/*.c"
)

# CMSIS System Initialization Source
set(CMSIS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c"
)

target_sources(drivers_lib PRIVATE
    ${HAL_SOURCES}
    ${CMSIS_SOURCES}
)
