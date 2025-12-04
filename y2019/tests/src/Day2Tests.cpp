#include "aoc/days/Day2.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace aoc2019;

TEST_CASE("Day 2, main test case", "[D2][MainTest]") {
    Day2 d{"test/day2.1.txt"};
    d.parse();

    SECTION("Parsing") {
        auto& comp = d.computer;
        REQUIRE(comp.source.size() == 12);
    }
}
