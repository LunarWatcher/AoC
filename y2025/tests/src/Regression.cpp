#include <catch2/catch_test_macros.hpp>

#include "aoc/days/Day1.hpp"

TEST_CASE("Day 1 regression tests") {
    aoc2025::Day1 d;
    d.parse();
    REQUIRE(d.part1() == 1048);
    REQUIRE(d.part2() == 6498);
}
