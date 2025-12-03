#pragma once

#include <common/Day.hpp>
#include <common/loader/Loader.hpp>

namespace aoc2025 {

class Day3 : public common::Day {
public:
    std::vector<common::Loader::IntStream> banks;

    DECLARE_DAY(2025, 3);

    std::pair<int64_t, int64_t> calculateBank(const std::vector<int64_t>& bank);

    void parse() override;
    uint64_t part1() override;
    uint64_t part2() override;

};

}
