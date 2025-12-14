add_executable(tests-common
    src/DisjointSetTests.cpp
    src/CappedBinarySearchListTests.cpp
    src/EqSystemTests.cpp
)

target_link_libraries(tests-common Catch2::Catch2WithMain)
target_link_libraries(tests-common aoc-common)

# vim:ft=cmake
