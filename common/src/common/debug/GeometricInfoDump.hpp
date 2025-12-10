#pragma once

#include "common/math/Vec.hpp"
#include <iostream>
namespace common::debug {

struct InfoDumpTwoPointRectangle {
    const common::Vec2& start, end;

};

inline std::ostream& operator<<(
    std::ostream& ss,
    const InfoDumpTwoPointRectangle& data
) {
    auto& [start, end] = data;
    return ss
        << "\n----------------------\n"
        << "DEBUG: Defined points:\n"
        << "\t" << start << "\n"
        << "\t" << end << "\n"
        << "Inferred rectangle (CCW or CW):\n"
        << "\t" << start << "\n"
        << "\t" << common::Vec2 { start.x, end.y } << "\n"
        << "\t" << end << "\n"
        << "\t" << common::Vec2 { end.x, start.y } << "\n"
        << "Vector render copypasta:\n"
        << "(" << start << "),"
        << "(" << common::Vec2 { start.x, end.y } << "),"
        << "(" << end << "),"
        << "(" << common::Vec2 { end.x, start.y } << ")\n"
        << "----------------------\n";

}

}
