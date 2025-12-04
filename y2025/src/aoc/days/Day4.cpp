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

uint64_t Day4::checkRemovable(
    decltype(map)& map,
    bool mutate
) {
    std::vector<std::pair<size_t, size_t>> neighbours;
    // We won't need this much on the average run. My part 1 result was like 1500
    neighbours.reserve(2000);
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map.at(0).size(); ++x) {
            if (map.at(y).at(x) != TileType::TOILET_ROLL) {
                continue;
            }
            int tileNeighbours = 0;
            for (const auto& dir : this->neighbours) {
                auto loc = isInBounds(map, x, y, dir);
                if (!loc) {
                    continue;
                }
                if (map.at(loc->second).at(loc->first) == TileType::TOILET_ROLL) {
                    ++tileNeighbours;
                }
            }
            if (tileNeighbours < 4) {
                neighbours.push_back({x, y});
            }
        }
    }
    if (mutate) {
        for (auto& [x, y] : neighbours) {
            map.at(y).at(x) = TileType::EMPTY;
        }
    }
    return neighbours.size();
}

uint64_t Day4::part1() {
    auto map = this->map;
    return checkRemovable(map, false);
}

uint64_t Day4::part2() {
    auto map = this->map;
    uint64_t sum = 0;
    while (true) {
        auto s = checkRemovable(map, true);
        if (s > 0) {
            sum += s;
        } else {
            break;
        }

    }
    return sum;
}

}
