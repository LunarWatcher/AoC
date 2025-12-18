#pragma once

#include "common/math/Vec.hpp"
#include <common/Day.hpp>
#include <vector>

namespace aoc2019 {

struct Moon {
    common::Vec3 position;
    common::Vec3 velocity { 0, 0, 0 };
};

class Day12 : public common::Day {
public:
    std::vector<Moon> moons;

    DECLARE_DAY(2019, 12);

    void simulate(
        std::vector<Moon>& state
    );
    
    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
