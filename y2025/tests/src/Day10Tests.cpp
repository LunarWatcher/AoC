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

    // SECTION("Button tests") {
    //     auto& buttons = d.machines.at(0).buttons;

    //     auto vec = std::vector<int64_t>(4);
    //     for (size_t i = 0; i < 10; ++i) {
    //         buttons.at(0).click(vec);
    //         REQUIRE(vec == std::vector<int64_t> { 0, 0, 0, (int64_t) -i - 1 });
    //     }
    // }

    SECTION("Part 1") {
        REQUIRE(std::get<std::uint64_t>(d.part1()) == 7);
    }

    // SECTION("Part 2") {
    //     REQUIRE(std::get<std::uint64_t>(d.part2()) == 33);
    // }
}
