#pragma once

#include "stc/StringUtil.hpp"
#include <cassert>
#include <common/Day.hpp>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <common/debug/Formatters.hpp>

#if defined(__SIZEOF_INT128__) && (__SIZEOF_INT128__ == 16)
#define HAS_128_BIT_INT
#endif

namespace aoc2025 {

#ifdef HAS_128_BIT_INT
inline __uint128_t encode(
    __uint128_t value,
    __uint128_t offset
) {
    return value << (9 * offset);
}

inline uint64_t decode(
    __uint128_t value,
    __uint128_t offset
) {
    return (uint64_t) (value >> (9 * offset)) % 512;
}
#endif

struct Button {
    size_t mask = 0;
    std::vector<bool> maskAsArray;
    int64_t enabled = 0;

#ifdef HAS_128_BIT_INT
    __uint128_t bigMask = 0;
#endif

    void set(size_t index) {
        mask |= (1ull << index);
#ifdef HAS_128_BIT_INT
        bigMask |= encode(1, index);
#endif
        maskAsArray.at(index) = true;
        ++enabled;
    }

    bool is(size_t idx) {
        return (mask & (1 << idx)) != 0;
    }

    void click(
        size_t& out
    ) {
        out ^= mask;
    }
#ifdef HAS_128_BIT_INT
    void click(
        __uint128_t& out
    ) const {
        out -= bigMask;
    }
#endif

    void click(std::vector<int64_t>& joltages) const {
        for (size_t i = 0; i < maskAsArray.size(); ++i) {
            if (maskAsArray.at(i)) {
                joltages.at(i) -= 1;
            }
        }
    }

    bool operator==(const Button& other) const { return mask == other.mask; }
};

struct UselessMachine {
    size_t indicators;
    std::vector<Button> buttons;
    std::vector<int64_t> joltages;
    
    UselessMachine(const std::string& v): indicators(0) {
        auto firstPart = v.substr(1, v.find(' ') - 2);

        for (size_t i = 0; i < firstPart.size(); ++i) {
            auto ch = firstPart.at(i);
            if (ch == '.') {
                // Noop: indicator is initialised to 0, so this is already set to 0
            } else if (ch == '#') {
                indicators |= (1 << i);
            } else {
                [[unlikely]] 
                throw std::runtime_error("Nope: " + std::string { ch });
            }
        }

        size_t p = 0;
        while ((p = v.find('(', p + 1)) != std::string::npos) {
            auto end = v.find(')', p);
            auto contents = v.substr(p + 1, end - p - 1);
            auto split = stc::string::split(contents, ',');
            Button b;
            b.maskAsArray.resize(firstPart.size(), false);
            // std::cout << "[[" << contents << "]]" << std::endl;
            for (auto& n : split) {
                // std::cout << "SET " << n << std::endl;
                // std::cout << n << std::endl;
                b.set(std::stoull(n));
            }
            // std::cout << std::endl;
            buttons.push_back(b);
        }

        p = v.find('{');
        auto end = v.find('}', p);
        auto contents = v.substr(p + 1, end - p - 1);
        auto split = stc::string::split(contents, ',');

        for (auto& n : split) {
            joltages.push_back(std::stoll(n));
        }

    }
};

struct ButtonConstraints {
    int64_t maxPresses;
};

#ifdef HAS_128_BIT_INT
struct SearchContext {
    __uint128_t joltages;
    std::vector<bool> enabledButtons;
    std::vector<int64_t> buttonPresses;
    __uint128_t path = 0;

    int64_t accumulatedClicks = 0;
};

struct SystemState {
    const int64_t systemJoltage;
    const std::vector<std::vector<size_t>> joltageToButtonMap;
    const std::vector<Button> buttons;
    const std::vector<ButtonConstraints> constraints;
    const std::vector<int64_t> minCostForJoltage;
    const size_t joltageCounts;
    
    std::unordered_set<__uint128_t> visited;
    int64_t minCost = std::numeric_limits<int64_t>::max();
};
#endif

class Day10 : public common::Day {
public:
    std::vector<UselessMachine> machines;

    DECLARE_DAY(2025, 10);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

#ifdef HAS_128_BIT_INT
    void directedDfsAStarThing(
        const SearchContext& searchState,
        SystemState& systemState
    );
#endif

    bool isButtonEnabled(
        __uint128_t joltages,
        size_t joltageCounts,
        const Button& b
    );
};

}
