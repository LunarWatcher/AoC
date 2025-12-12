# The bulk of the source files are separated into a library for them to be testable.
add_library(aoc2025src STATIC
    aoc/days/Day1.cpp
    aoc/days/Day2.cpp
    aoc/days/Day3.cpp
    aoc/days/Day4.cpp
    aoc/days/Day5.cpp
    aoc/days/Day6.cpp
    aoc/days/Day7.cpp
    aoc/days/Day8.cpp
    aoc/days/Day9.cpp
    aoc/days/Day10.cpp
    aoc/days/Day11.cpp
    aoc/days/Day12.cpp
)
add_executable(aoc-2025 aoc/Main.cpp)

target_compile_definitions(
    aoc-2025 PUBLIC AOC_YEAR=2025
)
target_include_directories(aoc2025src PUBLIC ./)
target_link_libraries(
    aoc2025src
PUBLIC
    aoc-common
)

target_link_libraries(aoc-2025 aoc2025src)
# vim:ft=cmake
