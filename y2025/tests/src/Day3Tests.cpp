#include <catch2/catch_test_macros.hpp>

#include <aoc/days/Day3.hpp>

using namespace aoc2025;

TEST_CASE("Day 3", "[D3][MainTest]") {
    Day3 d("test/day3.1.txt");
    d.parse();
    SECTION("Parsing") {
        REQUIRE(d.banks.size() == 4);
    }
    SECTION("Part 1") {
        REQUIRE(d.calculateBank(d.banks.at(0).data) == std::pair<int64_t, int64_t>{9, 8});
        REQUIRE(d.calculateBank(d.banks.at(1).data) == std::pair<int64_t, int64_t>{8, 9});
        REQUIRE(d.calculateBank(d.banks.at(2).data) == std::pair<int64_t, int64_t>{7, 8});
        REQUIRE(d.calculateBank(d.banks.at(3).data) == std::pair<int64_t, int64_t>{9, 2});

        REQUIRE(d.part1() == 357);
    }
}
