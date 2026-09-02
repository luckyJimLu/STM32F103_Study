# ==============================================================================
# middlewares/CMakeLists.txt - Middlewares, RTOS and Third-Party Libraries
# ==============================================================================

add_library(middlewares_lib STATIC)

# Provide a dummy translation unit so the library is never empty
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/middlewares_dummy.c"
    "/* Auto-generated dummy TU for middlewares_lib */\ntypedef int middlewares_dummy_t;\n")
target_sources(middlewares_lib PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/middlewares_dummy.c")

add_subdirectory(rtos)
add_subdirectory(third_party)

target_link_libraries(middlewares_lib PUBLIC
    rtos_lib
    third_party_lib
)
