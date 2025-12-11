#pragma once

#include <common/Day.hpp>
#include <unordered_map>
#include <vector>

namespace aoc2025 {

struct Server {
    std::vector<std::string> outputs;
};

struct Rays {
    std::uint64_t none = 0;
    std::uint64_t dft = 0;
    std::uint64_t fft = 0;
    std::uint64_t fft_dft = 0;
};

class Day11 : public common::Day {
public:
    std::unordered_map<std::string, Server> racks;

    DECLARE_DAY(2025, 11);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

    bool p2borked() override { return true; }
};

}
