#include "aoc/days/Day4.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace aoc2025;

TEST_CASE("Day 4, main test", "[D4][MainTest]") {
    Day4 d{"test/day4.1.txt"};
    d.parse();
    SECTION("Parsing") {
        REQUIRE(d.map.size() == 10);
    }
    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 13);
    }
}
