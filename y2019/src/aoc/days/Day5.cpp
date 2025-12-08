#include "Day5.hpp"
#include "aoc/intcode/IntCode.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2019 {

void Day5::parse() {
    this->prog = {
        common::Loader::loadSingleLineIntVector<int64_t>(
            this->path
        )
    };
}

common::Output Day5::part1() {
    IntCode computer(prog);
    computer.input.push(1);
    Program state;
    computer.runUntilHalted();

    return computer.diagnostic();
}

common::Output Day5::part2() {
    IntCode computer(prog);
    computer.input.push(5);
    computer.run();
    return computer.diagnostic();
}

}
