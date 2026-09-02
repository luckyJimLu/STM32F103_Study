# ==============================================================================
# post_build.cmake - Post-build targets for generating HEX, BIN and memory usage
# ==============================================================================

function(stm32_add_post_build_commands TARGET_NAME)
    get_filename_component(OUTPUT_BASENAME "${TARGET_NAME}" NAME_WE)

    # Generate .hex file
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_BINARY_DIR}/${OUTPUT_BASENAME}.hex
        COMMENT ">> Generating Intel HEX: ${PROJECT_BINARY_DIR}/${OUTPUT_BASENAME}.hex"
    )

    # Generate .bin file
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${TARGET_NAME}> ${PROJECT_BINARY_DIR}/${OUTPUT_BASENAME}.bin
        COMMENT ">> Generating Raw Binary: ${PROJECT_BINARY_DIR}/${OUTPUT_BASENAME}.bin"
    )

    # Print memory footprint
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_SIZE} --format=berkeley $<TARGET_FILE:${TARGET_NAME}>
        COMMENT ">> Output Memory Footprint (Berkeley Size):"
    )
endfunction()
