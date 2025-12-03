#include "Day3.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2025 {

void Day3::parse() {
    this->banks = common::Loader::loadVector<common::Loader::IntStream>(
        this->path,
        common::Loader::IntStreamLoader
    );
}


std::pair<int64_t, int64_t> Day3::calculateBank(const std::vector<int64_t>& bank) {
    std::pair<int64_t, int64_t> last;
    int64_t head = bank.at(0);
    int64_t tail = 0;
    // std::cout << "Checking new bank" << std::endl;
    for (size_t i = 1; i < bank.size(); ++i) {
        auto val = bank.at(i);
        if (val > head) {
            if (
                val > tail
                && last.first <= head
                && last.second < val
            ) {
                last = { head, val };
            }
            // std::cout << "head" << head << "val" << val << "tail" << tail 
            //     << "last" << last.first << last.second
            //     << "eval" << (val > tail) << (last.first >= head) << (last.second < val) 
            //     << std::endl;
            head = val;
            tail = 0;
        } else if (val > tail) {
            tail = val;
            last = { head, tail };
        }

        // std::cout << last.first << last.second << std::endl;

        if (head == 9 && tail == 9) {
            return last;
        }
    }
    if (last.first >= head && last.second < tail) {
        // std::cout << "End found: " << head << tail << std::endl;
        return { head, tail };
    }
    // std::cout << "Passthrough, last seen: " << head << tail << std::endl;
    return last;
}

uint64_t Day3::part1() {
    uint64_t sum = 0;
    for (const auto& [bank] : banks) {
        auto last = calculateBank(bank);
        sum += last.first * 10 + last.second;
    }

    return sum;
}

uint64_t Day3::part2() {
    return 0;
}

}
