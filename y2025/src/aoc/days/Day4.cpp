#include "Day4.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2025 {

void Day4::parse() {
    map = common::Loader::loadMap<TileType>(
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
    height = (int64_t) map.size();
    width = (int64_t) map.at(0).size();
}

uint64_t Day4::checkRemovable(
    decltype(map)& map,
    bool mutate
) {
    std::vector<std::pair<int64_t, int64_t>> neighbours;
    // We won't need this much on the average run. My part 1 result was like 1500
    neighbours.reserve(2000);
    for (int64_t y = 0; y < this->height; ++y) {
        for (int64_t x = 0; x < this->width; ++x) {
            if (map.at(y).at(x) != TileType::TOILET_ROLL) {
                continue;
            }
            int tileNeighbours = 0;
            for (int64_t i = -1; i <= 1; ++i) {
                for (int64_t j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) {
                        continue;
                    }
                    auto dx = x + i;
                    if (dx < 0 || dx >= width) {
                        continue;
                    }
                    auto dy = y + j;
                    if (dy < 0 || dy >= height) {
                        continue;
                    }

                    if (map.at(dy).at(dx) == TileType::TOILET_ROLL) {
                        ++tileNeighbours;

                        if (tileNeighbours == 4) {
                            goto out;
                        }
                    }
                }
            }
            if (tileNeighbours < 4) {
                neighbours.push_back({x, y});
            }
out:;
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
