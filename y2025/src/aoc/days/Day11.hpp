#pragma once

#include <common/Day.hpp>
#include <unordered_map>
#include <vector>

namespace aoc2025 {

struct Server {
    std::vector<std::string> outputs;
};

class Day11 : public common::Day {
public:
    std::unordered_map<std::string, Server> racks;

    DECLARE_DAY(2025, 11);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

    uint64_t dfs(
        std::unordered_map<std::string, uint64_t>& memos,
        const std::string& next,
        const std::string& dest
    );
};

}
