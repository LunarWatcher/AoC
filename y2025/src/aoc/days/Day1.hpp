#pragma once

#include <common/Day.hpp>
#include <string>
#include <vector>

namespace aoc2025 {

struct Dial {
    int op;
    int value;

    Dial(const std::string& line) {
        op = line[0] == 'L' ? -1 : 1;
        value = std::stoi(line.substr(1));
    }
};

class Day1 : public common::Day {
public:
    std::vector<Dial> dials;

    DECLARE_DAY(2025, 1);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
