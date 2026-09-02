# ==============================================================================
# RT-Thread Nano CMakeLists.txt
# ==============================================================================

add_library(rtthread_lib STATIC)

target_include_directories(rtthread_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/components/finsh
)

file(GLOB_RECURSE RTT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/libcpu/arm/cortex-m3/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/libcpu/arm/cortex-m3/*.S"
    "${CMAKE_CURRENT_SOURCE_DIR}/board.c"
)

target_sources(rtthread_lib PRIVATE
    ${RTT_SOURCES}
)

target_link_libraries(rtthread_lib PUBLIC
    drivers_lib
    bsp_lib
)
