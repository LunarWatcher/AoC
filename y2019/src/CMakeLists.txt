add_library(aoc2019src STATIC
    aoc/days/Day1.cpp
    aoc/days/Day2.cpp
    aoc/days/Day3.cpp

    aoc/intcode/IntCode.cpp
)
add_executable(aoc-2019 aoc/Main.cpp)

target_include_directories(aoc2019src PUBLIC ./)
target_link_libraries(
    aoc2019src
PUBLIC
    aoc-common
)

target_link_libraries(aoc-2019 aoc2019src)
# vim:ft=cmake
