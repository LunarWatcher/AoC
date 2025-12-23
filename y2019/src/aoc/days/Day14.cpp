#include "Day14.hpp"
#include "common/loader/Loader.hpp"
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <unordered_map>

namespace aoc2019 {

void Day14::parse() {
    auto lines = common::Loader::getRawLinesForProcessing(this->path);

    Reagents reagents;

    for (auto& line : lines) {
        auto spaces = stc::string::split(line, ',');

        for (size_t i = 0; i < spaces.size(); ++i) {
            auto& line = spaces.at(i);
            if (i == spaces.size() - 1) {
                // Last component
                auto split = line.find('=');
                int64_t quantity = std::stoll(line.substr(split + 2));
                auto product = line.substr(line.rfind(' ') + 1);

                reagents.addReaction(line.substr(0, split - 1));
                reagents.productQuantity = quantity;
                // Each reaction result only appears at most once as a result.
                this->reactions[product] = reagents;
                reagents = {};
            } else {
                reagents.addReaction(
                    line
                );
            }
        }
    }
}

std::unordered_map<std::string, int64_t> Day14::collapse(
    const std::string& next,
    int64_t desired,
    std::unordered_map<std::string, int64_t>& reserve
) {
    const auto& nextReagent = this->reactions.at(next);
    auto& r = reserve[next];
    if (r > 0) {
        auto m = std::min(r, desired);
        r -= m;
        desired -= m;
        if (m == 0) {
            return {};
        }
    }

    int64_t multiples = std::ceil(
        double(desired) / double(nextReagent.productQuantity)
    );
    reserve[next] += multiples * nextReagent.productQuantity - desired;

    std::unordered_map<std::string, int64_t> totals;
    for (auto& [ reaction, needed ] : nextReagent.reagents) {
        int64_t total = needed * multiples;
        int64_t usable = std::min(total, reserve[reaction]);
        if (usable != 0) {
            total -= usable;
            reserve[reaction] -= usable;
        }
        totals[reaction] += total;
    }
    return totals;
}

int64_t Day14::getMinFuel(int64_t fuel) {
    std::unordered_map<std::string, int64_t>
        cache,
        needed;
    std::queue<std::pair<std::string, int64_t>> q;
    q.push({"FUEL", fuel});

    while (!q.empty()) {
        auto [next, quant] = q.front();
        q.pop();
        if (quant == 0) {
            continue;
        }

        auto components = collapse(
            next,
            quant,
            cache
        );
        // For whatever moronic fucking reason, auto& [reaction, needed] makes the compiler whine
        for (auto& reaction : components) {
            needed[reaction.first] += reaction.second;
            // std::cout << reaction.first << " " << reaction.second << std::endl;

            if (reaction.first != "ORE") {
                q.push({ reaction.first, reaction.second });
            }
        }
    }
    // for (auto& [k, v] : cache) {
    //     std::cout << k << " " << v << std::endl;
    // }
    return needed.at("ORE");
}

common::Output Day14::part1() {
    return getMinFuel(1);
}

common::Output Day14::part2() {
    int64_t low = int64_t(1e12) / getMinFuel(1);
    int64_t high = 1000 * low;
    while (high - low > 1) {
        int64_t val = low + (high - low) / 2;
        auto fuelForValue = getMinFuel(val);
        if (fuelForValue > (int64_t) 1e12)
            high = val;
        else low = val;
    }

    return low;
}

}
