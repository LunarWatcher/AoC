#include "Day8.hpp"
#include "common/data/DisjointSet.hpp"
#include "common/loader/Loader.hpp"
#include "common/math/Vec.hpp"
#include "stc/StringUtil.hpp"
#include <map>
#include <queue>

namespace aoc2025 {

void Day8::parse() {
    for (auto& line : common::Loader::getRawLinesForProcessing(this->path)) {
        auto split = stc::string::split(line, ',');

        this->boxes.push_back({{
            std::stoll(split.at(0)),
            std::stoll(split.at(1)),
            std::stoll(split.at(2)),
        }, {}});
    }

}

uint64_t Day8::part1() {
    auto boxes = this->boxes;

    std::vector<std::tuple<size_t, size_t, uint64_t>> lines;
    lines.reserve(boxes.size() * boxes.size());

    for (size_t i = 0; i < boxes.size() - 1; ++i) {
        auto& box = boxes.at(i);
        for (size_t j = i + 1; j < boxes.size(); ++j) {
            lines.push_back({ i, j, box.pos.euclidiean(boxes.at(j).pos) });
        }
    }

    // TODO: this accounts for the majority of the time spent
    std::sort(lines.begin(), lines.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) < std::get<2>(b); 
    });

    common::DisjointSet<uint64_t> dsu(boxes.size());

    for (size_t i = 0; i < this->pairs; ++i) {
        auto [b1, b2, _] = lines.at(i);
        // std::cout << "LINK NODE " << b1 << " TO " << b2 << std::endl;
        dsu.link(b1, b2);
    }

    std::priority_queue<uint64_t> q;
    for (size_t i = 0; i < boxes.size(); ++i) {
        // Only push one size per cluster
        if (dsu.parent.at(i) == i) {
            q.push(dsu.sizes.at(i));
        }
    }

    uint64_t out = 1;

    for (size_t i = 0; i < 3; ++i) {
        out *= q.top();
        q.pop();
    }

    return out;
}

uint64_t Day8::part2() {
    auto boxes = this->boxes;

    std::vector<std::tuple<size_t, size_t, uint64_t>> lines;
    lines.reserve(boxes.size() * boxes.size());

    for (size_t i = 0; i < boxes.size() - 1; ++i) {
        auto& box = boxes.at(i);
        for (size_t j = i + 1; j < boxes.size(); ++j) {
            lines.push_back({ i, j, box.pos.euclidiean(boxes.at(j).pos) });
        }
    }

    // TODO: this accounts for the majority of the time spent
    std::sort(lines.begin(), lines.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) < std::get<2>(b); 
    });

    common::DisjointSet<uint64_t> dsu(boxes.size());

    std::tuple<size_t, size_t, uint64_t> curr;
    size_t i = 0;
    while (dsu.remaining > 1) {
        curr = lines.at(i++);
        auto [b1, b2, _] = curr;
        // std::cout << "LINK NODE " << b1 << " TO " << b2 << std::endl;
        dsu.link(b1, b2);
    }

    return boxes.at(std::get<0>(curr)).pos.x
        * boxes.at(std::get<1>(curr)).pos.x;
}

}
