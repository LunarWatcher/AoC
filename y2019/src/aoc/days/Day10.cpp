#include "Day10.hpp"
#include "common/loader/Loader.hpp"
#include "stc/Math.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <numbers>

namespace aoc2019 {

void Day10::parse() {
    this->asteroids = common::Loader::loadMapAsObjectList<common::Vec2d>(this->path, [](const auto& ch) {
        return ch == '#';
    });

}

common::Output Day10::part1() {
    uint64_t sum = 0;
    for (size_t i = 0; i < asteroids.size(); ++i) {
        size_t localSum = 0;
        auto& sourceAsteroid = this->asteroids.at(i);
        std::vector<common::Vec2d> relativeVectors;
        for (size_t j = 0; j < asteroids.size(); ++j) {
            if (i == j) {
                continue;
            }
            auto& targetAsteroid = this->asteroids.at(j);

            auto norm = (sourceAsteroid - targetAsteroid).div();

            if (std::find(relativeVectors.begin(), relativeVectors.end(), norm) != relativeVectors.end()) {
                continue;
            }
            ++localSum;
            relativeVectors.push_back(norm);
        }
        if (localSum > sum) {
            sum = localSum;
            this->origin = sourceAsteroid;
        }
    }
    return sum;
}

common::Output Day10::part2() {
    if (this->origin == common::Vec2d{ 0, 0 }) {
        [[unlikely]] // Only in tests
        part1();
    }
    auto asteroids = this->asteroids;

    std::vector<common::Vec2d> relativeVectors;
    auto uppies = common::Vec2d(0, 1);
    for (size_t j = 0; j < asteroids.size(); ++j) {
        auto& targetAsteroid = this->asteroids.at(j);
        if (targetAsteroid == origin) {
            continue;
        }

        auto norm = (origin - targetAsteroid);
        relativeVectors.push_back(norm);
    }
    // We now have a set of relative vectors to all the other asteroids. We now need to sort those
    std::sort(asteroids.begin(), asteroids.end(), [&](const auto& a, const auto& b) {

        auto angleA = a.angle(uppies);
        auto angleB = b.angle(uppies);
        if (angleA > angleB) {
            return true;
        } else if (angleA < angleB) {
            return false;
        }

        return a.euclidiean(this->origin) < b.euclidiean(this->origin);
    });

    return (uint64_t) asteroids.at(200).x * 100 + (uint64_t) asteroids.at(200).y;
}

}
