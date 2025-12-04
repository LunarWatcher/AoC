#include <catch2/catch_test_macros.hpp>
#include <aoc/days/Day1.hpp>

using namespace aoc2019;

TEST_CASE("Day 1, main test case", "[D1][MainTest]") {
    Day1 d("test/day1.1.txt");
    d.parse();

    SECTION("Parse") {
        REQUIRE(d.masses.size() == 4);
    }
    SECTION("Part 1") {
        REQUIRE(d.part1() == 2 + 2 + 654 + 33583);
    }
}
