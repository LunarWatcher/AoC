#include "Day2.hpp"
#include "common/loader/Loader.hpp"
#include <algorithm>
#include <cmath>
#include <set>

namespace aoc2025 {


void Day2::parse() {
    this->ranges = common::Loader::loadSingleLineVector<common::Loader::Range>(
        this->path,
        ',',
        common::Loader::RangeLoader
    );
}

common::Output Day2::part1() {
    uint64_t sum = 0;
    for (auto range : ranges) {
        std::string start = std::to_string(range.left);
        std::string end = std::to_string(range.right);

        if (start.size() % 2 != 0 
            && start.size() == end.size()) {
            // Both are odd and of the same size; no repeats can occur
            // 101, 10101 and so on aren't considered to be repeats
            // (I bet part 2 is "repetitions anywhere in the string")
            continue;
        } else if (start.size() % 2 != 0) {
            // Start is odd: move range up
            auto order = start.size();
            range.left = (uint64_t) std::pow(10, order);
            start = std::to_string(range.left);
        } else if (end.size() % 2 != 0) {
            // End is odd: move range down
            auto order = end.size() - 1;
            range.right = (uint64_t) std::pow(10, order) - 1;
            end = std::to_string(range.right);
        }
        // std::cout << range.left << "-" << range.right << std::endl;

        if (range.right < range.left) {
            // Constraint solving pushed the range into an illegal area, so abort
            continue;
        } else if (range.right == range.left) {
            // optimisation: left == right means we just need to check if that one value is legal. I don't think this
            // will ever trigger
            [[unlikely]]
            std::cout << "It did trigger" << std::endl;
            auto [sA, sB] = this->substrHalf(start);
            if (sA == sB) {
                sum += range.right;
            }
            continue;
        }

        // Assumptions:
        // 1. We can disregard all odd parts of the range
        // 2. In a given even prefix, we know there's precisely one match, since first_half == second_half
        //
        // The hard part is identifying which prefixes are within a range

        // Testing shows that this is always 0, which massively simplifies things. We can simply iterate the digits
        // auto ordersBetweenStartAndEnd = end.size() - start.size();
        // std::cout << ordersBetweenStartAndEnd << std::endl;
        //
        // Assuming 10-99:
        // 11, 22, 33, ..., 99
        // If 10-40:
        // 11, 22, 33
        //
        // we also need a concept of a common prefix. Given 1690-1960, we don't need to care about
        // anything below 16xx. 1616 is out of range, so we discard it in the loop. 
        // 1690-1960 has four potential matches:
        // 1616
        // 1717
        // 1818
        // 1919
        //
        // Of which 3 are in range (everything but 1616)

        size_t smallestIndexOfInterest = 0;

        for (size_t i = 0; i < start.size() / 2; ++i) {
            // Given 1690-1960:
            // i == 0 => smallestIndexOfInterest = 1
            //      1 == 1
            // i == 0 => [no change]
            //      6 != 9
            if (start.at(i) == end.at(i)) {
                ++smallestIndexOfInterest;
            } else if (smallestIndexOfInterest != 0) {
                break;
            }
        }

        // std::cout << smallestIndexOfInterest << std::endl;

        // If the first half of the number is shared between the two, we know there's only one possible option:
        //
        // Given 16xx-16xx, the only possible option is 1616. 
        // This may be out of the real range, so this needs ot be checked separately.
        if (smallestIndexOfInterest == start.size() / 2) {
            auto substr = start.substr(0, start.size() / 2);
            auto add = std::stoull(substr + substr);

            if (add >= range.left && add <= range.right) {
                // std::cout << "ADD, FORCED: " << add << std::endl;
                sum += add;
            }
            continue;
        }

        auto startRange = std::stoull(
            start.substr(0, start.size() / 2)
        );
        auto endRange = std::stoull(
            end.substr(0, end.size() / 2)
        );
        for (auto i = startRange; i <= endRange; ++i) {
            auto str = std::to_string(i);
            auto val = std::stoull(str + str);

            if (val >= range.left && val <= range.right) {
                sum += val;
            }
        }

    }

    return sum;
}

common::Output Day2::part2() {
    uint64_t sum = 0;
    for (auto range : ranges) {
        for (uint64_t i = range.left;
            i <= range.right;
            ++i
        ) {
            std::string asStr = std::to_string(i);
            std::string_view asView = asStr;

            for (size_t sl = 1; sl <= asStr.size() / 2; ++sl) {
                if (asStr.size() % sl != 0) {
                    continue;
                }

                auto segments = asStr.size() / sl;

                for (size_t seg = 1; seg < segments; ++seg) {
                    if (asView.substr(seg * sl, sl) != asView.substr(0, sl)) {
                        goto nope;
                    }
                }
                {
                    sum += i;
                    break;
                }
nope:;
            }

        }
    }

    return sum;
}

std::pair<std::string_view, std::string_view> Day2::substrHalf(
    const std::string_view& in
) {
    if (in.size() % 2 != 0) {
        [[unlikely]]
        throw std::runtime_error("substrHalf constraint violated");
    }
    return {
        in.substr(0, in.size() / 2),
        in.substr(in.size() / 2)
    };
}

}
