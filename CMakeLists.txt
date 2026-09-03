cmake_minimum_required(VERSION 3.20)

if(NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-none-eabi-gcc.cmake")
endif()

project(STM32F103_Study C ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
include(cmake/stm32f103_options.cmake)
include(cmake/post_build.cmake)

add_library(project_config INTERFACE)
target_include_directories(project_config INTERFACE
    "${PROJECT_GENERATED_DIR}"
    "${PRODUCT_INCLUDE_DIR}"
    "${CMAKE_SOURCE_DIR}/platform/include"
)
target_compile_definitions(project_config INTERFACE
    ${PRODUCT_MCU_DEFINE}
    USE_HAL_DRIVER
)

add_subdirectory(drivers)
add_subdirectory(bsp)
add_subdirectory(app)
add_subdirectory(middlewares)
add_subdirectory(platform)

set(TARGET_ELF "${PROJECT_NAME}.elf")
add_executable(${TARGET_ELF} "${PRODUCT_STARTUP_ASM}")
set_target_properties(${TARGET_ELF} PROPERTIES LINKER_LANGUAGE C)
target_link_options(${TARGET_ELF} PRIVATE "-T${PRODUCT_LINKER_SCRIPT}")
target_link_libraries(${TARGET_ELF} PRIVATE platform_lib)

stm32_add_post_build_commands(${TARGET_ELF})
