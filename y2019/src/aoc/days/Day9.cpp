#include "Day9.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2019 {

void Day9::parse() {
    this->prog = {
        common::Loader::loadSingleLineIntVector<int64_t>(
            this->path
        )
    };
}

common::Output Day9::part1() {
    IntCode computer(this->prog);
    computer.input.push(1);

    computer.run();

    return computer.diagnostic();
}

common::Output Day9::part2() {
    IntCode computer(this->prog);
    computer.input.push(2);

    computer.run();

    return computer.diagnostic();
}

}
