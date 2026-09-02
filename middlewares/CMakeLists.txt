# ==============================================================================
# middlewares/CMakeLists.txt - Middlewares, RTOS and Third-Party Libraries
# ==============================================================================

add_library(middlewares_lib STATIC)

add_subdirectory(rtos)
add_subdirectory(third_party)

target_link_libraries(middlewares_lib PUBLIC
    rtos_lib
    third_party_lib
)
