#include "aoc/intcode/IntCode.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Day 2 IntCode examples", "[D2][IntCode]") {
    SECTION("Main example") {
        aoc2019::IntCode computer {
            { 1,9,10,3,2,3,11,0,99,30,40,50 }
        };

        aoc2019::Program program;
        auto result = computer.run(&program);

        // for (auto& p : program) {
        //     std::cout << p << "," << std::endl;
        // }

        REQUIRE(result == 3500);
    }
}
