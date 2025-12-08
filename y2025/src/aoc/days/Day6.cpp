#include "Day6.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2025 {

void Day6::parse() {
    auto lines = common::Loader::getRawLinesForProcessing(this->path);

    size_t i = 0;
    size_t strLen = lines.at(0).size();
    while (i < strLen) {
        // Assume 0 is the start of the block
        auto& opLine = lines.back();
        auto op = opLine.at(i);
        auto nextNonSpace = opLine.find_first_not_of(' ', i + 1);
        // extra -1 to account for the mandatory and intentional space between each round
        auto len = (nextNonSpace == std::string::npos ? strLen : (nextNonSpace - 1)) - i; 
        std::vector<std::string> nums;
        // We have already parsed the op line
        nums.reserve(lines.size() - 1);
        for (size_t n = 0; n < lines.size() - 1; ++n) {
            nums.push_back(lines.at(n).substr(i, len));
        }

        i += len + 1;

        this->input.push_back(Column {
            nums, 
            op == '*' ? Operator::MULT : Operator::ADD
        });
    }
}

common::Output Day6::part1() {
    uint64_t sum = 0;

    for (const auto& column : input) {
        int64_t intermediate = column.op == Operator::MULT ? 1 : 0;
        for (auto& line : column.nums) {
            switch (column.op) {
            case Operator::MULT: {
                intermediate *= std::stoll(line); 
            } break;
            case Operator::ADD: {
                intermediate += std::stoll(line);
            } break;

            }
        }

        sum += intermediate;
    }

    return sum;
}

common::Output Day6::part2() {
    uint64_t sum = 0;
    for (const auto& column : input) {
        int64_t intermediate = column.op == Operator::MULT ? 1 : 0;
        for (size_t x = 0; x < column.nums.at(0).size(); ++x) {
            std::string n;
            for (auto& line : column.nums) {
                if (line.at(x) != ' ') {
                    n += line.at(x);
                }
            }
            auto val = std::stoll(n);

            switch (column.op) {
            case Operator::MULT: {
                intermediate *= val; 
            } break;
            case Operator::ADD: {
                intermediate += val;
            } break;

            }
        }
        sum += intermediate;

    }
    return sum;
}

}
