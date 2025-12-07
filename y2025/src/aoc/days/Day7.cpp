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

uint64_t Day7::part1() {
    std::queue<common::Vec2> lasers;
    lasers.push(
        common::Vec2 {
            input.emitter.x,
            // We start at -1 to force the first check to be at y = 0 in splitter line space
            -1
        }
    );

    uint64_t out = 0;
    while (lasers.size()) {
        auto head = lasers.front();
        lasers.pop();

        // The next hit may not be immediately on the next line
        while (true) {
            head.y += 1;
            if (head.y >= (int64_t) input.splitters.size()) {
                // Beam hit the end and cannot hit any more splitters
                break;
            }

            auto& m = input.splitters.at(head.y);
            auto it = m.find(head.x);
            if (it == m.end()) {
                continue;
            }
            auto& [_, splitter] = *it;
            if (splitter.hits != 0) {
                break;
            }
            splitter.hits += 1;
            ++out;

            lasers.push({
                splitter.pos.x + 1,
                head.y
            });
            lasers.push({
                splitter.pos.x - 1,
                head.y
            });
            break;
        }
    }

    return out;
}

uint64_t Day7::part2() {
    return 0;
}

}
