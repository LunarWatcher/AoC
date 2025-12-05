#include "Day5.hpp"
#include "common/loader/Loader.hpp"
#include <iostream>

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
    D5Input data = this->data;

    // Deduplicate ranges
    for (size_t i = 0; i < data.ranges.size() - 1; ++i) {
        auto& r1 = data.ranges.at(i);
        // Range erased by previous iteration
        if (r1.left == 0) {
            continue;
        }
        for (size_t j = i + 1; j < data.ranges.size(); ++j) {
            auto& r2 = data.ranges.at(j);
            // Range erased by previous iteration
            if (r2.left == 0) {
                continue;
            }
            if (contains(r1, r2.left) && contains(r1, r2.right)) {
                // std::cout << r1.left << "-" << r2.right << " contains "
                //     << r2.left << " and " << r2.right << std::endl;
                r2.left = r2.right = 0;
                continue;
            } else if (contains(r2, r1.left) && contains (r2, r1.right)) {
                r1.left = r1.right = 0;
            } else if (contains(r1, r2.left)) {
                r2.left = r1.right + 1;
            } else if (contains(r1, r2.right)) {
                r2.right = r1.left - 1;
            }
        }
    }

    // At this point, all the ranges are unique, and can be added directly
    uint64_t sum = 0;
    for (auto& [start, end] : data.ranges) {
        // Skip 0 ranges
        if (start == 0) {
            continue;
        }
        auto delta = end - start;
        sum += delta + 1ull;
        // std::cout << start << "-" << end << "=" << delta + 1 << std::endl;
    }
    return sum;
}

bool Day5::contains(const common::Loader::Range& r, uint64_t val) {
    return val >= r.left && val <= r.right;
}

}
