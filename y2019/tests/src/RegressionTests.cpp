#include <catch2/catch_test_macros.hpp>

#include "aoc/days/Day1.hpp"
#include "aoc/days/Day2.hpp"
#include "aoc/days/Day3.hpp"

using namespace aoc2019;

TEST_CASE("Day 1", "[Regression]") {
    Day1 d;
    d.parse();
    REQUIRE(d.part1() == 3159380);
    REQUIRE(d.part2() == 4736213);
}

TEST_CASE("Day 2", "[Regression]") {
    Day2 d;
    d.parse();
    REQUIRE(d.computer.source.size() == 117);
    REQUIRE(d.part1() == 4570637);
    REQUIRE(d.part2() == 5485);
}

TEST_CASE("Day 3", "[Regression]") {
    Day3 d;
    d.parse();
    REQUIRE(d.part1() == 2129);
    REQUIRE(d.part2() == 134662);
}
