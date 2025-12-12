#include "Day11.hpp"
#include "common/loader/Loader.hpp"
#include <queue>
#include <thread>
#include <unordered_map>
#include <unordered_set>

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
    uint64_t sum = 1;
    for (auto& [start, end] : std::vector<std::pair<std::string, std::string>> {
        { "svr", "fft" },
        { "fft", "dac" },
        { "dac", "out" }
    }) {
        std::unordered_map<std::string, uint64_t> memos;
        sum *= dfs(
            memos,
            start,
            end
        );
    }

    return sum;
}

uint64_t Day11::dfs(std::unordered_map<std::string, uint64_t>& memos, const std::string& next, const std::string& dest) {
    if (auto it = memos.find(next); it != memos.end()) {
        return it->second; 
    } else if (next == dest) {
        return 1;
    }

    auto& outputs = this->racks.at(next).outputs;
    size_t sum = 0;
    for (auto& output : outputs) {
        // if output contains out, output _is_ out
        if (output == "out" && dest != "out") {
            return 0;
        } 
        auto res = dfs(memos, output, dest);
        sum += res;
    }
    memos[next] += sum;
    return sum;
}
}
