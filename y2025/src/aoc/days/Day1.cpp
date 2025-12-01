#include "Day1.hpp"
#include "common/loader/Loader.hpp"
#include <iostream>

namespace aoc2025 {

void Day1::parse() {
    dials = common::Loader::loadVector<Dial>(
        this->path, common::Loader::naiveLoader<Dial>
    );
}

int64_t Day1::part1() {
    int ptr = 50;
    int zeroes = 0;

    for (const auto& dial : dials) {
        ptr += dial.op * dial.value;
        ptr %= 100;
        if (ptr < 0) {
            ptr += 100;
        }

        if (ptr == 0) {
            ++zeroes;
        }
    }

    return zeroes;
}

int64_t Day1::part2() {
    int ptr = 50;
    int zeroes = 0;

    for (const auto& dial : dials) {
        int old_ptr = ptr;
        ptr += dial.op * dial.value;

        auto res = std::div(ptr, 100);

        zeroes += std::abs(
            res.quot
            // Account for negative crossings (-18 / 100 == 0 rem 18, but a zero has been crossed).
            // We always need to add 1 for negative numbers, but only 1. 
            // -118 / 100 = 1 rem 18, and res.quot == 1, so adding 1 is all we need to do here.
            // This only applies if old_ptr > 0, as if it's just 0, no 0 has been crossed on L<n>
        )
            + (ptr < 0 && old_ptr != 0 ? 1 : 0);

        if (ptr == 0) {
            ++zeroes;
        }

        ptr = (res.rem < 0 ? 100 : 0) + res.rem;
        if (ptr < 0) {
            [[unlikely]]
            throw std::runtime_error("Idiot");
        }
    }

    return zeroes;
}
}
