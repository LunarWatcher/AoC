add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(run-2019
    COMMAND aoc-2019
    DEPENDS aoc-2019
    COMMENT "Run AoC (2019)")
add_custom_target(test-2019
    COMMAND tests-2019
    DEPENDS tests-2019
    COMMENT "Test AoC (2019)")
