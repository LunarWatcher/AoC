#pragma once

#include "common/loader/Loader.hpp"
#include "common/math/Vec.hpp"
#include <common/Day.hpp>

namespace aoc2019 {

enum class WireDirection {
    HORIZONTAL,
    VERTICAL
};

class Day3 : public common::Day {
private:
    WireDirection opposite(WireDirection src) {
        return src == WireDirection::HORIZONTAL ? WireDirection::VERTICAL : WireDirection::HORIZONTAL;
    }
public:
    std::vector<std::vector<common::Loader::DirectionalInstruction>> wires;

    DECLARE_DAY(2019, 3);

    void parse() override;
    
    std::unordered_map<WireDirection, std::vector<common::Line>> convertToWires(
        const std::vector<common::Loader::DirectionalInstruction>& instructions
    );

    uint64_t part1() override;
    uint64_t part2() override;

};

}
