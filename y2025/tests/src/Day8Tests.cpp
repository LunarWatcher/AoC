#include "aoc/days/Day8.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test 1", "[D8]") {
    aoc2025::Day8 d{"test/day8.1.txt"};
    d.parse();

    SECTION("Part 1") {
        REQUIRE(
            d.part1() == 40
        );
    }

}
