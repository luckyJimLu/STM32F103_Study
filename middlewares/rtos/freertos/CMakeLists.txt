# ==============================================================================
# FreeRTOS CMakeLists.txt
# ==============================================================================

add_library(freertos_lib STATIC)

target_include_directories(freertos_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM3
)

file(GLOB_RECURSE FREERTOS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM3/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/portable/MemMang/heap_4.c"
)

target_sources(freertos_lib PRIVATE
    ${FREERTOS_SOURCES}
)

target_link_libraries(freertos_lib PUBLIC
    drivers_lib
    bsp_lib
)
