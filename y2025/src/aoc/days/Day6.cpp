#include "Day6.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2025 {

void Day6::parse() {
    this->input = common::Loader::splitLoader<D6Input>(
        this->path,
        [](D6Input& data, const std::string& line, int mode) {
            std::stringstream ss;
            ss << line;
            if (mode == 0) {
                int64_t val;
                std::vector<int64_t> out;

                while (ss >> val) {
                    out.push_back(val);
                }

                data.lines.push_back(out);
            } else {
                char v;
                while (ss >> v) {
                    if (v == ' ' || v == '\n') {
                        continue;
                    }
                    switch (v) {
                    case '*':
                        data.ops.push_back(Operator::MULT);
                        break;
                    case '+':
                        data.ops.push_back(Operator::ADD);
                        break;
                    default:
                        throw std::runtime_error("Good job idiot: " + std::to_string(v));
                    }
                }
            }
        },
        [](const auto& line, int currMode) {
            if (std::isdigit(line[0]) == 0) {
                if (currMode != 0) {
                    throw std::runtime_error("Parsing error: found " + std::to_string(currMode) + " but found " + line);
                }
                return true;
            }
            return false;
        },
        true
    );

}

uint64_t Day6::part1() {
    uint64_t sum = 0;

    for (size_t i = 0; i < input.ops.size(); ++i) {
        int64_t intermediate;
        switch (input.ops.at(i)) {
        case Operator::MULT: {
            intermediate = 1;
            for (const auto& line : input.lines) {
                intermediate *= line.at(i);
            }
        } break;
        case Operator::ADD: {
            intermediate = 0;
            for (const auto& line : input.lines) {
                intermediate += line.at(i);
            }
        } break;

        }

        sum += intermediate;
    }

    return sum;
}

uint64_t Day6::part2() {
    uint64_t sum = 0;
    for (int64_t i = (int64_t) input.ops.size() - 1; i >= 0; --i) {

        for (size_t p = 0; p < 4; ++p) {
            int64_t intermediate = input.ops.at(i) == Operator::MULT ? 1 : 0;
            std::string stringifiedVal;
            for (const auto& line : input.lines) {
                std::string asString = std::to_string(line.at(i));

                if (asString.size() > p) {
                    stringifiedVal += asString.at(p);
                }
            }
            if (stringifiedVal.size() == 0) {
                continue;
            }

            int64_t val = std::stoll(stringifiedVal);
            switch (input.ops.at(i)) {
            case Operator::MULT: {
                intermediate *= val;
            } break;
            case Operator::ADD: {
                intermediate += val;
            } break;

            }

            std::cout << "SUM ADD " << intermediate << std::endl;
            sum += intermediate;
        }

    }

    return sum;
}

}
