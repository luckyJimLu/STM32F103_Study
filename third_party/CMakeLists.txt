# ==============================================================================
# third_party/CMakeLists.txt - Top-level Third-Party Components
# ==============================================================================

add_library(third_party_lib STATIC)

# Base dummy source so the library can always link
target_sources(third_party_lib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/dummy_third_party.c"
)

# Subcomponents
if(CONFIG_USING_CJSON)
    add_subdirectory(cJSON)
    target_link_libraries(third_party_lib PUBLIC cjson_lib)
    message(STATUS ">> [ThirdParty] Linked cJSON")
endif()

if(CONFIG_USING_LWIP)
    add_subdirectory(lwip)
    target_link_libraries(third_party_lib PUBLIC lwip_lib)
    message(STATUS ">> [ThirdParty] Linked LwIP")
endif()

if(CONFIG_USING_SEGGER_RTT)
    add_subdirectory(segger_rtt)
    target_link_libraries(third_party_lib PUBLIC segger_rtt_lib)
    message(STATUS ">> [ThirdParty] Linked SEGGER RTT")
endif()

if(CONFIG_USING_EASYLOGGER)
    add_subdirectory(easylogger)
    target_link_libraries(third_party_lib PUBLIC easylogger_lib)
    message(STATUS ">> [ThirdParty] Linked EasyLogger")
endif()

if(CONFIG_USING_LETTER_SHELL)
    add_subdirectory(letter_shell)
    target_link_libraries(third_party_lib PUBLIC letter_shell_lib)
    message(STATUS ">> [ThirdParty] Linked Letter Shell")
endif()
