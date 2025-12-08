#include "Day5.hpp"
#include "aoc/intcode/IntCode.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2019 {

void Day5::parse() {
    this->computer = IntCode {
        common::Loader::loadSingleLineIntVector<int64_t>(
            this->path
        )
    };
}

uint64_t Day5::part1() {
    computer.cacheWorkingMemory = true;
    StdStream s { .data = { 1 } };
    Program state;
    computer.runUntilHalted(&s, &state);

    return computer.diagnostic();
}

uint64_t Day5::part2() {
    computer.recode({});
    computer.cacheWorkingMemory = false;
    StdStream s { .data = { 5 } };
    computer.run(&s);
    return computer.diagnostic();
}

}
