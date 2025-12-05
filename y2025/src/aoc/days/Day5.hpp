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
    uint64_t part1() override;
    uint64_t part2() override;
    bool contains(const common::Loader::Range& r, uint64_t val);

};

}
