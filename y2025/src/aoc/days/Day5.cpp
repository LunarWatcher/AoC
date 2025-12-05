#include "Day5.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2025 {

void Day5::parse() {
    data = common::Loader::splitLoader<D5Input>(
        this->path, 
        [](D5Input& data, const auto& line, int mode) {
            if (mode > 1) {
                [[unlikely]]
                throw std::runtime_error("Parsing error: found unexpected new mode");
            }
            if (mode == 0) {
                data.ranges.push_back(common::Loader::Range { line });
            } else {
                data.ingredientIds.push_back(std::stoull(line));
            }
        }
    );
}

uint64_t Day5::part1() {
    uint64_t fresh = 0;
    for (auto& id : data.ingredientIds) {
        for (auto& [start, end] : data.ranges) {
            if (id >= start && id <= end) {
                ++fresh;
                break;
            }
        }
    }
    return fresh;
}

uint64_t Day5::part2() {
    return 0;
}

}
