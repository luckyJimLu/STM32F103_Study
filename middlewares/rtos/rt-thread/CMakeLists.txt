# ==============================================================================
# RT-Thread Nano CMakeLists.txt
# ==============================================================================

add_library(rtthread_lib STATIC)

target_include_directories(rtthread_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(RTT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/idle.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ipc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/irq.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kservice.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/object.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scheduler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/timer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcpu/arm/cortex-m3/cpuport.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libcpu/arm/cortex-m3/context_gcc.S
)

target_sources(rtthread_lib PRIVATE
    ${RTT_SOURCES}
)

target_link_libraries(rtthread_lib PUBLIC
    drivers_lib
    project_config
)
