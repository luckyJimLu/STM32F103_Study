# ==============================================================================
# arm-none-eabi-gcc.cmake - Toolchain configuration for ARM GCC cross compilation
# ==============================================================================

set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

# Check if local toolchain exists in tools/toolchain/bin
set(LOCAL_TOOLCHAIN_DIR "${CMAKE_CURRENT_LIST_DIR}/../tools/toolchain/bin")
if(EXISTS "${LOCAL_TOOLCHAIN_DIR}")
    set(TOOLCHAIN_PATH_HINT "${LOCAL_TOOLCHAIN_DIR}/")
    message(STATUS ">> [Toolchain] Using local tools/toolchain/bin toolchain")
else()
    set(TOOLCHAIN_PATH_HINT "")
endif()

# Toolchain executables
set(TOOLCHAIN_PREFIX                arm-none-eabi-)

find_program(CMAKE_C_COMPILER       ${TOOLCHAIN_PATH_HINT}${TOOLCHAIN_PREFIX}gcc)
find_program(CMAKE_CXX_COMPILER     ${TOOLCHAIN_PATH_HINT}${TOOLCHAIN_PREFIX}g++)
find_program(CMAKE_ASM_COMPILER     ${TOOLCHAIN_PATH_HINT}${TOOLCHAIN_PREFIX}gcc)
find_program(CMAKE_AR               ${TOOLCHAIN_PATH_HINT}${TOOLCHAIN_PREFIX}ar)
find_program(CMAKE_OBJCOPY          ${TOOLCHAIN_PATH_HINT}${TOOLCHAIN_PREFIX}objcopy)
find_program(CMAKE_OBJDUMP          ${TOOLCHAIN_PATH_HINT}${TOOLCHAIN_PREFIX}objdump)
find_program(CMAKE_SIZE             ${TOOLCHAIN_PATH_HINT}${TOOLCHAIN_PREFIX}size)

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
