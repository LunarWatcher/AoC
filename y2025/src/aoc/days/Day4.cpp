#include "Day4.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2025 {

void Day4::parse() {
    map = common::Loader::loadMap<Tile>(
        this->path,
        [](char ch) {
            if (ch == '.') {
                return Tile {TileType::EMPTY};
            } else if (ch == '@') {
                return Tile {TileType::TOILET_ROLL};
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
    int cycle
) {
    int64_t markedForDeathInCycle = 0;

    for (int64_t y = 0; y < this->height; ++y) {
        for (int64_t x = 0; x < this->width; ++x) {
            auto& tile = map.at(y).at(x);
            if (
                tile.markedForDeathInCycle != -1 
                || tile.t != TileType::TOILET_ROLL
            ) {
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
                    auto t2 = map.at(dy).at(dx);

                    if (t2.markedForDeathInCycle == -1 && t2.t == TileType::TOILET_ROLL) {
                        ++tileNeighbours;

                        if (tileNeighbours == 4) {
                            goto out;
                        }
                    }
                }
            }
            if (tileNeighbours < 4) {
                markedForDeathInCycle += 1;
                tile.markedForDeathInCycle = cycle;
            }
out:;
        }
    }
    return markedForDeathInCycle;
}

uint64_t Day4::part1() {
    auto map = this->map;
    return checkRemovable(map, false);
}

uint64_t Day4::part2() {
    auto map = this->map;
    uint64_t sum = 0;
    int cycle = 0;
    while (true) {
        auto s = checkRemovable(
            map,
            cycle
        );
        if (s > 0) {
            sum += s;
        } else {
            break;
        }
        ++cycle;
    }
    return sum;
}

}
