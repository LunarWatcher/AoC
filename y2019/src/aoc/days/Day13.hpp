#pragma once

#include "aoc/intcode/IntCode.hpp"
#include <common/Day.hpp>

namespace aoc2019 {

enum class TileType {
    EMPTY = 0,
    WALL = 1,
    BLOCK = 2,
    HORIZONTAL_PADDLE = 3,
    BALL = 4
};

class Day13 : public common::Day {
public:
    Program prog;

    DECLARE_DAY(2019, 13);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
