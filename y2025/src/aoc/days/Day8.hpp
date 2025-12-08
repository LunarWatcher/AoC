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

    DECLARE_DAY(2025, 8);

    void parse() override;
    uint64_t part1() override;
    uint64_t part2() override;

};

}
