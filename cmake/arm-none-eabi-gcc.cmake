# ==============================================================================
# arm-none-eabi-gcc.cmake - Toolchain configuration for ARM GCC cross compilation
# ==============================================================================

set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

# Use the repository-local toolchain so no system installation or PATH change is needed.
get_filename_component(LOCAL_TOOLCHAIN_DIR
    "${CMAKE_CURRENT_LIST_DIR}/../tools/toolchain/bin" ABSOLUTE)

if(WIN32)
    set(TOOLCHAIN_EXECUTABLE_SUFFIX ".exe")
else()
    set(TOOLCHAIN_EXECUTABLE_SUFFIX "")
endif()

set(TOOLCHAIN_PREFIX "${LOCAL_TOOLCHAIN_DIR}/arm-none-eabi-")
set(TOOLCHAIN_GCC "${TOOLCHAIN_PREFIX}gcc${TOOLCHAIN_EXECUTABLE_SUFFIX}")

if(NOT EXISTS "${TOOLCHAIN_GCC}")
    message(FATAL_ERROR
        "GNU Arm toolchain not found at: ${TOOLCHAIN_GCC}\n"
        "Extract it so tools/toolchain/bin/arm-none-eabi-gcc exists.")
endif()

message(STATUS ">> [Toolchain] Using repository-local tools/toolchain/bin")

set(CMAKE_C_COMPILER   "${TOOLCHAIN_PREFIX}gcc${TOOLCHAIN_EXECUTABLE_SUFFIX}" CACHE FILEPATH "C compiler")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++${TOOLCHAIN_EXECUTABLE_SUFFIX}" CACHE FILEPATH "C++ compiler")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PREFIX}gcc${TOOLCHAIN_EXECUTABLE_SUFFIX}" CACHE FILEPATH "ASM compiler")
set(CMAKE_AR           "${TOOLCHAIN_PREFIX}ar${TOOLCHAIN_EXECUTABLE_SUFFIX}" CACHE FILEPATH "Archiver")
set(CMAKE_OBJCOPY      "${TOOLCHAIN_PREFIX}objcopy${TOOLCHAIN_EXECUTABLE_SUFFIX}" CACHE FILEPATH "Objcopy")
set(CMAKE_OBJDUMP      "${TOOLCHAIN_PREFIX}objdump${TOOLCHAIN_EXECUTABLE_SUFFIX}" CACHE FILEPATH "Objdump")
set(CMAKE_SIZE         "${TOOLCHAIN_PREFIX}size${TOOLCHAIN_EXECUTABLE_SUFFIX}" CACHE FILEPATH "Size tool")
set(CMAKE_NM           "${TOOLCHAIN_PREFIX}nm${TOOLCHAIN_EXECUTABLE_SUFFIX}" CACHE FILEPATH "NM tool")

set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)

# Architecture flags for Cortex-M3 (STM32F103)
set(ARM_ARCH_FLAGS                  "-mcpu=cortex-m3 -mthumb")

# Common compiler flags
set(COMMON_FLAGS                    "${ARM_ARCH_FLAGS} -fdata-sections -ffunction-sections -Wall -fstack-usage")

set(CMAKE_C_FLAGS                   "${COMMON_FLAGS} -std=gnu11" CACHE INTERNAL "C Compiler options")
set(CMAKE_CXX_FLAGS                 "${COMMON_FLAGS} -std=gnu++14 -fno-exceptions -fno-rtti" CACHE INTERNAL "C++ Compiler options")
set(CMAKE_ASM_FLAGS                 "${COMMON_FLAGS} -x assembler-with-cpp" CACHE INTERNAL "ASM Compiler options")

# Optimization flags for Debug / Release
set(CMAKE_C_FLAGS_DEBUG             "-O0 -g3 -DDEBUG" CACHE INTERNAL "C Debug options")
set(CMAKE_CXX_FLAGS_DEBUG           "-O0 -g3 -DDEBUG" CACHE INTERNAL "C++ Debug options")
set(CMAKE_ASM_FLAGS_DEBUG           "-g3" CACHE INTERNAL "ASM Debug options")

set(CMAKE_C_FLAGS_RELEASE           "-Os -DNDEBUG" CACHE INTERNAL "C Release options")
set(CMAKE_CXX_FLAGS_RELEASE         "-Os -DNDEBUG" CACHE INTERNAL "C++ Release options")
set(CMAKE_ASM_FLAGS_RELEASE         "" CACHE INTERNAL "ASM Release options")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS          "${ARM_ARCH_FLAGS} -Wl,--gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map" CACHE INTERNAL "Linker options")
