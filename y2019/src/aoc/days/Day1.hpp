#pragma once

#include <common/Day.hpp>
#include <vector>
#include <cstdint>

namespace aoc2019 {

class Day1 : public common::Day {
public:
    std::vector<uint64_t> masses;
    DECLARE_DAY(2019, 1);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
