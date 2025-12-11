#include "Day11.hpp"
#include "common/loader/Loader.hpp"
#include <queue>

namespace aoc2025 {

void Day11::parse() {
    auto lines = common::Loader::getRawLinesForProcessing(this->path);

    for (auto& line : lines) {
        std::stringstream lineAsStr;
        lineAsStr << line;
        std::string buff;
        std::string server;
        std::vector<std::string> outputs;
        while (std::getline(lineAsStr, buff, ' ')) {
            if (buff.ends_with(':')) {
                server = buff.substr(0, 3);
            } else {
                outputs.push_back(buff);
            }
        }

        racks[server] = {
            outputs
        };
    }
}

common::Output Day11::part1() {

    std::queue<std::string> search;
    uint64_t sum = 0;

    search.push("you");

    while (search.size()) {
        auto curr = search.front();
        search.pop();

        for (auto& next : this->racks.at(curr).outputs) {
            if (next == "out") {
                sum += 1;
            } else {
                search.push(next);
            }
        }
    }


    return sum;
}

common::Output Day11::part2() {
    return 0ull;
}

}
