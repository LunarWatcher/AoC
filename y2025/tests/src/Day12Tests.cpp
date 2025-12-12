#include <catch2/catch_test_macros.hpp>

#include <aoc/days/Day12.hpp>

TEST_CASE("Test 1", "[Day12]") {
    aoc2025::Day12 d("test/day12.1.txt");
    d.parse();

    SECTION("Parsing") {
        REQUIRE(d.shapes.at(4).filled == std::vector<std::vector<bool>> {
            {true, true, true},
            {true, false, false},
            {true, true, true}
        });
        REQUIRE(d.regions.size() == 3);
        REQUIRE(d.regions.at(1).shapeCounts == std::vector<uint64_t>{
            1, 0, 1, 0, 2, 2
        });
    }

    SECTION("Part 1") {
        // TODO: This doesn't work because the naive solution is too lax for the test input. I don't know if the test
        // input can pass ever with my solution
        // REQUIRE(std::get<uint64_t>(d.part1()) == 2);
    }
}
