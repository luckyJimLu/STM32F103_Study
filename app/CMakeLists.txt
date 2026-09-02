# ==============================================================================
# app/CMakeLists.txt - Application Layer
# ==============================================================================

add_library(app_lib STATIC)

target_include_directories(app_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

file(GLOB_RECURSE APP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

target_sources(app_lib PRIVATE
    ${APP_SOURCES}
)

target_link_libraries(app_lib PUBLIC
    bsp_lib
    middlewares_lib
    drivers_lib
)
