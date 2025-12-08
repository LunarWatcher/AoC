#include <catch2/catch_test_macros.hpp>

#include "aoc/days/Day1.hpp"
#include "aoc/days/Day2.hpp"
#include "aoc/days/Day3.hpp"
#include "aoc/days/Day4.hpp"
#include "aoc/days/Day5.hpp"
#include "aoc/days/Day6.hpp"
#include "aoc/days/Day7.hpp"
#include "aoc/days/Day8.hpp"

using namespace aoc2019;

TEST_CASE("Day 1", "[Regression]") {
    Day1 d;
    d.parse();
    REQUIRE(std::get<uint64_t>(d.part1()) == 3159380);
    REQUIRE(std::get<uint64_t>(d.part2()) == 4736213);
}

TEST_CASE("Day 2", "[Regression]") {
    Day2 d;
    d.parse();
    REQUIRE(d.prog.ram.size() == 117);
    REQUIRE(std::get<int64_t>(d.part1()) == 4570637);
    REQUIRE(std::get<int64_t>(d.part2()) == 5485);
}

TEST_CASE("Day 3", "[Regression]") {
    Day3 d;
    d.parse();
    REQUIRE(std::get<uint64_t>(d.part1()) == 2129);
    REQUIRE(std::get<uint64_t>(d.part2()) == 134662);
}

TEST_CASE("Day 4", "[Regression]") {
    Day4 d;
    d.parse();
    REQUIRE(std::get<uint64_t>(d.part1()) == 1767);
    REQUIRE(std::get<uint64_t>(d.part2()) == 1192);
}

TEST_CASE("Day 5", "[Regression]") {
    Day5 d;
    d.parse();
    REQUIRE(std::get<int64_t>(d.part1()) == 6731945ll);
    REQUIRE(std::get<int64_t>(d.part2()) == 9571668ll);
}

TEST_CASE("Day 6", "[Regression]") {
    Day6 d;
    d.parse();
    REQUIRE(std::get<uint64_t>(d.part1()) == 227612);
    REQUIRE(std::get<uint64_t>(d.part2()) == 454);
}

TEST_CASE("Day 7", "[Regression]") {
    Day7 d;
    d.parse();
    REQUIRE(std::get<int64_t>(d.part1()) == 22012);
    REQUIRE(std::get<int64_t>(d.part2()) == 4039164ll);
}

TEST_CASE("Day 8", "[Regression]") {
    Day8 d;
    d.parse();
    SECTION("Parsing") {
        REQUIRE(d.images.size() == 100);
    }
    SECTION("Part 1") {
        REQUIRE(std::get<uint64_t>(d.part1()) == 1206);
    }
    SECTION("Part 2") {
        REQUIRE(std::get<std::string>(d.part2()) == R"(
####...##.###...##..###..
#.......#.#..#.#..#.#..#.
###.....#.#..#.#....#..#.
#.......#.###..#.##.###..
#....#..#.#.#..#..#.#....
####..##..#..#..###.#....
)");
    }
}
