#include <catch2/catch_test_macros.hpp>

#include "aoc/days/Day8.hpp"

TEST_CASE("Image parsing", "[Day8]") {
    aoc2019::Image i{
        3, 2,
        "123456"
    };

    REQUIRE(i.pixels.size() == 2);
    REQUIRE(i.pixels.at(0) == std::vector { 1, 2, 3 });
    REQUIRE(i.pixels.at(1) == std::vector { 4, 5, 6 });
}

