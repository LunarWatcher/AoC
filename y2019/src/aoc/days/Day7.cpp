#include "Day7.hpp"
#include "aoc/intcode/IntCode.hpp"
#include "common/loader/Loader.hpp"
#include <algorithm>

namespace aoc2019 {

void Day7::parse() {
    this->prog = {
        common::Loader::loadSingleLineIntVector<int64_t>(
            this->path
        )
    };
}

common::Output Day7::part1() {
    std::vector<int64_t> phases = {0, 1, 2, 3, 4};

    int64_t out = 0;
    do {
        int64_t signal = 0;
        for (auto val : phases) {
            IntCode computer{this->prog};
            computer.input.push(val);
            computer.input.push(signal);

            computer.run();
            signal = computer.diagnostic();
        }
        out = std::max(out, signal);
    } while (std::next_permutation(phases.begin(), phases.end()));
    return out;
}

common::Output Day7::part2() {
    std::vector<int64_t> phases = {5, 6, 7, 8, 9};


    int64_t out = 0;
    do {
        std::vector<IntCode> states{
            5,
            this->prog
        };


        for (size_t i = 0; i < 5; ++i) {
            states.at(i).input.push(phases.at(i));
        }

        int64_t signal = 0;
        while (!states.at(0).hasHalted()) {
            for (size_t i = 0; i < phases.size(); ++i) {
                auto& computer = states.at(i);
                computer.input.push(signal);
                computer.run();
                signal = computer.diagnostic();
            }
        }
        out = std::max(out, signal);
    } while (std::next_permutation(phases.begin(), phases.end()));
    return out;
}

}
