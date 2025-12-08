#include "Day7.hpp"
#include "aoc/intcode/IntCode.hpp"
#include "common/loader/Loader.hpp"
#include <algorithm>

namespace aoc2019 {

void Day7::parse() {
    this->computer = IntCode {
        common::Loader::loadSingleLineIntVector<int64_t>(
            this->path
        )
    };
}

uint64_t Day7::part1() {
    std::vector<int64_t> phases = {0, 1, 2, 3, 4};
    this->computer.cacheWorkingMemory = true;

    int64_t out = 0;
    do {
        this->computer.recode({});
        int64_t signal = 0;
        for (auto val : phases) {
            Program p;
            auto in = StdStream {{ val, signal }};
            this->computer.run(&in, &p);
            signal = this->computer.diagnostic();
        }
        out = std::max(out, signal);
    } while (std::next_permutation(phases.begin(), phases.end()));
    return out;
}

uint64_t Day7::part2() {
    std::vector<int64_t> phases = {5, 6, 7, 8, 9};

    this->computer.cacheWorkingMemory = true;

    int64_t out = 0;
    do {
        this->computer.recode({});
        std::vector<Program> states;
        states.resize(5);

        std::vector<StdStream> streams;
        streams.reserve(5);
        for (size_t i = 0; i < 5; ++i) {
            streams.push_back(StdStream {
                {  phases.at(i)  }
            });
        }

        int64_t signal = 0;
        while (!computer.hasHalted()) {
            for (size_t i = 0; i < phases.size(); ++i) {
                auto& stream = streams.at(i);
                stream.push(signal);

                this->computer.run(
                    &stream,
                    &states.at(i)
                );
                signal = this->computer.diagnostic();
            }
        }
        computer.recode({});
        out = std::max(out, signal);
    } while (std::next_permutation(phases.begin(), phases.end()));
    return out;
}

}
