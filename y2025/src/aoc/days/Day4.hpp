#pragma once

#include <common/Day.hpp>
#include <optional>
#include <vector>

namespace aoc2025 {

enum class TileType : char {
    EMPTY = '.',
    TOILET_ROLL = '@'
};

class Day4 : public common::Day {
private:
    static inline std::vector<std::pair<int64_t, int64_t>> neighbours = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},
        {1, 1},
        {-1, -1},
        {-1, 1},
        {1, -1},
    };
public:
    std::vector<std::vector<TileType>> map;

    DECLARE_DAY(2025, 4);

    void parse() override;
    uint64_t part1() override;
    uint64_t part2() override;


    std::optional<std::pair<size_t, size_t>> isInBounds(
        const decltype(map)& map,
        size_t x,
        size_t y,
        const std::pair<int64_t, int64_t>& dir
    ) {
        if ((dir.first < 0 && x == 0) || (dir.second < 0 && y == 0)) {
            return std::nullopt;
        }

        x = x + dir.first;
        y = y + dir.second;

        if (x < map.at(0).size() && y < map.at(0).size()) {
            return std::pair<size_t, size_t> { x, y };
        }
        return std::nullopt;
    }

};

}
