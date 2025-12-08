#pragma once

#include "common/loader/Loader.hpp"
#include <common/Day.hpp>

namespace aoc2019 {

class Day4 : public common::Day {
public:
    common::Loader::Range range;

    DECLARE_DAY(2019, 4);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
