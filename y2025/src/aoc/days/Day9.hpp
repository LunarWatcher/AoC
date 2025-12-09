#pragma once

#include "common/math/Vec.hpp"
#include <common/Day.hpp>
#include <vector>

namespace aoc2025 {

class Day9 : public common::Day {
public:
    std::vector<common::Vec2> points;

    DECLARE_DAY(2025, 9);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

    bool p2borked() override { return true; }

};

}
