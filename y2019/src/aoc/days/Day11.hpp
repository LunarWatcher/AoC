#pragma once

#include "aoc/intcode/IntCode.hpp"
#include <common/Day.hpp>

namespace aoc2019 {

class Day11 : public common::Day {
public:
    Program prog;

    DECLARE_DAY(2019, 11);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
