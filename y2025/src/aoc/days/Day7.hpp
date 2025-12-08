#pragma once

#include "common/math/Vec.hpp"
#include <common/Day.hpp>
#include <unordered_map>
#include <vector>

namespace aoc2025 {

struct Beam {
    int64_t realities = 1;
};

struct Splitter {
    common::Vec2 pos;
    int64_t hits = 0;
};

struct D7Input {
    common::Vec2 emitter;

    std::vector<std::unordered_map<int64_t, Splitter>> splitters;
};

class Day7 : public common::Day {
public:
    D7Input input;

    DECLARE_DAY(2025, 7);

    void parse() override;
    std::pair<uint64_t, uint64_t> solve();
    common::Output part1() override;
    common::Output part2() override;

};

}
