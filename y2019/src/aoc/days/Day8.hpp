#pragma once

#include <common/Day.hpp>

namespace aoc2019 {

class Day8 : public common::Day {
public:

    DECLARE_DAY(2019, 8);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
