#include "Day1.hpp"
#include "common/loader/Loader.hpp"
#include <cmath>
#include <queue>

namespace aoc2019 {

void Day1::parse() {
    this->masses = common::Loader::loadIntVector<uint64_t>(
        this->path
    );
}

uint64_t Day1::part1() {
    uint64_t sum = 0;
    for (auto mass : masses) {
        sum += (uint64_t) std::floor((double) mass / 3.0) - 2;
    }
    return sum;
}

uint64_t Day1::part2() {
    std::deque<uint64_t> q{
        masses.begin(),
        masses.end()
    };

    int64_t sum = 0;
    while (q.size()) {
        auto mass = q.front();
        q.pop_front();

        auto fuel = (int64_t) std::floor((double) mass / 3.0) - 2;
        if (fuel <= 0) {
            continue;
        }
        q.push_back(fuel);
        sum += fuel;
    }
    return sum;
}

}
