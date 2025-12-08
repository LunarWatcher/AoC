#include "Day7.hpp"
#include "common/loader/Loader.hpp"
#include <numeric>
#include <queue>
#include <algorithm>
#include <unordered_map>

namespace aoc2025 {

void Day7::parse() {
    auto lines = common::Loader::getRawLinesForProcessing(
        this->path
    );

    for (size_t y = 0; y < lines.size(); ++y) {
        auto& line = lines.at(y);

        std::unordered_map<int64_t, Splitter> splitters;
        for (size_t x = 0; x < line.size(); ++x) {
            if (line.at(x) == '.') {
                continue;
            } 

            auto asVec = common::Vec2 {
                (int64_t) x,
                (int64_t) y
            };

            if (line.at(x) == 'S') {
                this->input.emitter = asVec;
            } else if (line.at(x) == '^') {
                splitters[(int64_t) x] = {asVec};
            } else {
                throw std::runtime_error("Wtf is a " + line.substr(x, 1));
            }
        }

        if (splitters.size() == 0) {
            continue;
        }

        this->input.splitters.push_back(splitters);
    }
}

std::pair<uint64_t, uint64_t> Day7::solve() {
    auto input = this->input;

    uint64_t splitCount = 0;
    uint64_t combinedRealities = 0;

    std::unordered_map<int64_t, uint64_t> beams = {
        {input.emitter.x, 1}
    };
    for (auto& splitters : input.splitters) {
        std::unordered_map<int64_t, uint64_t> newBeams;


        for (auto& [x, realities] : beams) {
            auto splitter = splitters.find(x);
            if (splitter == splitters.end()) {
                newBeams[x] += realities;
                continue;
            }
            newBeams[x - 1] += realities;
            newBeams[x + 1] += realities;

            if (++splitter->second.hits == 1) {
                ++splitCount;
            }
        }
        beams = newBeams;
    }

    for (auto& [_, realities] : beams) {
        combinedRealities += realities;
    }

    return { splitCount, combinedRealities };
}

common::Output Day7::part1() {
    return solve().first;
}

common::Output Day7::part2() {
    return solve().second;
}

}
