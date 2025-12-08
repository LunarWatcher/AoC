add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(run-2025
    COMMAND aoc-2025
    DEPENDS aoc-2025
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    COMMENT "Run AoC (2025)")
add_custom_target(test-2025
    COMMAND tests-2025
    DEPENDS tests-2025
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    COMMENT "Test AoC (2025)")
