#include "Day12.hpp"
#include "common/loader/Loader.hpp"
#include "common/math/Vec.hpp"
#include <iostream>
#include <numeric>

namespace aoc2019 {

void Day12::parse() {
    std::ifstream f = common::Loader::open(this->path);

    
    char ch;
    while (f >> ch) {
        if (ch == '=') {
            common::Vec3 v;
            f >> v.x;
            f.ignore(4);
            f >> v.y;
            f.ignore(4);
            f >> v.z;
            f.ignore(2);

            this->moons.push_back({v});
        }
    }
}

void Day12::simulate(
    std::vector<Moon>& state
) {
    for (size_t i = 0; i < state.size() - 1; ++i) {
        auto& moon = state.at(i);
        for (size_t j = i + 1; j < state.size(); ++j) {
            auto& pair = state.at(j);
            auto delta = moon.position - pair.position;
            // moon.x > pair.x => delta.x > 0
            // delta.x > 0 => moon.x -= 1, pair.x += 1
            auto sx = delta.x == 0 ? 0 : (std::signbit(delta.x) ? -1 : 1);
            auto sy = delta.y == 0 ? 0 : (std::signbit(delta.y) ? -1 : 1);
            auto sz = delta.z == 0 ? 0 : (std::signbit(delta.z) ? -1 : 1);

            auto signs = common::Vec3 { sx, sy, sz };
            moon.velocity -= signs;
            pair.velocity += signs;
        }
    }

    for (auto& moon : state) {
        moon.position += moon.velocity;
    }
}

common::Output Day12::part1() {
    auto state = this->moons;
    for (size_t i = 0; i < 1000; ++i) {
        simulate(state);
    }

    uint64_t sum = 0;
    for (auto& moon : state) {
        sum += (
            std::abs(moon.position.x) 
            + std::abs(moon.position.y)
            + std::abs(moon.position.z)
        ) * (
            std::abs(moon.velocity.x) 
            + std::abs(moon.velocity.y)
            + std::abs(moon.velocity.z)
        );
    }

    return sum;
}

common::Output Day12::part2() {
    auto state = this->moons;
    std::vector<common::Vec3> initialPositions;

    int64_t it = 1;
    common::Vec3 coordCyclesRepeated(0, 0, 0);

    while (
        coordCyclesRepeated.x == 0
        || coordCyclesRepeated.y == 0
        || coordCyclesRepeated.z == 0
    ) {
        simulate(state);

        bool x = true, y = true, z = true;
        for (size_t i = 0; i < state.size(); ++i) {
            if (coordCyclesRepeated.x == 0 && state.at(i).velocity.x == 0) {
                if (this->moons.at(i).position.x != state.at(i).position.x) {
                    x = false;
                }
            } else {
                x = false;
            }
            if (coordCyclesRepeated.y == 0 && state.at(i).velocity.y == 0) {
                if (this->moons.at(i).position.y != state.at(i).position.y) {
                    y = false;
                }
            } else {
                y = false;
            }
            if (coordCyclesRepeated.z == 0 && state.at(i).velocity.z == 0) {
                if (this->moons.at(i).position.z != state.at(i).position.z) {
                    z = false;
                }
            } else {
                z = false;
            }
        }

        if (x) {
            coordCyclesRepeated.x = it;
        }
        if (y) {
            coordCyclesRepeated.y = it;
        }
        if (z) {
            coordCyclesRepeated.z = it;
        }

        ++it;
    }

    return std::lcm(
        (uint64_t) coordCyclesRepeated.x,
        std::lcm(
            (uint64_t) coordCyclesRepeated.y, 
            (uint64_t) coordCyclesRepeated.z
        )
    );
}

}
