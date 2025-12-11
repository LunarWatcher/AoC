#include "Day11.hpp"
#include "common/loader/Loader.hpp"
#include <queue>
#include <set>
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
    std::queue<std::pair<std::string, Rays>> search;
    std::unordered_map<std::string, std::vector<std::string>> reverseTree;
    std::unordered_map<std::string, Rays> visited;

    for (auto& [node, links] : racks) {
        for (auto& link : links.outputs) {
            reverseTree[link].push_back(node);
        }
    }

    search.push({"svr", {}});
    std::unordered_set<std::string> lastLayer = { "svr" };

    while (true) {
        std::unordered_set<std::string> nextSearch;
        while (search.size()) {
            auto [ curr, acc ] = search.front();
            search.pop();

            for (auto& next : this->racks.at(curr).outputs) {
                if (next != "out") {
                    nextSearch.insert(next);
                }
                if (!visited.contains(next)) {
                    visited[next] = acc;
                } else {
                    auto& v = visited.at(next);
                    v.dft += acc.dft;
                    v.fft += acc.fft;
                    v.fft_dft += acc.fft_dft;
                    v.none += acc.none;
                }
                auto& visitedAcc = visited.at(next);
                // Now we want to calculate the sums
                if (next == "dft") {
                    visitedAcc.dft += visitedAcc.none + 1;
                    visitedAcc.fft_dft += visitedAcc.fft + 1;

                    visitedAcc.fft = 0;
                    visitedAcc.none = 0;
                } else if (next == "fft") {
                    visitedAcc.fft += visitedAcc.none + 1;
                    visitedAcc.fft_dft += visitedAcc.dft + 1;

                    visitedAcc.dft = 0;
                    visitedAcc.none = 0;
                } else if (curr == "svr") {
                    // This can break if dft or fft is immediately after svr, but we're ignoring this possibility out of
                    // convenience.
                    ++visitedAcc.none;
                    continue;
                }
                // Only add if not 0 to avoid spawning paths out of thin air
                visitedAcc.dft += (int64_t) visitedAcc.dft != 0;
                visitedAcc.fft += (int64_t) visitedAcc.fft != 0;
                visitedAcc.none += (int64_t) visitedAcc.none != 0;
                visitedAcc.fft_dft += (int64_t) visitedAcc.fft_dft != 0;
            }
        }

        if (nextSearch.empty()) {
            break;
        }

        for (auto& next : nextSearch) {
            search.push({ next, visited.at(next) });
        }

        std::swap(nextSearch, lastLayer);
    }

    auto& out = visited.at("out");
    // std::cout
    //     << "out node has none=" << out.none
    //     << ", dft=" << out.dft
    //     << ", fft=" << out.fft
    //     << ", fft&dft" << out.fft_dft
    //     << std::endl; 
    return out.fft_dft;
}

}
