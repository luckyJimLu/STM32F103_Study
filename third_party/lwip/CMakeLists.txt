# ==============================================================================
# third_party/lwip/CMakeLists.txt
# ==============================================================================

add_library(lwip_lib STATIC)

target_include_directories(lwip_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/arch
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

file(GLOB_RECURSE LWIP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/ipv4/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/api/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/netif/*.c"
)

target_sources(lwip_lib PRIVATE
    ${LWIP_SOURCES}
)
