# ==============================================================================
# third_party/segger_rtt/CMakeLists.txt
# ==============================================================================

add_library(segger_rtt_lib STATIC)

target_include_directories(segger_rtt_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(segger_rtt_lib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SEGGER_RTT.c
)
