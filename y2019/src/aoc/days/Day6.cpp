#include "Day6.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2019 {

void Day6::parse() {
    this->orbits = common::Loader::loadLinkedStringMap<std::string, std::string>(
        this->path,
        [](const auto& line) {
            auto sep = line.find(')');
            return std::pair<std::string, std::string> {
                line.substr(0, sep),
                line.substr(sep + 1)
            };
        }
    );
}

uint64_t Day6::recurseTree(const std::string& currentRoot, uint64_t treeSize) {
    auto it = orbits.find(currentRoot);
    if (it == orbits.end()) {
        return treeSize;
    }

    uint64_t s = treeSize;
    for (const auto& child : it->second) {

        s += recurseTree(child, treeSize + 1);
    }
    return s;
}

uint64_t Day6::recurseTreeP2(const std::string& currentRoot, uint64_t treeSize, bool& hasMerged) {
    auto it = orbits.find(currentRoot);
    if (it == orbits.end()) {
        if (currentRoot == "YOU" || currentRoot == "SAN") {
            return 1;
        }
        return 0;
    }

    uint64_t s = 0;
    int count = 0;
    for (const auto& child : it->second) {

        bool nestedHasMerged = false;
        auto v = recurseTreeP2(child, treeSize + 1, hasMerged);
        if (nestedHasMerged) {
            hasMerged = true;
        }
        if (v != 0) {
            s += v;
            ++count;
        }
    }

    if (count == 2) {
        hasMerged = true;
    } else if (count == 1 && !hasMerged) {
        ++s;
    }

    return s;
}

common::Output Day6::part1() {
    return recurseTree("COM", 0);
}

common::Output Day6::part2() {
    bool _ = false;
    // -2 because the first root notes return 1 while they're supposed to return 0. Could be avoided if an optional or
    // negative numbers were used instead, but that's effort and I have committed.
    return recurseTreeP2("COM", 0, _) - 2;
}

}
