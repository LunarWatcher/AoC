#pragma once

#include "aoc/intcode/IntCode.hpp"
#include <common/Day.hpp>

namespace aoc2019 {

class Day5 : public common::Day {
public:
    Program prog;

    DECLARE_DAY(2019, 5);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
