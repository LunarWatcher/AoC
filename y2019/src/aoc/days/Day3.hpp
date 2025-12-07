#pragma once

#include "common/loader/Loader.hpp"
#include "common/math/Vec.hpp"
#include <common/Day.hpp>

namespace aoc2019 {

struct LineWithPointData {
    common::Vec2 start;
    common::Vec2 end;
    int64_t traveledAtStart;

    /**
     * Currently only handles intersects where the lines are on opposite axes.
     */
    bool linearIntersect(
        const LineWithPointData& other
    ) const {
        return (
            other.start.x > std::min(start.x, end.x)
            && other.end.x < std::max(start.x, end.x)
            && start.y > std::min(other.start.y, other.end.y)
            && start.y < std::max(other.start.y, other.end.y)
        ) || (
            start.x > std::min(other.start.x, other.end.x)
            && start.x < std::max(other.start.x, other.end.x)
            && other.start.y > std::min(start.y, end.y)
            && other.end.y < std::max(start.y, end.y)
        );
    }
};

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
    
    std::unordered_map<WireDirection, std::vector<LineWithPointData>> convertToWires(
        const std::vector<common::Loader::DirectionalInstruction>& instructions
    );

    uint64_t part1() override;
    uint64_t part2() override;

};

}
