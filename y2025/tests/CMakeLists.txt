add_executable(tests-2025
    src/Day1Tests.cpp
    src/Day2Tests.cpp
    src/Day3Tests.cpp
    src/Day4Tests.cpp
    src/Day5Tests.cpp

    # Exists to allow for improvements without needing to manually check new answers.
    # This contains tests against the expected output on the real input.
    src/RegressionTests.cpp
)

target_link_libraries(tests-2025 Catch2::Catch2WithMain)
target_link_libraries(tests-2025 aoc2025src)

# vim:ft=cmake
