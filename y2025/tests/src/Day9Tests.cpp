#include <catch2/catch_test_macros.hpp>

#include <aoc/days/Day9.hpp>

TEST_CASE("Test 1", "[Day9]") {
    aoc2025::Day9 d{"test/day9.1.txt"};
    d.parse();

    SECTION("Part 1") {
        REQUIRE(
            std::get<uint64_t>(d.part1()) == 50
        );
    }
    SECTION("Part 2") {
        REQUIRE(
            std::get<uint64_t>(d.part2()) == 24
        );
    }
}
