#include "aoc/days/Day6.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Day 6 test case 1", "[D6]") {
    aoc2019::Day6 d("test/day6.1.txt");
    d.parse();

    SECTION("Parsing") {
        REQUIRE(d.orbits.size() == 9);
    }

    SECTION("Part 1") {
        REQUIRE(d.part1() == 54);
    }

    SECTION("Part 2") {
        REQUIRE(d.part2() == 4);
    }
}
