#include <catch2/catch_test_macros.hpp>

#include <aoc/days/Day12.hpp>

TEST_CASE("Test 1", "[Day12]") {
    aoc2019::Day12 d("test/day12.1.txt");
    d.parse();

    // SECTION("Part 1") {
    //     REQUIRE(std::get<uint64_t>(d.part1()) == 179ull);
    // }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 2772);
    }
}
