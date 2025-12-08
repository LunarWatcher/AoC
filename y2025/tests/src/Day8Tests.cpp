#include "aoc/days/Day8.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test 1", "[D8]") {
    aoc2025::Day8 d{"test/day8.1.txt", 10};
    d.parse();

    SECTION("Part 1") {
        REQUIRE(
            std::get<uint64_t>(d.part1()) == 40
        );
    }
    SECTION("Part 2") {
        REQUIRE(
            std::get<uint64_t>(d.part2()) == 25272
        );
    }
}
