#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
namespace common {

struct Vec2 {
    int64_t x;
    int64_t y;

    int64_t manhatten(const Vec2& other = { 0, 0 }) const {
        return std::abs(x - other.x) + std::abs(y - other.y);
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2 {
            x - other.x,
            y - other.y
        };
    }
};

struct Vec3 {
    int64_t x, y, z;

    int64_t euclidiean(const Vec3& other = { 0, 0, 0 }) const {
        auto dx = other.x - x;
        auto dy = other.y - y;
        auto dz = other.z - z;
        return (int64_t) std::sqrt(
            dx * dx + dy * dy + dz * dz
        );
    }
};

struct Line {
    Vec2 start;
    Vec2 end;

    /**
     * Currently only handles intersects where the lines are on opposite axes.
     */
    bool linearIntersect(
        const Line& other
    ) const {
        return (
            other.start.x > std::min(start.x, end.x)
            && other.end.x < std::max(start.x, end.x)
            && start.y > std::min(other.start.y, other.end.y)
            && start.y < std::max(other.start.y, other.end.y)
        ) || (
            start.x > std::min(other.start.x, other.end.x)
            && start.x < std::max(other.start.x, other.end.x)
            && other.start.y > std::min(start.y, end.y)
            && other.end.y < std::max(start.y, end.y)
        );
    }
};



}
