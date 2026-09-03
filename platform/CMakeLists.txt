add_library(platform_lib STATIC src/main.c)
target_include_directories(platform_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(SELECTED_RTOS STREQUAL "RTTHREAD")
    target_sources(platform_lib PRIVATE src/system_runtime_rtthread.c)
elseif(SELECTED_RTOS STREQUAL "FREERTOS")
    target_sources(platform_lib PRIVATE src/system_runtime_freertos.c)
else()
    target_sources(platform_lib PRIVATE src/system_runtime_baremetal.c)
endif()

target_link_libraries(platform_lib PUBLIC
    app_lib
    bsp_lib
    rtos_lib
    project_config
)
