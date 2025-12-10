#pragma once

#include "stc/StringUtil.hpp"
#include <cassert>
#include <common/Day.hpp>
#include <string>
#include <vector>

namespace aoc2025 {

struct Button {
    size_t mask = 0;
    std::vector<bool> maskAsArray;

void set(size_t index) {
        mask |= (1 << index);
        maskAsArray.at(index) = true;
    }

    bool is(size_t idx) {
        return (mask & (1 << idx)) != 0;
    }

    void click(
        size_t& out
    ) {
        out ^= mask;
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

struct LinAlgSystem {
    size_t buttonCount;
    std::vector<int64_t> solutionsCol;
    std::vector<std::vector<int64_t>> mat{
        solutionsCol.size(), std::vector<int64_t> (
            // + 1 to allow for solutions in the matrix
            buttonCount + 1, 0
        )
    };
    std::vector<bool> pivots = std::vector(mat.at(0).size() - 1, false);

    void gaussEliminate() {
        // Populate the solutions column
        for (size_t i = 0; i < solutionsCol.size(); ++i) {
            mat.at(i).back() = solutionsCol.at(i);
        }

        size_t pivotRow = 0;
        size_t pivotCol = 0;

        // Terminology reminders to self:
        // mxn: m rows * n cols
        // Translation: 
        auto rows = mat.size();
        auto cols = mat.at(0).size();
        // Reorder
        while (
            pivotRow < rows
            // We subtract 1 to prevent the solutions col from being eliminated, when it doesn't contain anything of 
            // value. 
            && pivotCol < cols
        ) {
            size_t iMax = 0;
            int64_t maxElem = -1;
            for (size_t i = pivotRow; i < rows; ++i) {
                auto val = std::abs(mat.at(i).at(pivotCol));
                if (val > maxElem) {
                    maxElem = val;
                    iMax = i;
                }
            }

            if (mat.at(iMax).at(pivotCol) == 0) {
                ++pivotCol;

            } else {
                auto& refPivotRow = mat.at(pivotRow);
                std::swap(
                    mat.at(pivotRow),
                    mat.at(iMax)
                );

                pivots.at(pivotCol) = true;

                for (size_t i = 0; i < rows; ++i) {
                    if (i == pivotRow) {
                        continue;
                    }
                    auto& rRow = mat.at(i);
                    double m = (double) rRow.at(pivotCol) / (double) refPivotRow.at(pivotCol);
                    // std::cout << "eliminate pivotCol=" << pivotCol  << " on " << i 
                    //     << " using m=" << m << " and pivotRow=" << pivotRow
                    //     << std::endl;
                    // for (auto& row : mat) {
                    //     for (auto& val : row) {
                    //         std::cout << val << " ";
                    //     }
                    //     std::cout << std::endl;
                    // }
                    rRow.at(pivotCol) = 0;

                    for (size_t j = pivotCol + 1; j < cols; ++j) {
                        rRow.at(j) -= (int64_t) ((double) refPivotRow.at(j) * m);
                    }
                }

                ++pivotRow;
                ++pivotCol;
            }
        }
    }

    std::vector<int64_t> solve() {

        std::vector<int64_t> freeVars;
        for (size_t i = 0; i < pivots.size(); ++i) {
            if (!pivots.at(i)) {
                freeVars.push_back((int64_t) i);
            }
        }

        std::vector<int64_t> bestSolution;
        size_t bestSum = 0;

        

        return bestSolution;
    }
};

class Day10 : public common::Day {
public:
    std::vector<UselessMachine> machines;

    DECLARE_DAY(2025, 10);

    void assembleSystem(
        LinAlgSystem& sys,
        const std::vector<Button>& buttons
    );

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

    bool p2borked() override { return true; }

};

}
