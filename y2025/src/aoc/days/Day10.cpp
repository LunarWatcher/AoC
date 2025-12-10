#include "Day10.hpp"
#include "common/loader/Loader.hpp"
#include <queue>

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

        std::queue<std::pair<uint64_t, std::vector<bool>>> q {
            {
                {0, sourceIndicators},
            }
        };


        std::optional<std::pair<uint64_t, std::vector<bool>>> match;
        while (q.size()) {
            auto [ click, currState ] = q.front();
            q.pop();

            ++click;

            for (auto& button : buttons) {
                auto state = currState;
                button.click(state);
                bool hasValue = false;
                for (auto val : state) {
                    hasValue = hasValue || val;
                }

                if (!hasValue) {
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
    return 0ull;
}

}
