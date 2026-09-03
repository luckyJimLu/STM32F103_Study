add_library(app_lib STATIC src/app_task.c)
target_include_directories(app_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(app_lib PUBLIC bsp_lib project_config)
