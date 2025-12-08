#include "Day4.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2019 {

void Day4::parse() {

    this->range = common::Loader::loadVector<common::Loader::Range>(
        this->path,
        common::Loader::RangeLoader
    ).at(0);
}

common::Output Day4::part1() {
    uint64_t matches = 0;
    for (size_t i = range.left; i <= range.right; ++i) {
        auto asStr = std::to_string(i);

        char last = 0;
        bool hasRepeating = false;
        for (const auto& ch : asStr) {
            if (ch == last) {
                hasRepeating = true;
            }
            if (last > ch) {
                goto nope;
            }
            
            last = ch;
        }

        if (hasRepeating) {
            ++matches;
        }
nope:;
    }
    return matches;
}

common::Output Day4::part2() {
    uint64_t matches = 0;
    for (size_t i = range.left; i <= range.right; ++i) {
        auto asStr = std::to_string(i);

        char last = 0;
        char repeating = 0;
        char lastBad = 0;

        for (const auto& ch : asStr) {
            if (ch == last && ch != lastBad) {
                // ch == last means xxAAxx
                // ch == last AND ch == repeating means xAAAxx
                //                                       RLC
                // 
                // At this point, lastBad = ch and it's blacklisted
                if (repeating == ch) {
                    repeating = 0;
                    lastBad = ch;
                } else if (repeating == 0) {
                    repeating = ch;
                }
            }
            if (last > ch) {
                goto nope;
            }

            last = ch;
        }

        if (repeating != 0) {
            ++matches;
        }
nope:;
    }
    return matches;
}

}
