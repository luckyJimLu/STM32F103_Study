# ==============================================================================
# third_party/letter_shell/CMakeLists.txt
# ==============================================================================

add_library(letter_shell_lib STATIC)

target_include_directories(letter_shell_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(GLOB LETTER_SHELL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

target_sources(letter_shell_lib PRIVATE
    ${LETTER_SHELL_SOURCES}
)
