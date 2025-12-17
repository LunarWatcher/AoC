#pragma once

#include "common/math/Vec.hpp"
#include <common/Day.hpp>
#include <vector>

namespace aoc2019 {

class Day10 : public common::Day {
public:
    std::vector<common::Vec2d> asteroids;
    common::Vec2d origin{0,0};

    DECLARE_DAY(2019, 10);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
