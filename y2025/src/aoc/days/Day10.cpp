#include "Day10.hpp"
#include <common/debug/Formatters.hpp>
#include "common/loader/Loader.hpp"
#include "common/math/VecN.hpp"
#include <limits>
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
        // common::EqSystem system {
        //     buttons.size(),
        //     joltages
        // };
        // assembleSystem(system, buttons);

        // system.gaussEliminate();
        // std::cout << system << "\n\n";
        // auto res = system.solveForSmallestTotalWithMinConstraints(
        //     0
        // );
        // auto presses = std::accumulate(
        //     res.begin(),
        //     res.end(),
        //     0ll
        // );

        // std::cout << "System requires " << presses << std::endl;
        // sum += presses;
        
        std::cout << joltages << std::endl;
        std::vector<common::VecN<int64_t>> buttonVectors;
        for (auto& button : buttons) {
            std::vector<int64_t> values(joltages.size(), 0);

            for (size_t i = 0; i < joltages.size(); ++i) {
                if (button.is(i)) {
                    values.at(i) = 1;
                }
            }

            buttonVectors.push_back({
                values
            });
        }

        common::VecN<int64_t> target {
            joltages
        };
        uint64_t maxJoltage = std::accumulate(
            joltages.begin(), joltages.end(), 0ll
        );

        auto cmp = [&](const SearchData& a, const SearchData& b) {
            if (a.position.values.size() != b.position.values.size()) {
                [[unlikely]]
                return false;
            }
            return 
                a.position.euclidean(target) > b.position.euclidean(target)
                || a.buttonPresses < b.buttonPresses;
        };
        std::priority_queue<SearchData, std::vector<SearchData>, decltype(cmp)> q(cmp);

        for (auto& vector : buttonVectors) {
            // std::cout << "APPEND " << vector.values << std::endl;
            q.push(SearchData {
                .position = vector,
                .buttonPresses = 1
            });
        }

        uint64_t min = std::numeric_limits<uint64_t>::max();
        // std::cout << "NEW" << std::endl;

        while (q.size() > 0) {
            auto [ position, currPresses ] = q.top();
            q.pop();


            if (position == target) {
                min = std::min(currPresses, min);
                break;
            }

            auto currDist = position.euclidean(target);

            for (size_t i = 0; i < buttonVectors.size(); ++i) {
                auto& next = buttonVectors.at(i);
                auto presses = currPresses + 1;
                if (presses > min || presses > maxJoltage) {
                    continue;
                }

                auto newPos = position + next;

                if (newPos.euclidean(target) > currDist) {
                    continue;
                }

                for (size_t i = 0; i < target.values.size(); ++i) {
                    if (newPos.values.at(i) > target.values.at(i)) {
                        goto bad;
                    }
                }
                
                q.push({newPos, presses });
bad:
            }
        }

        // std::cout << "ADD " << min << std::endl;
        sum += min;
    }
    
    return sum;
}

}
