#include <catch2/catch_test_macros.hpp>

#include <aoc/days/Day5.hpp>

using namespace aoc2025;

TEST_CASE("Day 5, main test case", "[D5][MainTest]") {
    Day5 d("test/day5.1.txt");
    d.parse();

    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 3);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 14);
    }
}
