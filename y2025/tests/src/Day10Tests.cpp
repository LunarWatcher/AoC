#include "aoc/days/Day10.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace aoc2025;

TEST_CASE("Test 1", "[Day10]") {
    Day10 d("test/day10.1.txt");
    d.parse();

    SECTION("Parsing") {
        REQUIRE(d.machines.size() == 3);

        auto& m1 = d.machines.at(0);
        auto& m2 = d.machines.at(1);
        auto& m3 = d.machines.at(2);

        REQUIRE(m1.indicators == std::vector { false, true, true, false });
        REQUIRE(m2.indicators == std::vector { false, false, false, true, false });
        REQUIRE(m3.indicators == std::vector { false, true, true, true, false, true });

        REQUIRE(m1.buttons.size() == 6);
        REQUIRE(m2.buttons.size() == 5);
        REQUIRE(m3.buttons.size() == 4);

        REQUIRE(m1.buttons == std::vector<Button> {
            Button { .targets = { 3 } },
            Button { .targets = { 1, 3 } },
            Button { .targets = { 2 } },
            Button { .targets = { 2, 3 } },
            Button { .targets = { 0, 2 } },
            Button { .targets = { 0, 1 } },
        });
        REQUIRE(m2.buttons == std::vector<Button> {
            Button { .targets = { 0, 2, 3, 4 } },
            Button { .targets = { 2, 3 } },
            Button { .targets = { 0, 4 } },
            Button { .targets = { 0, 1, 2 } },
            Button { .targets = { 1, 2, 3, 4 } },
        });
        REQUIRE(m3.buttons == std::vector<Button> {
            Button { .targets = { 0, 1, 2, 3, 4 } },
            Button { .targets = { 0, 3, 4 } },
            Button { .targets = { 0, 1, 2, 4, 5 } },
            Button { .targets = { 1, 2 } },
        });

        REQUIRE(
            m1.joltages == std::vector<uint64_t> {
                3, 5, 4, 7
            }
        );
        REQUIRE(
            m2.joltages == std::vector<uint64_t> {
                7, 5, 12, 7, 2
            }
        );
        REQUIRE(
            m3.joltages == std::vector<uint64_t> {
                10, 11, 11, 5, 10, 5
            }
        );
    }

    SECTION("Part 1") {
        REQUIRE(std::get<std::uint64_t>(d.part1()) == 7);
    }
}
