# ==============================================================================
# middlewares/third_party/CMakeLists.txt - Third Party Libraries
# ==============================================================================

add_library(third_party_lib STATIC)

# Third party sources list
set(THIRD_PARTY_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/dummy_third_party.c")

if(ENABLE_CJSON)
    target_include_directories(third_party_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cJSON)
    list(APPEND THIRD_PARTY_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/cJSON/cJSON.c)
    message(STATUS ">> ThirdParty: Enabled cJSON")
endif()

if(ENABLE_SEGGER_RTT)
    target_include_directories(third_party_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SEGGER_RTT)
    file(GLOB RTT_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/SEGGER_RTT/*.c")
    list(APPEND THIRD_PARTY_SRCS ${RTT_SRCS})
    message(STATUS ">> ThirdParty: Enabled SEGGER RTT")
endif()

target_sources(third_party_lib PRIVATE
    ${THIRD_PARTY_SRCS}
)
