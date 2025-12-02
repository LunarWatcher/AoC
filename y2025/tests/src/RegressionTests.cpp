#include <catch2/catch_test_macros.hpp>

#include "aoc/days/Day1.hpp"
#include "aoc/days/Day2.hpp"

using namespace aoc2025;

TEST_CASE("Day 1 regression tests") {
    Day1 d;
    d.parse();
    REQUIRE(d.part1() == 1048);
    REQUIRE(d.part2() == 6498);
}
TEST_CASE("Day 2 regression tests") {
    Day2 d;
    d.parse();
    REQUIRE(d.part1() == 28846518423ull);
    REQUIRE(d.part2() == 31578210022ull);
}
