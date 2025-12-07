#include "Day5.hpp"
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
    computer.run({ .data = { 1 } });
    return computer.diagnostic();
}

uint64_t Day5::part2() {
    computer.run({ .data = { 5 } });
    return computer.diagnostic();
}

}
