#include "Day3.hpp"
#include "common/loader/Loader.hpp"
#include <algorithm>

namespace aoc2025 {

void Day3::parse() {
    this->banks = common::Loader::loadVector<common::Loader::IntStream>(
        this->path,
        common::Loader::IntStreamLoader
    );
}


std::vector<int64_t> Day3::calculateBank(
    const std::vector<int64_t>& bank,
    size_t bankSize
) {
    // Start at the highest element that's far enough away from the end to fit a full series
    // We know that given 
    //  12345xxxx
    // and bankSize = 5, 5xxxx is guaranteed to be the biggest number. 
    // equivalently, for
    //  12345xxxxxxxxxxxxxxxxxxxxx
    // and bankSize = 5 and where each x <= 4, the number will start with that max value.
    std::vector<int64_t> last;
    size_t startIdx = 0;
    while(last.size() < bankSize) {
        auto max = std::max_element(
            bank.begin() + (int64_t) startIdx,
            bank.end() - (int64_t) (bankSize - last.size() -1)
        );
        startIdx = std::distance(bank.begin(), max) + 1;
        last.push_back(*max);
    }

    return last;
}

uint64_t Day3::part1() {
    uint64_t sum = 0;
    for (const auto& [bank] : banks) {
        sum += vec2int(
            calculateBank(bank, 2)
        );
    }
    return sum;
}

uint64_t Day3::part2() {
    uint64_t sum = 0;
    for (const auto& [bank] : banks) {
        sum += vec2int(
            calculateBank(bank, 12)
        );
    }
    return sum;
}

}
