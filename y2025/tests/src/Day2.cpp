#include "aoc/days/Day2.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Day 2, test case", "[D2]") {
    aoc2025::Day2 d("test/day2.1.txt");
    d.parse();
    SECTION("Parse") {
        REQUIRE(d.ranges.size() == 11);
    }
    SECTION("Part 1") {
        REQUIRE(d.part1() == 1227775554ll);
    }
}
