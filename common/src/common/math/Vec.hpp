#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <ostream>
namespace common {

struct Vec2 {
    int64_t x;
    int64_t y;

    int64_t manhatten(const Vec2& other = { 0, 0 }) const {
        return std::abs(x - other.x) + std::abs(y - other.y);
    }

    int64_t euclidiean(const Vec2& other = { 0, 0 }) const {
        auto dx = other.x - x;
        auto dy = other.y - y;
        return (int64_t) std::sqrt(
            dx * dx + dy * dy
        );
    }

    int64_t dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2 {
            x - other.x,
            y - other.y
        };
    }
    Vec2 operator+(const Vec2& other) const {
        return Vec2 {
            x + other.x,
            y + other.y
        };
    }

    Vec2 operator/(int64_t val) const {
        return Vec2 {
            x / val,
            y / val
        };
    }

    bool operator==(const Vec2& other) const {
        return other.x == x && other.y == y;
    }
};

struct Vec2d {
    double x;
    double y;

    double manhatten(const Vec2d& other = { 0, 0 }) const {
        return std::abs(x - other.x) + std::abs(y - other.y);
    }

    double euclidiean(const Vec2d& other = { 0, 0 }) const {
        auto dx = other.x - x;
        auto dy = other.y - y;
        return std::sqrt(
            dx * dx + dy * dy
        );
    }

    double dot(const Vec2d& other) const {
        return x * other.x + y * other.y;
    }

    Vec2d operator-(const Vec2d& other) const {
        return Vec2d {
            x - other.x,
            y - other.y
        };
    }
    Vec2d operator+(const Vec2d& other) const {
        return Vec2d {
            x + other.x,
            y + other.y
        };
    }

    Vec2d operator/(double val) const {
        return Vec2d {
            x / val,
            y / val
        };
    }

    Vec2d div() const {
        return *this / euclidiean();
    }

    double angle(const Vec2d& other) const  {
        auto d = dot(other);
        if (d == 0)  {
            return std::numbers::pi / 2;
        }
        return std::acos(
            d / (other.euclidiean() * euclidiean())
        );
    }

    bool operator==(const Vec2d& other) const {
        auto mx = std::max(x, other.x);
        auto my = std::max(y, other.y);

        auto minx = std::min(x, other.x);
        auto miny = std::min(y, other.y);
        return 
            std::signbit(other.x) == std::signbit(x)
            && std::signbit(other.y) == std::signbit(y)
            && std::abs(mx) - std::abs(minx) < std::numeric_limits<double>::epsilon()
            && std::abs(my) - std::abs(miny) < std::numeric_limits<double>::epsilon();
    }
};

inline std::ostream& operator<<(std::ostream& ss, const Vec2& v) {
    return ss << v.x << "," << v.y;
}
inline std::ostream& operator<<(std::ostream& ss, const Vec2d& v) {
    return ss << v.x << "," << v.y;
}

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
