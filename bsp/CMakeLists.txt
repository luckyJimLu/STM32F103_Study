add_library(bsp_lib STATIC src/bsp.c)

if(CONFIG_BSP_USING_LED)
    target_sources(bsp_lib PRIVATE src/bsp_led.c)
endif()
if(CONFIG_BSP_USING_KEY)
    target_sources(bsp_lib PRIVATE src/bsp_key.c)
endif()
if(CONFIG_BSP_USING_USART1)
    target_sources(bsp_lib PRIVATE src/bsp_usart.c)
endif()

target_include_directories(bsp_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(bsp_lib PUBLIC drivers_lib project_config)
