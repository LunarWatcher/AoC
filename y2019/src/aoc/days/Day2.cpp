#include "Day2.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2019 {

void Day2::parse() {
    this->computer = IntCode {
        common::Loader::loadSingleLineIntVector<int64_t>(
            this->path
        )
    };
}

uint64_t Day2::part1() {
    computer.recode({
        {1, 12},
        {2, 2}
    });
    return computer.run();
}

uint64_t Day2::part2() {
    for (int64_t n = 0; n < 99; ++n) {
        for (int64_t v = 0; v < 99; ++v) {
            computer.recode({
                {1, n},
                {2, v}
            });
            if (computer.run() == 19690720ll) {
                return 100 * n + v;
            }
        }
    }
    throw std::runtime_error("Nope");
}

}
