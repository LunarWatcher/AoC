#pragma once

#include <common/Day.hpp>

namespace aoc2019 {

class Day1 : public common::Day {
public:

    DECLARE_DAY(2019, 1);

    void parse() override;
    uint64_t part1() override;
    uint64_t part2() override;

};

}
