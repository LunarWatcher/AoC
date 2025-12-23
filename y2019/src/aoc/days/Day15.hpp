#pragma once

#include "aoc/intcode/IntCode.hpp"
#include <common/Day.hpp>

namespace aoc2019 {

enum D15Dir {
    NORTH = 1,
    SOUTH = 2,
    WEST = 3,
    EAST = 4
};

class Day15 : public common::Day {
public:
    Program prog;

    DECLARE_DAY(2019, 15);

    void parse() override;
    int64_t getCancellingMove(int64_t lastMove) {
        switch (lastMove) {
            case 1: return 2;
            case 2: return 1;
            case 3: return 4;
            case 4: return 3;
            default: throw std::runtime_error("Bad girl");
        }
    }
    int64_t right(int64_t last) {
        switch (last) {
            case NORTH: return EAST;
            case SOUTH: return WEST;
            case WEST: return NORTH;
            case EAST: return SOUTH;
            default: throw std::runtime_error("Bad girl");
        }
    }
    int64_t left(int64_t last) {
        switch (last) {
            case NORTH: return WEST;
            case SOUTH: return EAST;
            case WEST: return SOUTH;
            case EAST: return NORTH;
            default: throw std::runtime_error("Bad girl");
        }
    }
    common::Output part1() override;
    common::Output part2() override;

};

}
