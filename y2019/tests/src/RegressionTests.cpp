#include <catch2/catch_test_macros.hpp>

#include "aoc/days/Day1.hpp"
#include "aoc/days/Day2.hpp"
#include "aoc/days/Day3.hpp"
#include "aoc/days/Day4.hpp"
#include "aoc/days/Day5.hpp"
#include "aoc/days/Day6.hpp"
#include "aoc/days/Day7.hpp"
#include "aoc/days/Day8.hpp"
#include "aoc/days/Day9.hpp"
#include "aoc/days/Day10.hpp"
#include "aoc/days/Day11.hpp"
#include "aoc/days/Day12.hpp"
#include "aoc/days/Day13.hpp"
#include "aoc/days/Day14.hpp"
#include "aoc/days/Day15.hpp"

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

TEST_CASE("Day 9", "[Regression]") {
    Day9 d;
    d.parse();
    REQUIRE(std::get<int64_t>(d.part1()) == 4006117640ull);
    REQUIRE(std::get<int64_t>(d.part2()) == 88231ull);
}

TEST_CASE("Day 10", "[Regression]") {
    Day10 d;
    d.parse();
    REQUIRE(std::get<uint64_t>(d.part1()) == 340);
    REQUIRE(std::get<uint64_t>(d.part2()) == 2628);
}

TEST_CASE("Day 11", "[Regression]") {
    Day11 d;
    d.parse();
    REQUIRE(std::get<uint64_t>(d.part1()) == 2054);
    REQUIRE(std::get<std::string>(d.part2()) == R"(
 #  # ###  #### ####  ##    ## #  # ###
 # #  #  #    # #    #  #    # #  # #  #
 ##   #  #   #  ###  #  #    # #### ###
 # #  ###   #   #    ####    # #  # #  #
 # #  # #  #    #    #  # #  # #  # #  #
 #  # #  # #### #### #  #  ##  #  # ###
)");
}

TEST_CASE("Day 12", "[Regression]") {
    Day12 d;
    d.parse();
    REQUIRE(std::get<uint64_t>(d.part1()) == 5937);
    REQUIRE(std::get<uint64_t>(d.part2()) == 376203951569712ull);
}

TEST_CASE("Day 13 regression test", "[Regression]") {
    Day13 d;
    d.parse();
    REQUIRE(std::get<uint64_t>(d.part1()) == 291);
    REQUIRE(std::get<uint64_t>(d.part2()) == 14204);
}

TEST_CASE("Day 14 regression test", "[Regression]") {
    Day14 d;
    d.parse();
    REQUIRE(std::get<int64_t>(d.part1()) == 158482);
    REQUIRE(std::get<int64_t>(d.part2()) == 7993831);
}

TEST_CASE("Day 15 regression test", "[Regression]") {
    Day15 d;
    d.parse();
    REQUIRE(std::get<uint64_t>(d.part1()) == 238);
    // REQUIRE(std::get<uint64_t>(d.part2()) == 392);
}
