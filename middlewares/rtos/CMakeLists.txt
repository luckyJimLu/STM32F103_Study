add_library(rtos_lib INTERFACE)

if(SELECTED_RTOS STREQUAL "RTTHREAD")
    add_subdirectory(rt-thread)
    target_link_libraries(rtos_lib INTERFACE rtthread_lib)
elseif(SELECTED_RTOS STREQUAL "FREERTOS")
    add_subdirectory(freertos)
    target_link_libraries(rtos_lib INTERFACE freertos_lib)
endif()
