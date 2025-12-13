#pragma once

#include "stc/StringUtil.hpp"
#include <cassert>
#include <common/Day.hpp>
#include <string>
#include <vector>
#include <common/debug/Formatters.hpp>


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

    bool is(size_t idx) {
        return (mask & (1 << idx)) != 0;
    }

    void click(
        size_t& out
    ) {
        out ^= mask;
    }

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

class Day10 : public common::Day {
public:
    std::vector<UselessMachine> machines;

    DECLARE_DAY(2025, 10);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

    bool p2borked() override { return true; }
};

}
