#include "aoc/intcode/IntCode.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Day 2 IntCode examples", "[D2][IntCode]") {
    SECTION("Main example") {
        aoc2019::IntCode computer {
            { 1,9,10,3,2,3,11,0,99,30,40,50 }
        };

        aoc2019::Program program;
        auto result = computer.run({}, &program);

        // for (auto& p : program) {
        //     std::cout << p << "," << std::endl;
        // }

        REQUIRE(result == 3500);
    }
}

TEST_CASE("Mode parsing", "[IntCode]") {
    aoc2019::IntCode computer{{}};
    SECTION("Sample from day 4") {
        REQUIRE(computer.resolveMode(1001, 0) == 0);
        REQUIRE(computer.resolveMode(1001, 1) == 1);
        for (size_t i = 0; i < 60; ++i) {
            REQUIRE(computer.resolveMode(1001, 2 + i) == 0);
        }
    }
    SECTION("Test handling of a full 3 digit modeset") {
        REQUIRE(computer.resolveMode(10101, 0) == 1);
        REQUIRE(computer.resolveMode(10101, 1) == 0);
        REQUIRE(computer.resolveMode(10101, 2) == 1);
    }
    SECTION("No modes specified should still work") {
        REQUIRE(computer.resolveMode(2, 0) == 0);
        REQUIRE(computer.resolveMode(2, 1) == 0);
        REQUIRE(computer.resolveMode(2, 2) == 0);
    }
}

TEST_CASE("Day 5 part 2 features", "[IntCode]") {
    aoc2019::IntCode computer{ 
        {
            3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,
            1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,
            999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99
        }
    };

    SECTION("Value < 8") {
        aoc2019::StdStream s {{ 5 }};
        computer.run(&s);
        REQUIRE(computer.diagnostic() == 999);
    }
}
