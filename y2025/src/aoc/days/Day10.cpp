#include "Day10.hpp"
#include "common/loader/Loader.hpp"
#include <bitset>
#include <common/debug/Formatters.hpp>
#include <limits>
#include <queue>
#include <set>
#include <type_traits>
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

uint64_t Day10::recursivelyPressButtons(
    const std::unordered_map<size_t, std::set<std::set<size_t>>>& parityPaths,
    const std::vector<Button>& buttons,
    const std::vector<int64_t>& joltages
) {
    bool isDone = true;
    for (auto& joltage : joltages) {
        if (joltage < 0) {
            return std::numeric_limits<uint64_t>::max();
        } else if (joltage != 0) {
            isDone = false;
        }
    }
    if (isDone) {
        return 0;
    }
    size_t currParity = 0;
    for (size_t i = 0; i < joltages.size(); ++i) {
        currParity |= ((size_t) (joltages.at(i) % 2 != 0)) << i;
    }
    std::cout << joltages << std::endl;
    std::cout << parityPaths.at(currParity) << std::endl;
    auto& paths = parityPaths.at(currParity);
    uint64_t out = std::numeric_limits<uint64_t>::max();
    for (auto& path : paths) {
        auto newJoltages = joltages;
        // if (buttons.at(btnIdx).maxPresses(newJoltages) == 0) {
        //     goto bad;
        // }
        for (auto& btnIdx : path) {
            if (buttons.at(btnIdx).maxPresses(joltages) == 0) {
                goto bad;
            }
            buttons.at(btnIdx).click(newJoltages, 1);
        }
        {
            auto min = std::min_element(
                newJoltages.begin(), newJoltages.end()
            );
            auto max = std::max_element(
                newJoltages.begin(), newJoltages.end()
            );

            // TODO: This should not be necessary: maxPresses() is supposed to guard from negative clicks, but it isn't.
            if (*min < 0) {
                continue;
            } else if (*min == 0 && *max == 0) {
                out = std::min(out, path.size());
                continue;
            }

            std::cout << "Dividing" << newJoltages << std::endl;
            size_t mult = 1;
            if (*min > 0) {
                bool hasMore = true;
                while (hasMore) {
                    for (auto& joltage : newJoltages) {
                        joltage /= 2;
                        if (joltage % 2 != 0) {
                            hasMore = false;
                        }
                    }
                    mult *= 2;
                }
            }
            // std::cout << "Recurse " << newJoltages << " from click " << path << std::endl;
            auto val = recursivelyPressButtons(
                parityPaths,
                buttons,
                newJoltages
            );
            if (val == std::numeric_limits<uint64_t>::max()) {
                return val;
            }
            out = std::min(out, mult * val + path.size());
        }
bad:
    }
    return out;
}
std::unordered_map<size_t, std::set<std::set<size_t>>> Day10::findAllPaths(
    const std::vector<Button>& buttons
) {
    size_t possibilities = 1;

    for (size_t i = 0; i < buttons.size(); ++i) {
        possibilities *= 2;
    }
    
    std::unordered_map<size_t, std::set<std::set<size_t>>> out;
    // We skip i = 0 because 0 buttons enabled is pointless
    for (size_t i = 1; i < possibilities; ++i) {
        std::set<size_t> enabled;
        for (size_t j = 0; j < buttons.size(); ++j) {
            if ((i >> j) % 2 == 1) {
                enabled.insert(j);
            }
        }
        size_t state = 0;
        for (auto& j : enabled) {
            buttons.at(j).click(state);
        }

        out[state].insert(enabled);
    }

    return out;
}

common::Output Day10::part2() {
    uint64_t sum = 0;

    size_t machineIdx = 0;
    for (const auto& [_, buttons, joltages] : machines) {
        std::cout << "Now processing " << machineIdx << std::endl;

        auto paths = findAllPaths(
            buttons
        );
        auto res = recursivelyPressButtons(
            paths,
            buttons,
            joltages
        );
        std::cout << "ADD " << res << std::endl;
        if (res == std::numeric_limits<uint64_t>::max()) {
            throw std::runtime_error("Idiot");
        }
        sum += res;

        ++machineIdx;
    }
    
    return sum;
}

}
