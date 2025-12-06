#include "aoc/days/Day6.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Day 6, main test", "[D6][MainTest]") {
    aoc2025::Day6 d("test/day6.1.txt");
    d.parse();

    SECTION("Parsing") {
        REQUIRE(d.input.lines.size() == 3);
        REQUIRE(d.input.ops.size() == 4);
    }

    SECTION("Part 1") {
        REQUIRE(d.part1() == 4277556);
    }
    SECTION("Part 2") {
        REQUIRE(d.part2() == 3263827);
    }
}
