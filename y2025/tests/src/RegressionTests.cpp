#include <catch2/catch_test_macros.hpp>

#include "aoc/days/Day1.hpp"
#include "aoc/days/Day2.hpp"
#include "aoc/days/Day3.hpp"
#include "aoc/days/Day4.hpp"
#include "aoc/days/Day5.hpp"
#include "aoc/days/Day6.hpp"

using namespace aoc2025;

TEST_CASE("Day 1 regression tests", "[Regression]") {
    Day1 d;
    d.parse();
    REQUIRE(d.part1() == 1048);
    REQUIRE(d.part2() == 6498);
}
TEST_CASE("Day 2 regression tests", "[Regression]") {
    Day2 d;
    d.parse();
    REQUIRE(d.part1() == 28846518423ull);
    REQUIRE(d.part2() == 31578210022ull);
}

TEST_CASE("Day 3 regression tests", "[Regression]") {
    Day3 d;
    d.parse();
    REQUIRE(d.part1() == 17535);
    REQUIRE(d.part2() == 173577199527257ull);
}

TEST_CASE("Day 4 regression tests", "[Regression]") {
    Day4 d;
    d.parse();
    REQUIRE(d.part1() == 1564);
    REQUIRE(d.part2() == 9401);
}

TEST_CASE("Day 5 regression tests", "[Regression]") {
    Day5 d;
    d.parse();
    REQUIRE(d.part1() == 811);
    REQUIRE(d.part2() == 338189277144473);
}

TEST_CASE("Day 6 regression tests", "[Regression]") {
    Day6 d;
    d.parse();
    REQUIRE(d.part1() == 5335495999141);
    REQUIRE(d.part2() == 10142723156431);
}
