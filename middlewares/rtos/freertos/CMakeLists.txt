# ==============================================================================
# middlewares/rtos/freertos/CMakeLists.txt
# FreeRTOS V202112.00 — GCC ARM_CM3 port
# ==============================================================================

add_library(freertos_lib STATIC)

# --------------------------------------------------------------------------
# Include directories
# --------------------------------------------------------------------------
target_include_directories(freertos_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}                      # FreeRTOSConfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include              # FreeRTOS kernel headers
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM3 # portmacro.h
)

# --------------------------------------------------------------------------
# Kernel source files
# --------------------------------------------------------------------------
set(FREERTOS_KERNEL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stream_buffer.c
)

# --------------------------------------------------------------------------
# Portable layer — GCC Cortex-M3
# --------------------------------------------------------------------------
set(FREERTOS_PORT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM3/port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/MemMang/heap_4.c   # heap_4: best fit, coalescing
)

target_sources(freertos_lib PRIVATE
    ${FREERTOS_KERNEL_SOURCES}
    ${FREERTOS_PORT_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/freertos_hooks.c
)


# --------------------------------------------------------------------------
# Link against drivers for SystemCoreClock and HAL
# --------------------------------------------------------------------------
target_link_libraries(freertos_lib PUBLIC
    drivers_lib
    bsp_lib
)
