#include "Day15.hpp"
#include "aoc/intcode/IntCode.hpp"
#include "common/loader/Loader.hpp"
#include "common/math/Vec.hpp"
#include <unordered_set>

namespace aoc2019 {

void Day15::parse() {
    this->prog = {
        common::Loader::loadSingleLineIntVector<int64_t>(
            this->path
        )
    };
}

common::Output Day15::part1() {
    IntCode computer(this->prog);

    uint64_t distance = 0;
    int64_t lastMove = 1;
    std::unordered_map<uint64_t, uint64_t> visited{
        {
            ((uint64_t) 100 << 32) | 100, 0
        }
    };

    common::Vec2 dir(100,100);
    while (true) {
        computer.input.push(lastMove);
        computer.run();
        auto diag = computer.diagnostic();
        if (diag == 2) {
            ++distance;
            break;
        } else if (diag == 0) {
            lastMove = right(lastMove);
            continue;
        }
        if (lastMove == 1) {
            dir.y += 1;
        } else if (lastMove == 2) {
            dir.y -= 1;
        } else if (lastMove == 3) {
            dir.x += 1;
        } else {
            dir.x -= 1;
        }
        // std::cout << dir << std::endl;
        auto& v = visited[((uint64_t) dir.x << 32) | (uint64_t) dir.y];
        ++distance;
        if (v == 0 || v > distance) {
            v = distance;
        } else if (distance > v){
            // we have returned from a side entrance, so we can ignore it
            distance = v;
        }
        lastMove = left(lastMove);
    }

    return distance;
}

common::Output Day15::part2() {
    uint64_t sum = 0;

    return sum;
}

}
