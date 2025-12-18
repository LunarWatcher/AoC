#include "Day13.hpp"
#include "common/loader/Loader.hpp"
#include "common/math/Vec.hpp"

namespace aoc2019 {

void Day13::parse() {
    this->prog = {
        common::Loader::loadSingleLineIntVector<int64_t>(
            this->path
        )
    };
}

common::Output Day13::part1() {
    IntCode computer(this->prog);

    while (true) {
        computer.run();
        if (computer.hasHalted()) {
            break;
        }
    }

    uint64_t sum = 0;
    for (size_t i = 2; i < computer.output.data.size(); i += 3) {
        if (computer.output.data.at(i) == static_cast<int>(TileType::BLOCK)) {
            ++sum;
        }
    }
    return sum;
}

common::Output Day13::part2() {
    IntCode computer(this->prog);
    computer.recode({{ 0, 2 }});

    common::Vec2 ball(0, 0);
    common::Vec2 paddle(0, 0);
    uint64_t score = 0;
    while (true) {
        computer.input.onOverflow = 
            (ball.x > paddle.x) ? 1 : (ball.x < paddle.x ? -1 : 0);
        computer.run();
        if (computer.hasHalted()) {
            break;
        }
        computer.run(); computer.run();

        auto x = *(computer.output.data.end() - 3);
        auto y = *(computer.output.data.end() - 2);
        auto val = *(computer.output.data.end() - 1);
        if (x == -1 && y == 0) {
            score = std::max<uint64_t>(score, (uint64_t) val);
            continue;
        }

        auto tile = static_cast<TileType>(val);

        if (tile == TileType::BALL) {
            ball.x = x;
            ball.y = y;
        } else if (tile == TileType::HORIZONTAL_PADDLE) {
            paddle.x = x;
            paddle.y = y;
        }

    }
    return score;
}

}
