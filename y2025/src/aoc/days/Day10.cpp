#include "Day10.hpp"
#include "common/loader/Loader.hpp"
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
    LinAlgSystem& sys,
    const std::vector<Button>& buttons
) {
    // Assemble the system
    for (size_t i = 0; i < buttons.size(); ++i) {
        auto& button = buttons.at(i);
        for (size_t j = 0; j < button.maskAsArray.size(); ++j) {
            sys.mat.at(j).at(i) = button.maskAsArray.at(j) ? 1 : 0;
        }
    }
}

common::Output Day10::part2() {
    uint64_t sum = 0;
    return sum;

    for (auto& [_, buttons, joltages] : machines) {
        LinAlgSystem system {
            .buttonCount = buttons.size(),
            .solutionsCol = joltages
        };
        assembleSystem(system, buttons);

        system.gaussEliminate();
        auto res = system.solve(buttons);
        sum += std::accumulate(
            res.begin(),
            res.end(),
            0ll
        );
    }
    
    return sum;
}

}
