#include "Day10.hpp"
#include "common/loader/Loader.hpp"
#include <cstdint>
#include <limits>
#include <queue>
#include <unordered_set>
#include <Eigen/Dense>

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

common::Output Day10::part2() {
    using Fuck = Eigen::Index;
    uint64_t sum = 0;
    for (auto& [_, buttons, joltages] : machines) {
        Eigen::MatrixXd A(
            (Fuck) joltages.size(), 
            (Fuck) buttons.size()
        );
        A.setZero();
        Eigen::VectorXd b(
            (Fuck) joltages.size()
        );
        b.setZero();
        for (size_t j = 0; j < joltages.size(); ++j) {
            b((Fuck) j) = (double) joltages.at(j);
            for (size_t i = 0; i < buttons.size(); ++i) {
                auto& button = buttons.at(i);
                A((Fuck) j, (Fuck) i) = (double) button.is(j);
            }
        }
        auto fuckKnows = 
            A
            .fullPivLu();
        decltype(b) intermediateResult = fuckKnows.solve(b);
        
        // std::cout << kernel << std::endl << std::endl;
        // std::cout << b << std::endl << std::endl;
        // std::cout << A << std::endl << std::endl;
        // std::cout << intermediateResult << std::endl << std::endl;
        // std::cout << "Done: " << std::endl << intermediateResult << std::endl << std::endl;
        for (auto& r : intermediateResult) {
            sum += (int64_t) r;
        }

    }
    return sum;
}

}
