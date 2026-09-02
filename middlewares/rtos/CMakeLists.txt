# ==============================================================================
# middlewares/rtos/CMakeLists.txt - RTOS Selection Management
# ==============================================================================

add_library(rtos_lib STATIC)
target_sources(rtos_lib PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/rtos_none.c")

if(USE_RTOS STREQUAL "RTTHREAD")
    add_subdirectory(rt-thread)
    target_link_libraries(rtos_lib PUBLIC rtthread_lib)
    message(STATUS ">> Middleware: Linked RT-Thread library")
elseif(USE_RTOS STREQUAL "FREERTOS")
    add_subdirectory(freertos)
    target_link_libraries(rtos_lib PUBLIC freertos_lib)
    message(STATUS ">> Middleware: Linked FreeRTOS library")
else()
    message(STATUS ">> Middleware: Baremetal mode (No RTOS linked)")
endif()
