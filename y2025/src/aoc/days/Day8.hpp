#pragma once

#include "common/math/Vec.hpp"
#include <common/Day.hpp>
#include <vector>

namespace aoc2025 {

struct Box {
    common::Vec3 pos;
    std::vector<Box*> links;

    bool consumed = false;
};

class Day8 : public common::Day {
public:
    std::vector<Box> boxes;
    size_t pairs;

    DECLARE_CONSTRUCTOR(2025, 8, size_t pairs = 1000), pairs(pairs) {}

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
