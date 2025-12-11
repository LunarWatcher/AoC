#include "aoc/days/Day11.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test 1", "[Day11]") {
    aoc2025::Day11 d{"test/day11.1.txt"};
    d.parse();

    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 5);
    }
}

TEST_CASE("Test 2", "[Day11]") {
    aoc2025::Day11 d{"test/day11.2.txt"};
    d.parse();

    // SECTION("Part 2") {
    //     REQUIRE(std::get<uint64_t>(d.part2()) == 2);
    // }
}
