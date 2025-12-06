#pragma once

#include <common/Day.hpp>
#include <vector>

namespace aoc2025 {

enum class Operator {
    MULT, ADD
};

struct Column {
    std::vector<std::string> nums;
    Operator op;
};

class Day6 : public common::Day {
public:
    std::vector<Column> input;

    DECLARE_DAY(2025, 6);

    void parse() override;
    uint64_t part1() override;
    uint64_t part2() override;

};

}
