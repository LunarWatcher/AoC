#pragma once

#include <common/Day.hpp>
#include <optional>
#include <vector>

namespace aoc2025 {

enum class TileType : char {
    EMPTY = '.',
    TOILET_ROLL = '@'
};

struct Tile {
    TileType t;
    int markedForDeathInCycle = -1;
};

class Day4 : public common::Day {
public:
    std::vector<std::vector<Tile>> map;
    int64_t width;
    int64_t height;

    DECLARE_DAY(2025, 4);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

    uint64_t checkRemovable(
        decltype(map)& map,
        int cycle = 0
    );

};

}
