# ==============================================================================
# third_party/easylogger/CMakeLists.txt
# ==============================================================================

add_library(easylogger_lib STATIC)

target_include_directories(easylogger_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

file(GLOB_RECURSE ELOG_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/port/*.c"
)

target_sources(easylogger_lib PRIVATE
    ${ELOG_SOURCES}
)
