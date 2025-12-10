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

        REQUIRE(m2.buttons == std::vector<Button> {
            Button { 0b11101 },
            Button { 0b01100 },
            Button { 0b10001 },
            Button { 0b00111 },
            Button { 0b11110 },
        });
        REQUIRE(m3.buttons == std::vector<Button> {
            Button { 0b11111 },
            Button { 0b11001 },
            Button { 0b110111 },
            Button { 0b110 },
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
