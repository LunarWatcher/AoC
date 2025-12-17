#include "Day10.hpp"
#include <common/debug/Formatters.hpp>
#include "common/loader/Loader.hpp"
#include "common/math/VecN.hpp"
#include <limits>
#include <thread>
#include <numeric>
#include <queue>
#include <unordered_set>

namespace aoc2025 {

void Day10::parse() {
    this->machines = common::Loader::loadVector<UselessMachine>(
        this->path,
        [](const auto& str) { return UselessMachine { str }; }
    );
}

common::Output Day10::part1() {
    uint64_t sum = 0;

    for (auto& [sourceIndicators, buttons, _] : machines) {

        std::queue<std::pair<uint64_t, size_t>> q {
            {
                {0, sourceIndicators},
            }
        };

        std::unordered_set<size_t> searchedStates;
        std::optional<std::pair<uint64_t, size_t>> match;
        while (q.size()) {
            auto [ click, currState ] = q.front();
            q.pop();

            ++click;

            for (auto& button : buttons) {
                auto state = currState;
                button.click(state);
                if (searchedStates.insert(state).second == false) {
                    continue;
                }

                if (state == 0) {
                    match = { click, state };
                    goto done;
                }


                q.push({ click, state });
            }


        }

        if (!match.has_value()) {
            throw std::runtime_error("Bad girl");
        }
done:;
        sum += match->first;

    }
    
    return sum;
}

void Day10::assembleSystem(
    common::EqSystem& sys,
    const std::vector<Button>& buttons
) {
    // Assemble the system
    for (size_t i = 0; i < buttons.size(); ++i) {
        auto& button = buttons.at(i);
        for (size_t j = 0; j < button.maskAsArray.size(); ++j) {
            sys(j, i) = (int64_t) button.maskAsArray.at(j);
        }
    }
}

common::Output Day10::part2() {
    uint64_t sum = 0;

    size_t processed = 0;
    for (auto& [_, buttons, joltages] : machines) {
        std::cout << "Now running " << processed++ << std::endl;
        common::EqSystem system {
            buttons.size(),
            joltages
        };
        assembleSystem(system, buttons);

        std::cout << system << "\n";
        system.gaussEliminate();
        std::cout << system << "\n\n";
        std::vector<int64_t> maxPresses;

        for (auto& button : buttons) {
            auto max = std::numeric_limits<int64_t>::max();

            for (size_t i = 0; i < joltages.size(); ++i) {
                if (button.is(i)) {
                    max = std::min(
                        max,
                        joltages.at(i)
                    );
                }
            }

            maxPresses.push_back(max);
        }

        auto res = system.solveForSmallestTotalWithMinConstraints(
            0,
            maxPresses
        );
        auto presses = std::accumulate(
            res.begin(),
            res.end(),
            0ll
        );

        std::cout << "System requires " << presses << std::endl;
        sum += presses;
    }
    
    return sum;
}

}
