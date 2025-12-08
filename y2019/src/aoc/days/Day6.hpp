#pragma once

#include <common/Day.hpp>
#include <unordered_map>
#include <vector>

namespace aoc2019 {

class Day6 : public common::Day {
public:
    std::unordered_map<std::string, std::vector<std::string>> orbits;

    DECLARE_DAY(2019, 6);

    void parse() override;

    uint64_t recurseTree(const std::string& currentRoot, uint64_t treeSize);
    uint64_t recurseTreeP2(
        const std::string& currentRoot,
        uint64_t treeSize,
        bool& hasMerged
    );
    
    common::Output part1() override;
    common::Output part2() override;

};

}
