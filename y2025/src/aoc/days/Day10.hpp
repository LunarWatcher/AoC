#pragma once

#include "common/fuckingmathbullshit/EqSystem.hpp"
#include "common/math/VecN.hpp"
#include "stc/StringUtil.hpp"
#include <cassert>
#include <common/Day.hpp>
#include <limits>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace aoc2025 {

struct Button {
    size_t mask = 0;
    std::vector<bool> maskAsArray;
    int64_t targets = 0;

    void set(size_t index) {
        mask |= (1ull << index);
        maskAsArray.at(index) = true;
        ++targets;
    }

    bool is(size_t idx) const {
        return (mask & (1 << idx)) != 0;
    }

    void click(
        size_t& out
    ) const {
        out ^= mask;
    }
    void click(
        std::vector<int64_t>& joltages,
        int64_t clicks
    ) const {
        for (size_t i = 0; i < joltages.size(); ++i) {
            if (is(i)) {
                joltages.at(i) -= clicks;
            }
        }
    }

    int64_t maxPresses(
        const std::vector<int64_t>& joltages
    ) const {
        int64_t maxPresses = std::numeric_limits<int64_t>::max();
        for (size_t i = 0; i < joltages.size(); ++i) {
            if (is(i)) {
                auto& joltage = joltages.at(i);
                if (joltage <= 0) { return 0; }
                maxPresses = std::min(
                    maxPresses, joltage
                );
            }
        }
        return maxPresses;
    }
    
    bool operator==(const Button& other) const { return mask == other.mask; }
};

struct SearchData {
    common::VecN<int64_t> position;
    uint64_t buttonPresses = 0;
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

class Day10 : public common::Day {
public:
    std::vector<UselessMachine> machines;

    DECLARE_DAY(2025, 10);

    void assembleSystem(
        common::EqSystem& sys,
        const std::vector<Button>& buttons
    );

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

    std::unordered_map<size_t, std::set<std::set<size_t>>> findAllPaths(
        const std::vector<Button>& buttons
    );
    uint64_t recursivelyPressButtons(
        const std::unordered_map<size_t, std::set<std::set<size_t>>>& parityPaths,
        const std::vector<Button>& buttons,
        const std::vector<int64_t>& joltages
    );

    bool p2borked() override { return true; }
};

}
