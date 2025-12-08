#include "aoc/days/Day6.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Day 6, main test", "[D6][MainTest]") {
    aoc2025::Day6 d("test/day6.1.txt");
    d.parse();

    SECTION("Parsing") {
        REQUIRE(d.input.size() == 4);
        REQUIRE(d.input.at(0).nums.size() == 3);
    }

    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 4277556);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 3263827);
    }
}
