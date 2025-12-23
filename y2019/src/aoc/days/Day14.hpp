#pragma once

#include <common/Day.hpp>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

namespace aoc2019 {

struct Reagents {
    int64_t productQuantity;
    std::unordered_map<std::string, int64_t> reagents;

    void addReaction(const std::string& line) {
        auto quantity(std::stoll(line));
        // rfind because find would break due to splitting by comma instead of splitting by space
        auto reagent(line.substr(line.rfind(' ') + 1));
        reagents[reagent] = quantity;
    }
};

class Day14 : public common::Day {
public:
    std::map<
        std::string /* product */,
        Reagents
    > reactions;

    DECLARE_DAY(2019, 14);

    void parse() override;

    std::unordered_map<std::string, int64_t> collapse(
        const std::string& next,
        int64_t desired,
        std::unordered_map<std::string, int64_t>& reserve
    );

    int64_t getMinFuel(int64_t fuel);

    common::Output part1() override;
    common::Output part2() override;

};

}
