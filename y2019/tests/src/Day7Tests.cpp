#include <catch2/catch_test_macros.hpp>

#include <aoc/days/Day7.hpp>

TEST_CASE("Day 7 test case 1") {
    aoc2019::Day7 d("test/day7.1.txt");
    d.parse();

    SECTION("Part 2") {
        REQUIRE(d.part2() == 139629729);
    }
}
