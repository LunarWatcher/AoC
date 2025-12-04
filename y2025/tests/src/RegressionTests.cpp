#include <catch2/catch_test_macros.hpp>

#include "aoc/days/Day1.hpp"
#include "aoc/days/Day2.hpp"
#include "aoc/days/Day3.hpp"
#include "aoc/days/Day4.hpp"

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
