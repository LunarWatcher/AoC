#include <catch2/catch_test_macros.hpp>

#include <aoc/days/Day4.hpp>

TEST_CASE("Day 4 edge test case 1", "[D4]") {
    aoc2019::Day4 d{"test/day4.1.txt"};
    d.parse();

    SECTION("Parse") {
        REQUIRE(d.range.left == 111222);
        REQUIRE(d.range.right == 111222);
    }

    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 1);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 0);
    }
}

TEST_CASE("Day 4 edge test case 2", "[D4]") {
    aoc2019::Day4 d{"test/day4.2.txt"};
    d.parse();

    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 1);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 0);
    }
}

TEST_CASE("Day 4 edge test case 3", "[D4]") {
    aoc2019::Day4 d{"test/day4.3.txt"};
    d.parse();

    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 1);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 1);
    }
}

TEST_CASE("Day 4 edge test case 4", "[D4]") {
    aoc2019::Day4 d{"test/day4.4.txt"};
    d.parse();

    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 1);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<uint64_t>(d.part2()) == 1);
    }
}
