#include "Day10.hpp"
#include "common/loader/Loader.hpp"
#include <cstdint>
#include <limits>
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

bool Day10::isButtonEnabled(
    __uint128_t joltages,
    size_t joltageCounts,
    const Button& b
) {
    for (size_t i = 0; i < joltageCounts; ++i) {
        if (((joltages >> (9 * i)) % 512) == 0 && b.maskAsArray.at(i)) {
            // At least one of the targets are done
            return false;
        }
    }
    return true;
}

#ifdef HAS_128_BIT_INT
void Day10::directedDfsAStarThing(
    const SearchContext& context,
    SystemState& systemState
) {

    for (size_t i = 0; i < systemState.buttons.size(); ++i) {
        if (context.enabledButtons.at(i) == false) {
            continue;
        }
        auto newContext = context;
        auto& button = systemState.buttons.at(i);
        newContext.path += encode(1, i);
        int64_t currButtonPresses = 0;
        for (size_t i = 0; i < systemState.buttons.size(); ++i) {
            currButtonPresses += (int64_t) decode(newContext.path, i);
        }

        // If the current total cost is greater than our minimal cost, this path is fucked and cannot be
        // recovered.
        if (currButtonPresses >= systemState.minCost - 1) {
            continue;
        }

        if (!systemState.visited.insert(newContext.path).second) {
            // std::cout << "Discarded" << std::endl;
            // for (size_t j = 0; j < systemState.buttons.size(); ++j) {

            //     std::cout << "\tbutton " << j << ": "
            //         << (int64_t) ((newContext.path >> (9 * j)) % 512);

            // }
            // std::cout << std::endl;
            continue;
        }

        newContext.accumulatedClicks += button.enabled;
        if (newContext.accumulatedClicks > systemState.systemJoltage) {
            // Abort search; we have violated the total number of presses the system can have
            continue;
        }

        button.click(newContext.joltages);

        // std::cout << newContext.currJoltages << std::endl;
        for (size_t i = 0; i < systemState.joltageCounts; ++i) {
            if (decode(newContext.joltages, i) != 0) {
                goto notDone;
            }
        } /* else */ {
            // The min is probably redundant, but if currCost == systemState.minCost - 1, 
            // these two costs are equal
            systemState.minCost = std::min(currButtonPresses, systemState.minCost);
            continue;
        }
notDone:
        newContext.buttonPresses.at(i) += 1;
        if (newContext.buttonPresses.at(i) > 512) {
            throw std::runtime_error("Something has gone very wrong");
        }

        // This constraint identifies whether or not it's possible for the path to continue. 
        // If the minimum cost of actuating a button exceeds that of the system, there is no way forward and we
        // abort.
        for (size_t j = 0; j < systemState.joltageCounts; ++j) {
            auto requiredPresses = decode(newContext.joltages, j);

            auto minCost = systemState.minCostForJoltage.at(j);
            if ((int64_t) requiredPresses * minCost > systemState.systemJoltage - newContext.accumulatedClicks) {
                goto bad;
            }
        }
        goto good;
bad:
        continue;
good:

        // Update button states before recursing
        for (size_t j = 0; j < systemState.buttons.size(); ++j) {
            auto enabled = newContext.enabledButtons.at(j);
            // Skip if not enabled: if it's disabled, it can never be re-enabled, so we don't need to check
            if (!enabled) {
                continue;
            }
            enabled = newContext.buttonPresses.at(j) < systemState.constraints.at(j).maxPresses
                && isButtonEnabled(
                    newContext.joltages,
                    systemState.joltageCounts,
                    systemState.buttons.at(j)
                );
        }

        directedDfsAStarThing(
            newContext,
            systemState
        );
    }
}
#endif

common::Output Day10::part2() {
#ifdef HAS_128_BIT_INT
    uint64_t sum = 0;

    auto start = std::chrono::system_clock::now();
    size_t machineIdx = 0;
    for (auto& [_, buttons, joltages] : machines) {
        std::cout << "New machine " << machineIdx++ << " started at t=" << std::format(
            "{}ms",
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count()
        ) << std::endl;
        std::vector<std::vector<size_t>> joltageToButtonMap(joltages.size());

        std::vector<ButtonConstraints> constraints;

        int64_t systemJoltage = 0;

        std::vector<int64_t> minCostForJoltage(joltages.size(), std::numeric_limits<int64_t>::max());
        std::vector<std::pair<size_t, int64_t>> transformedJoltages;
        __uint128_t encodedJoltages = 0;
        for (size_t i = 0; i < joltages.size(); ++i) {
            auto joltage = joltages.at(i);
            systemJoltage += joltage;
            encodedJoltages += encode(joltage, i);

            transformedJoltages.push_back({i, joltage});
        }

        // std::sort(
        //     transformedJoltages.begin(),
        //     transformedJoltages.end(),
        //     [](const auto& a, const auto& b) {
        //         return a.second < b.second;
        //     });


        for (size_t btnIdx = 0; btnIdx < buttons.size(); ++btnIdx) {
            auto& button = buttons.at(btnIdx);
            auto maxJoltage = std::numeric_limits<int64_t>::max();
            for (size_t i = 0; i < button.maskAsArray.size(); ++i) {
                if (button.maskAsArray.at(i)) {
                    maxJoltage = std::min(
                        maxJoltage,
                        joltages.at(i)
                    );
                    joltageToButtonMap.at(i).push_back(btnIdx);
                    auto& minCost = minCostForJoltage.at(i);
                    minCost = std::min(minCost, button.enabled);
                }
            }

            constraints.push_back({
                maxJoltage
            });
        }

        SystemState systemState {
            .systemJoltage = systemJoltage,
            .joltageToButtonMap = joltageToButtonMap,
            .buttons = buttons,
            .constraints = constraints,
            .minCostForJoltage = minCostForJoltage,
            .joltageCounts = joltages.size(),
            .visited = {},
        };

        directedDfsAStarThing({
            .joltages = encodedJoltages,
            .enabledButtons = std::vector<bool>(buttons.size(), true),
            .buttonPresses = std::vector<int64_t>(buttons.size(), 0),
        }, systemState);
        std::cout << "\tCost: " << systemState.minCost << std::endl;
        sum += systemState.minCost;
    }
    
    return sum;
#else
    return "Your platform/compiler does not support __int128_t, and cannot run this part";
#endif
}

}
