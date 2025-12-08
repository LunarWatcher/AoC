#include "aoc/days/Day1.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Day 1", "[D1]") {
    aoc2025::Day1 d("test/day1.1.txt");
    d.parse();
    SECTION("Validate parsing") {
        REQUIRE(d.dials.size() == 10);
        std::vector<std::pair<int, int>> dials = {
            std::pair(-1, 68),
            std::pair(-1, 30),
            std::pair(1, 48),
            std::pair(-1, 5),
            std::pair(1, 60),
            std::pair(-1, 55),
            std::pair(-1, 1),
            std::pair(-1, 99),
            std::pair(1, 14),
            std::pair(-1, 82),
        };
        for (size_t i = 0; i < dials.size(); ++i) {
            auto pd = d.dials.at(i);
            auto gd = dials.at(i);
            REQUIRE(pd.op == gd.first);
            REQUIRE(pd.value == gd.second);
        }
    }
    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 3);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 6);
    }
}

TEST_CASE("Day 1, input 2", "[D1]") {
    aoc2025::Day1 d("test/day1.2.txt");
    d.parse();
    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 1);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 1);
    }
}

TEST_CASE("Day 1, input 3", "[D1]") {
    aoc2025::Day1 d("test/day1.3.txt");
    d.parse();
    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 2);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 2);
    }
}

TEST_CASE("Day 1, input 4", "[D1]") {
    aoc2025::Day1 d("test/day1.4.txt");
    d.parse();
    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 2);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 2);
    }
}

