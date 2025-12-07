#pragma once

#include <common/Day.hpp>

namespace aoc2019 {

class Day5 : public common::Day {
public:

    DECLARE_DAY(2019, 5);

    void parse() override;
    uint64_t part1() override;
    uint64_t part2() override;

};

}
