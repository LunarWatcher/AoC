add_executable(tests-2025
    src/Day1Tests.cpp
    src/Day2Tests.cpp
    src/Day3Tests.cpp
    src/Day4Tests.cpp
    src/Day5Tests.cpp
    src/Day6Tests.cpp
    src/Day7Tests.cpp
    src/Day8Tests.cpp
    src/Day9Tests.cpp
    src/Day10Tests.cpp
    src/Day11Tests.cpp

    # Exists to allow for improvements without needing to manually check new answers.
    # This contains tests against the expected output on the real input.
    src/RegressionTests.cpp
)

target_link_libraries(tests-2025 Catch2::Catch2WithMain)
target_link_libraries(tests-2025 aoc2025src)

# vim:ft=cmake
