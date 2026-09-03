# Resolve and generate one immutable configuration per CMake build directory.
if(NOT DEFINED PROJECT_CONFIG_FILE OR PROJECT_CONFIG_FILE STREQUAL "")
    set(PROJECT_CONFIG_FILE "${CMAKE_SOURCE_DIR}/.config" CACHE FILEPATH
        "Kconfig file used by this build")
endif()

if(NOT IS_ABSOLUTE "${PROJECT_CONFIG_FILE}")
    get_filename_component(PROJECT_CONFIG_FILE
        "${PROJECT_CONFIG_FILE}" ABSOLUTE BASE_DIR "${CMAKE_SOURCE_DIR}")
endif()

if(NOT EXISTS "${PROJECT_CONFIG_FILE}")
    if(PROJECT_CONFIG_FILE STREQUAL "${CMAKE_SOURCE_DIR}/.config")
        set(PROJECT_CONFIG_FILE
            "${CMAKE_SOURCE_DIR}/product/bluepill_f103c8/configs/baremetal_defconfig")
        message(STATUS ">> [Kconfig] .config not found; using BluePill bare-metal default")
    else()
        message(FATAL_ERROR "Kconfig file does not exist: ${PROJECT_CONFIG_FILE}")
    endif()
endif()

set(PROJECT_GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${PROJECT_GENERATED_DIR}")
execute_process(
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/scripts/menuconfig.py"
            --sync --config "${PROJECT_CONFIG_FILE}"
            --output-dir "${PROJECT_GENERATED_DIR}"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RESULT_VARIABLE KCONFIG_RESULT
    OUTPUT_VARIABLE KCONFIG_OUTPUT
    ERROR_VARIABLE KCONFIG_ERROR
)
if(NOT KCONFIG_RESULT EQUAL 0)
    message(FATAL_ERROR
        "Kconfig generation failed for ${PROJECT_CONFIG_FILE}:\n${KCONFIG_OUTPUT}${KCONFIG_ERROR}")
endif()
include("${PROJECT_GENERATED_DIR}/kconfig.cmake")

if(CONFIG_PRODUCT_BLUEPILL_F103C8)
    include("${CMAKE_SOURCE_DIR}/product/bluepill_f103c8/product.cmake")
elseif(CONFIG_PRODUCT_ATK_ELITE_F103ZE)
    include("${CMAKE_SOURCE_DIR}/product/atk_elite_f103ze/product.cmake")
else()
    message(FATAL_ERROR "Exactly one supported product must be selected")
endif()

if(CONFIG_RTOS_NONE)
    set(SELECTED_RTOS "BAREMETAL")
elseif(CONFIG_RTOS_RTTHREAD)
    set(SELECTED_RTOS "RTTHREAD")
elseif(CONFIG_RTOS_FREERTOS)
    set(SELECTED_RTOS "FREERTOS")
else()
    message(FATAL_ERROR "Exactly one operating system must be selected")
endif()

set(PRODUCT_LINKER_SCRIPT "${PROJECT_GENERATED_DIR}/${PRODUCT_ID}.ld")
configure_file(
    "${CMAKE_SOURCE_DIR}/product/linker.ld.in"
    "${PRODUCT_LINKER_SCRIPT}"
    @ONLY
)

message(STATUS ">> [Config] ${PROJECT_CONFIG_FILE}")
message(STATUS ">> [Product] ${PRODUCT_DISPLAY_NAME}")
message(STATUS ">> [System] ${SELECTED_RTOS}")
message(STATUS ">> [Linker] ${PRODUCT_LINKER_SCRIPT}")
