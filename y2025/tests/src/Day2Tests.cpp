#include "aoc/days/Day2.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Day 2, test case", "[D2][MainTest]") {
    aoc2025::Day2 d("test/day2.1.txt");
    d.parse();
    SECTION("Parse") {
        REQUIRE(d.ranges.size() == 11);
    }
    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 1227775554ll);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 4174379265ll);
    }
}

TEST_CASE("Day 2, test case 2", "[D2][Quick]") {
    aoc2025::Day2 d("test/day2.2.txt");
    d.parse();

    SECTION("Parse") {
        REQUIRE(d.ranges.size() == 1);
        REQUIRE(d.ranges.at(0).left == 95);
        REQUIRE(d.ranges.at(0).right == 115);
    }

    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 99); // Control
    }

    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 99 + 111);
    }


}
