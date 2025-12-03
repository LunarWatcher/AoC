#pragma once

#include <common/Day.hpp>
#include <common/loader/Loader.hpp>
#include <cmath>

namespace aoc2025 {

class Day3 : public common::Day {
private:
    uint64_t vec2int(const std::vector<int64_t>& vec) {
        uint64_t out = 0;
        for (size_t i = 0; i < vec.size(); ++i) {
            out += (uint64_t) vec.at(i) * (uint64_t) std::pow(10, vec.size() - i - 1);
        }
        return out;
    }
public:
    std::vector<common::Loader::IntStream> banks;

    DECLARE_DAY(2025, 3);

    std::vector<int64_t> calculateBank(
        const std::vector<int64_t>& bank,
        size_t bankSize
    );

    void parse() override;
    uint64_t part1() override;
    uint64_t part2() override;

};

}
