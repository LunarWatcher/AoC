#include "aoc/days/Day10.hpp"
#include <bitset>
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

        REQUIRE(m1.indicators == 0b0110);
        REQUIRE(m2.indicators == 0b01000);
        REQUIRE(m3.indicators == 0b101110);

        REQUIRE(m1.buttons.size() == 6);
        REQUIRE(m2.buttons.size() == 5);
        REQUIRE(m3.buttons.size() == 4);

        REQUIRE(m1.joltages.size() == 4);
        REQUIRE(m2.joltages.size() == 5);
        REQUIRE(m3.joltages.size() == 6);

        auto m1Expected = std::vector<size_t> {
            0b1000,
            0b1010,
            0b0100,
            0b1100,
            0b0101,
            0b0011,
        };
        for (size_t i = 0; i < m1.buttons.size(); ++i) {
            INFO(i << "; " << std::bitset<4>(m1.buttons.at(i).mask) << "=?=" << std::bitset<4>(m1Expected.at(i)));
            REQUIRE(m1.buttons.at(i).mask == m1Expected.at(i));
        }
    }


    SECTION("Part 1") {
        REQUIRE(std::get<std::uint64_t>(d.part1()) == 7);
    }

    SECTION("Detached linsys solver") {
        LinAlgSystem system {
            .buttonCount = 2,
            .solutionsCol = { 5, 2 }
        };
        system.mat = {
            { 1, 1,  0 },
            { 0, 1,  0 },
        };
        // System:
        // x + y = 5
        //     y = 2
        system.gaussEliminate();
        REQUIRE(system.mat == std::vector<std::vector<int64_t>> {
            { 1, 0, 3 },
            { 0, 1, 2 }
        });
        REQUIRE(system.pivots == std::vector { true, true });
        // Buttons are ignored for squares, so this shouldn't ever be triggered
        std::vector<int64_t> sols;
        REQUIRE_NOTHROW(sols = system.solve({}));

        REQUIRE(sols == std::vector<int64_t> { 3, 2 });

        // REQUIRE(system.checkValidity(sols, {
        //     Button { .maskAsArray = { true, true } },
        //     Button { .maskAsArray = { false, true } }
        // }) == 0);

    }

    SECTION("Part 2 linsys assembly") {
        auto& machine = d.machines.at(0);
        LinAlgSystem system {
            .buttonCount = machine.buttons.size(),
            .solutionsCol = machine.joltages
        };
        REQUIRE(
            system.mat.size() == 4
        );

        for (auto& row : system.mat) {
            // 6 buttons + solutions column (embedded during elimination, not prepopulated)
            REQUIRE(row.size() == 7);
        }
        d.assembleSystem(system, machine.buttons);

        // Computed by hand
        // The cols represent x_0..x_n, expectedAnswer
        // The exepcted answer is, again, not populated at this point
        std::vector<std::vector<int64_t>> expected = {
            { 0, 0, 0, 0, 1, 1,   0 },
            { 0, 1, 0, 0, 0, 1,   0 },
            { 0, 0, 1, 1, 1, 0,   0 },
            { 1, 1, 0, 1, 0, 0,   0 },
        };


        for (size_t i = 0; i < expected.size(); ++i) {
            auto& exp = expected.at(i);
            auto& actual = system.mat.at(i);

            for (size_t v = 0; v < exp.size(); ++v) {
                INFO("Row " << i << ", col " << v);
                REQUIRE(exp.at(v) == actual.at(v));
            }
        }

        system.gaussEliminate();

        REQUIRE(system.mat == std::vector<std::vector<int64_t>> {
            {1, 0, 0, 1, 0, -1, 2 },
            {0, 1, 0, 0, 0, 1, 5 },
            {0, 0, 1, 1, 0, -1, 1 },
            {0, 0, 0, 0, 1, 1, 3 },
        });
        REQUIRE(system.pivots == std::vector { true, true, true, false, true, false });

        auto result = system.solve(machine.buttons);

        // REQUIRE(system.checkValidity(result, machine.buttons) == 0);
    }

    // SECTION("Part 2") {
    //     REQUIRE(std::get<std::uint64_t>(d.part2()) == 10);
    // }
}
