#include "Day9.hpp"
#include "common/loader/Loader.hpp"

#include <stc/Math.hpp>

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
            auto dx = std::max(p.x, p2.x) - std::min(p.x, p2.x);
            auto dy = std::max(p.y, p2.y) - std::min(p.y, p2.y);

            uint64_t area = (dx + 1) * (dy + 1);
            for (size_t k = 0; k < points.size(); ++k) {
                const auto& a = points.at(k);
                const auto& b = points.at((k + 1) % points.size());
                auto mid = common::Vec2 {
                    a.x + (a.x - b.x) / 2,
                    a.y + (a.y - b.y) / 2
                };

                common::Vec2 c1 = { p.x, p2.y };
                common::Vec2 c2 = { p2.x, p.y };
                if (
                    stc::math::g2d::rectangleContainsPointExclusive<int64_t>(
                        a, 
                        p,
                        p2
                    ) 
                    || stc::math::g2d::rectangleContainsPointExclusive<int64_t>(
                        mid,
                        p,
                        p2
                    ) 
                    || stc::math::g2d::lineIntersectsRectangleExclusive<int64_t>(
                        a, b,
                        p,
                        c1, c2,
                        p2
                    )
                ) {
                    // std::cout << "DISCARD: Area is " << area << " between " << p << "-" << p2 
                    //     << "(" << c1 << "--" << c2 << ")"
                    //     << "by " << a << "--" << b

                    // << ";;; contains: " << stc::math::g2d::rectangleContainsPointExclusive<int64_t>(
                    //     a, 
                    //     p, p2
                    // )
                    // << ";;; contains line: " <<  stc::math::g2d::lineIntersectsRectangleExclusive<int64_t>(
                    //     a, b,
                    //     p,
                    //     c1, c2,
                    //     p2
                    // )
                    //     << std::endl;
                    goto nope;
                }

            }
                    // std::cout << "DISCARD: Area is " << area << " between " << p << "-" << p2 


                    //     << std::endl;

            maxArea = std::max(maxArea, area);
nope:;
        }
    }

    return maxArea;
}

}
