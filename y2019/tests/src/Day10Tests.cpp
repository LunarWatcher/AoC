#include <catch2/catch_test_macros.hpp>

#include <aoc/days/Day10.hpp>

TEST_CASE("Test 1", "[Day10]") {
    aoc2019::Day10 d("test/day10.1.txt");
    d.parse();

    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 8);
    }
}
