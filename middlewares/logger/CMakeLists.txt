add_library(logger_lib STATIC src/logger.c)

target_include_directories(logger_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(logger_lib PUBLIC project_config)
