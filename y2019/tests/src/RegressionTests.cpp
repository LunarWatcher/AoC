#include <catch2/catch_test_macros.hpp>

#include "aoc/days/Day1.hpp"

using namespace aoc2019;

TEST_CASE("Day 1") {
    Day1 d;
    d.parse();
    REQUIRE(d.part1() == 3159380);
    REQUIRE(d.part2() == 4736213);
}

