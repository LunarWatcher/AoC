#include "Day4.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2025 {

void Day4::parse() {
    map = common::Loader::mapLoader<TileType>(
        this->path,
        [](char ch) {
            if (ch == '.') {
                return TileType::EMPTY;
            } else if (ch == '@') {
                return TileType::TOILET_ROLL;
            } else {
                throw std::runtime_error("Unknown tile type: " + std::string{ch});
            }
        }
    );
}

uint64_t Day4::part1() {
    uint64_t sum = 0;
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map.at(0).size(); ++x) {
            if (map.at(y).at(x) != TileType::TOILET_ROLL) {
                continue;
            }
            int neighbours = 0;
            for (const auto& dir : this->neighbours) {
                auto loc = isInBounds(map, x, y, dir);
                if (!loc) {
                    continue;
                }
                if (map.at(loc->second).at(loc->first) == TileType::TOILET_ROLL) {
                    ++neighbours;
                }
            }
            if (neighbours < 4) {
                ++sum;
            }
        }
    }
    return sum;
}

uint64_t Day4::part2() {
    return 0;
}

}
