add_executable(tests-2019
    src/Day1Tests.cpp
    src/Day2Tests.cpp

    src/IntCodeTests.cpp

    # Exists to allow for improvements without needing to manually check new answers.
    # This contains tests against the expected output on the real input.
    src/RegressionTests.cpp
)

target_link_libraries(tests-2019 Catch2::Catch2WithMain)
target_link_libraries(tests-2019 aoc2019src)

# vim:ft=cmake
