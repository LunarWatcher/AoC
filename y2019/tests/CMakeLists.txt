add_executable(tests-2019
    # Exists to allow for improvements without needing to manually check new answers.
    # This contains tests against the expected output on the real input.
    src/RegressionTests.cpp
)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.11.0
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(tests-2019 Catch2::Catch2WithMain)
target_link_libraries(tests-2019 aoc2019src)

# vim:ft=cmake
