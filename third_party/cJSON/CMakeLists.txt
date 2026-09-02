# ==============================================================================
# third_party/cJSON/CMakeLists.txt
# ==============================================================================

add_library(cjson_lib STATIC)

target_include_directories(cjson_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(cjson_lib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/cJSON.c
)
