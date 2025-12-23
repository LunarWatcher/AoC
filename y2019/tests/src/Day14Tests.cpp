#include "aoc/days/Day14.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("Test 1") {
    aoc2019::Day14 d("test/day14.1.txt");
    d.parse();

    SECTION("Parsing") {
        REQUIRE(d.reactions.size() == 9);
        auto plain = d.reactions.at("NZVS");
        REQUIRE(plain.productQuantity == 5);

        REQUIRE(plain.reagents.size() == 1);
        REQUIRE(plain.reagents.at("ORE") == 157);

        // auto commaSeparated = d.reactions.at(3);
        // REQUIRE(commaSeparated.first.quantity == 9);
        // REQUIRE(commaSeparated.first.reagent == "QDVJ");

        // REQUIRE(commaSeparated.second.size() == 3);
        // REQUIRE(commaSeparated.second.at(1).quantity == 1);
        // REQUIRE(commaSeparated.second.at(1).reagent == "GPVTF");
    }
    SECTION("Part 1") {
        REQUIRE(std::get<int64_t>(d.part1()) == 13312);
    }
}

TEST_CASE("Test 2") {
    aoc2019::Day14 d("test/day14.2.txt");
    d.parse();
    SECTION("Part 1") {
        REQUIRE(
            std::get<int64_t>(d.part1()) == 31
        );
    }
}
