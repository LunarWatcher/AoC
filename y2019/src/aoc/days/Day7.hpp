#pragma once

#include <common/Day.hpp>
#include <aoc/intcode/IntCode.hpp>

namespace aoc2019 {

class Day7 : public common::Day {
public:
    Program prog;

    DECLARE_DAY(2019, 7);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
