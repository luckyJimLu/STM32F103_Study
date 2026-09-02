cmake_minimum_required(VERSION 3.20)

# Load toolchain if not specified in command line
if(NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-none-eabi-gcc.cmake")
endif()

project(STM32F103_Study C CXX ASM)

# Include modules and options
include(cmake/stm32f103_options.cmake)
include(cmake/post_build.cmake)

# Global include directory for Kconfig autoconf.h
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/build/generated)

# Define Main Target Executable
set(TARGET_ELF ${PROJECT_NAME}.elf)
add_executable(${TARGET_ELF} ${STARTUP_ASM})

# Set Linker flags for target
target_link_options(${TARGET_ELF} PRIVATE
    -T${LINKER_SCRIPT}
)

# Add subdirectories
add_subdirectory(drivers)
add_subdirectory(bsp)
add_subdirectory(middlewares)
add_subdirectory(third_party)
add_subdirectory(app)

# Link all components to target executable
target_link_libraries(${TARGET_ELF} PRIVATE
    app_lib
    bsp_lib
    middlewares_lib
    third_party_lib
    drivers_lib
)

# Generate hex, bin, and display size after build
stm32_add_post_build_commands(${TARGET_ELF})
