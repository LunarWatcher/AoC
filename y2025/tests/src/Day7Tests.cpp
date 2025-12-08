#include "aoc/days/Day7.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Day 7, main test", "[D7][MainTest]") {
    aoc2025::Day7 d{"test/day7.1.txt"};
    d.parse();

    SECTION("Part 1") {
        REQUIRE(
            std::get<uint64_t>(d.part1()) == 21
        );
    }
    SECTION("Part 2") {
        REQUIRE(
            std::get<uint64_t>(d.part2()) == 40
        );
    }
}
