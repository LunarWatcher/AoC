add_library(
    aoc-common
STATIC
    src/common/Runner.cpp
)
target_include_directories(
    aoc-common
PUBLIC
    ./src/
)
target_link_libraries(
    aoc-common
PUBLIC
    stc::stc
)

add_subdirectory(tests)
