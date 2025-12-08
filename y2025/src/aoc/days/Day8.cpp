#include "Day8.hpp"
#include "common/loader/Loader.hpp"
#include "common/math/Vec.hpp"
#include "stc/StringUtil.hpp"
#include <limits>
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
    std::map<std::pair<int64_t, int64_t>, std::tuple<Box*, Box*, int64_t>> links;
    for (size_t i = 0; i < boxes.size() - 1; ++i) {
        auto& box = boxes.at(i);

        for (size_t j = 0; j < boxes.size(); ++j) {
            if (i == j) continue;
            auto& box2 = boxes.at(j);

            auto dist = box.pos.euclidiean(box2.pos);

            // if {minbox, box, mindist} in list, the inverse link has already been established.
            // The two notes are mutually closest to each other. Skip the link
            if (!links.contains({j, i})) {
                links[{i, j}] = {
                    &box, &box2, dist
                };
            }
        }

    }

    std::vector<std::tuple<Box*, Box*, int64_t>> shortestLinks;

    shortestLinks.reserve(links.size());
    for (auto& [_, link] : links) {
        shortestLinks.push_back(link);
    }

    std::sort(
        shortestLinks.begin(),
        shortestLinks.end(),
        [](const auto& a, const auto& b) {
            return std::get<2>(a) < std::get<2>(b); 
        }
    );

    for (size_t i = 0; i < boxes.size(); ++i) {
        auto& [a, b, d] = shortestLinks.at(i);
        std::cout << "IN: "
            << a->pos.x << "," << a->pos.y << "," << a->pos.z
            << " --> "
            << b->pos.x << "," << b->pos.y << "," << b->pos.z
            << "/ " << d
            << std::endl;
        a->links.push_back(b);
        b->links.push_back(a);
    }

    std::vector<std::vector<common::Vec3>> circuits;

    for (auto& box : boxes) {
        if (box.consumed) {
            continue;
        }
        std::vector<common::Vec3> circuit {
            box.pos
        };
        box.consumed = true;
        std::queue q(box.links.begin(), box.links.end());

        // std::cout << "Root: " << box.pos.x << ", " << box.pos.y << ", " << box.pos.z << std::endl;

        while (q.size()) {
            auto* b = q.front();
            q.pop();
            
            // std::cout << "\tNext: " << b->pos.x << "," << b->pos.y << "," << b->pos.z << std::endl;

            if (b->consumed) {
                continue;
            }

            b->consumed = true;
            circuit.push_back(b->pos);

            for (auto link : b->links) {
                if (link->consumed) {
                    continue;
                }

                q.push(link);
            }
        }

        circuits.push_back(circuit);
    }

    std::sort(
        circuits.begin(),
        circuits.end(),
        [](const auto& a, const auto& b) {
            return a.size() > b.size(); 
        }
    );

    for (size_t i = 0; i < 3; ++i) {
        for (auto& circuit : circuits.at(i)) {
            // std::cout << "\t" << circuit.x << "," << circuit.y << "," << circuit.z << std::endl;
        }
    }

    return circuits.at(0).size()
        * circuits.at(1).size()
        * circuits.at(2).size();
}

uint64_t Day8::part2() {
    return 0;
}

}
