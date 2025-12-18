#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <ostream>
namespace common {

struct Direction {
    int dir;

    explicit Direction(int dir) {
        this->dir = dir;
    }

    void constrain() {
        if (dir < 0) {
            this->dir = 3;
        } else if (dir > 3) {
            this->dir = 0;
        }
    }

    int64_t x() const {
        if (dir == 1) { // Right
            return  1;
        } else if (dir == 3) { // left
            return -1;
        }
        return 0;
    }
    int64_t y() const {
        if (dir == 0) { // up
            // TODO: this is inverted by requirement of 2019d11p2
            // I don't understand what part of the setup necessitates this
            // maybe 2019d11p2 just is on an inverted axis?
            return  -1;
        } else if (dir == 2) { // down
            return 1;
        }
        return 0;
    }

    void operator+=(int val) {
        dir += val;
        constrain();
    }
};

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

    Vec2& operator+=(const Direction& dir) {
        x += dir.x();
        y += dir.y();
        return *this;
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
        return 
            std::signbit(other.x) == std::signbit(x)
            && std::signbit(other.y) == std::signbit(y)
            && std::abs(x - other.x) < std::numeric_limits<double>::epsilon()
            && std::abs(y - other.y) < std::numeric_limits<double>::epsilon();
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

    Vec3& operator+=(const Vec3& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }
    Vec3& operator-=(const Vec3& other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Vec3 operator-() const {
        return {
            -this->x,
            -this->y,
            -this->z
        };
    }
    Vec3 operator-(const Vec3& other) const {
        return {
            this->x - other.x,
            this->y - other.y,
            this->z - other.z
        };
    }

    bool operator==(const Vec3& other) const {
        return 
            this->x == other.x
            && this->y == other.y 
            && this->z == other.z;
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

inline std::ostream& operator<<(std::ostream& ss, const Vec2& v) {
    return ss << v.x << "," << v.y;
}
inline std::ostream& operator<<(std::ostream& ss, const Vec3& v) {
    return ss << v.x << "," << v.y << "," << v.z;
}
inline std::ostream& operator<<(std::ostream& ss, const Vec2d& v) {
    return ss << v.x << "," << v.y;
}

}
