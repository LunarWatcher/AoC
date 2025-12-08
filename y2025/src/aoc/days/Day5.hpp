#pragma once

#include "common/loader/Loader.hpp"
#include <common/Day.hpp>

namespace aoc2025 {

struct D5Input {
    std::vector<common::Loader::Range> ranges;
    std::vector<uint64_t> ingredientIds;
};

class Day5 : public common::Day {
public:
    D5Input data;

    DECLARE_DAY(2025, 5);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;
    bool contains(const common::Loader::Range& r, uint64_t val);

};

}
