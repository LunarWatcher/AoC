#include "Day9.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2025 {

void Day9::parse() {
    for (auto& line : common::Loader::getRawLinesForProcessing(this->path)) {
        auto split = stc::string::split(line, ',');

        this->points.push_back({
            std::stoll(split.at(0)),
            std::stoll(split.at(1)),
        });
    }
}

common::Output Day9::part1() {
    uint64_t maxArea = 0;

    for (size_t i = 0; i < points.size() - 1; ++i) {
        auto& p = points.at(i);
        for (size_t j = i + 1; j < points.size(); ++j) {
            auto& p2 = points.at(j);
            uint64_t area = std::abs(
                p.x - p2.x + 1
            ) * std::abs(
                p.y - p2.y + 1
            );
            maxArea = std::max(maxArea, area);
        }
    }

    return maxArea;
}

common::Output Day9::part2() {
    uint64_t maxArea = 0;

    // Assumption: Given
    // #--#
    // |..|
    // #--#
    //
    // The greatest area will never be i,i+1, as that's just a line for all inputs. 
    // A line will never be diagonal
    for (size_t i = 0; i < points.size() - 2; ++i) {
        auto& p = points.at(i);
        for (size_t j = i + 2; j < points.size(); ++j) {
            auto& p2 = points.at(j);
            auto dx = p.x - p2.x;
            auto dy = p.y - p2.y;

            uint64_t area = std::abs(
                dx + 1
            ) * std::abs(
                dy + 1
            );
            auto c1 = common::Vec2 { p.x, p2.y };
            auto c2 = common::Vec2 { p2.x, p.y };
            for (size_t k = 0; k < points.size(); ++k) {
                auto& refPoint = points.at(k);
                if (refPoint == c1 || refPoint == c2) {
                    std::cout << p << "-" << p2 << std::endl;
                    maxArea = std::max(maxArea, area);
                    break;
                }
                
            }
        }
    }

    return maxArea;
}

}
