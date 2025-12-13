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

    SECTION("Button tests") {
        auto& buttons = d.machines.at(0).buttons;

        auto vec = std::vector<int64_t>(4);
        for (size_t i = 0; i < 10; ++i) {
            buttons.at(0).click(vec);
            REQUIRE(vec == std::vector<int64_t> { 0, 0, 0, (int64_t) -i - 1 });
        }
    }

    SECTION("Part 1") {
        REQUIRE(std::get<std::uint64_t>(d.part1()) == 7);
    }

#ifdef HAS_128_BIT_INT
    SECTION("128 bit extensions") {
        auto& m1 = d.machines.at(0);
        // 3 == 9 * 3 = 27
        // 27 / 4 = 6R3
        INFO(std::bitset<128>(m1.buttons.at(0).bigMask));
        INFO(std::bitset<128>((__uint128_t) 0x8'000'000));
        REQUIRE(m1.buttons.at(0).bigMask == (__uint128_t) 0x8'000'000); 

        __uint128_t encodedJoltage = 0;
        encodedJoltage += (((__uint128_t) 1) << (9 * 3)) * (__uint128_t) 9; 

        REQUIRE(d.isButtonEnabled(
            encodedJoltage, 4, m1.buttons.at(0)
        ));

        for (size_t i = 1; i < m1.buttons.size(); ++i) {
            REQUIRE_FALSE(d.isButtonEnabled(
                encodedJoltage, 4, m1.buttons.at(i)
            ));
        }

        for (int64_t i = 9; i > 0; --i) {
            REQUIRE((int64_t) (encodedJoltage >> (9 * 3)) % 512 == i);
            m1.buttons.at(0).click(encodedJoltage);
        }
    }

    SECTION("Part 2") {
        REQUIRE(std::get<std::uint64_t>(d.part2()) == 33);
    }
#endif
}
