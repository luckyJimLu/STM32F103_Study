# ==============================================================================
# bsp/CMakeLists.txt - Board Support Package Layer
# ==============================================================================

add_library(bsp_lib STATIC)

target_include_directories(bsp_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

file(GLOB_RECURSE BSP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

target_sources(bsp_lib PRIVATE
    ${BSP_SOURCES}
)

target_link_libraries(bsp_lib PUBLIC
    drivers_lib
)
