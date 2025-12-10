#pragma once

#include "stc/StringUtil.hpp"
#include <cassert>
#include <common/Day.hpp>
#include <string>
#include <vector>

namespace aoc2025 {

struct Button {
    std::vector<size_t> targets;

    void click(
        std::vector<bool>& out
    ) {
        for (auto& target : targets) {
            auto v = out.at(target);
            v = !v;
        }
    }

    bool operator==(const Button& other) const { return targets == other.targets; }
};

struct UselessMachine {
    std::vector<bool> indicators;
    std::vector<Button> buttons;
    std::vector<uint64_t> joltages;

    UselessMachine(const std::string& v) {
        auto firstPart = v.substr(1, v.find(' ') - 2);

        for (auto& ch : firstPart) {
            if (ch == '.') {
                indicators.push_back(false);
            } else if (ch == '#') {
                indicators.push_back(true);
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
            for (auto& n : split) {
                // std::cout << n << std::endl;
                b.targets.push_back(std::stoull(n));
            }
            buttons.push_back(b);
        }

        p = v.find('{');
        auto end = v.find('}', p);
        auto contents = v.substr(p + 1, end - p - 1);
        auto split = stc::string::split(contents, ',');


        for (auto& n : split) {
            joltages.push_back(std::stoull(n));
        }
    }
};

class Day10 : public common::Day {
public:
    std::vector<UselessMachine> machines;

    DECLARE_DAY(2025, 10);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
