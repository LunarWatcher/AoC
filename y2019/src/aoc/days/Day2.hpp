#pragma once

#include "aoc/intcode/IntCode.hpp"
#include <common/Day.hpp>
#include <cstdint>

namespace aoc2019 {

class Day2 : public common::Day {
public:
    Program prog;

    DECLARE_DAY(2019, 2);

    void parse() override;
    uint64_t part1() override;
    uint64_t part2() override;

};

}
