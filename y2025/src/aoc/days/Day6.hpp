#pragma once

#include <common/Day.hpp>
#include <vector>

namespace aoc2025 {

enum class Operator {
    MULT, ADD
};

struct D6Input {
    std::vector<
        std::vector<int64_t>
    > lines;
    std::vector<Operator> ops;
};  

class Day6 : public common::Day {
public:
    D6Input input;

    DECLARE_DAY(2025, 6);

    void parse() override;
    uint64_t part1() override;
    uint64_t part2() override;

};

}
