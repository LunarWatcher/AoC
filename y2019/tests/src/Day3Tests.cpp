#include "aoc/days/Day3.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Day 3, test case 1", "[D3]") {
    aoc2019::Day3 d{"test/day3.1.txt"};
    d.parse();

    SECTION("Parse") {
        REQUIRE(d.wires.size() == 2);

        REQUIRE(d.wires.at(0).size() == 4);
        REQUIRE(d.wires.at(1).size() == 4);
    }

    SECTION("Part 1") {
        REQUIRE(d.part1() == 6);
    }

    SECTION("Part 2") {
        REQUIRE(d.part2() == 30);
    }
}

TEST_CASE("Day 3, test case 2", "[D3]") {
    aoc2019::Day3 d{"test/day3.2.txt"};
    d.parse();

    SECTION("Parse") {
        REQUIRE(d.wires.size() == 2);

        REQUIRE(d.wires.at(0).size() == 9);
        REQUIRE(d.wires.at(1).size() == 8);
    }

    SECTION("Part 1") {
        REQUIRE(d.part1() == 159);
    }

    SECTION("Part 2") {
        REQUIRE(d.part2() == 610);
    }
}
