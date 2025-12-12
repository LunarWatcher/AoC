#pragma once

#include <common/Day.hpp>
#include <vector>

namespace aoc2025 {

struct Region {
    uint64_t width;
    uint64_t height;
    std::vector<uint64_t> shapeCounts;
};

struct Shape {
    std::vector<std::vector<bool>> filled{3, std::vector<bool>(3, false)};
    uint64_t area;
};

class Day12 : public common::Day {
public:
    std::vector<Region> regions;
    std::vector<Shape> shapes{6};

    DECLARE_DAY(2025, 12);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
