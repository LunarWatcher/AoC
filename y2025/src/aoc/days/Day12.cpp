#include "Day12.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2025 {

void Day12::parse() {
    auto lines = common::Loader::getRawLinesForProcessing(this->path);

    for (size_t i = 0; i < lines.size(); ++i) {
        auto& line = lines.at(i);
        if (line == "") {
            continue;
        }
        if (line[1] == ':') {
            auto shapeIdx = line[0] - '0';
            auto& shapeRef = this->shapes.at(shapeIdx);
            for (size_t j = i + 1; j < i + 4; ++j) {
                auto& shapeLine = lines.at(j);
                auto& parseTarget = shapeRef.filled.at(j - i - 1);
                for (size_t i = 0; i < shapeLine.size(); ++i) {
                    parseTarget[i] = shapeLine.at(i) == '#';
                    shapeRef.area += (uint64_t) parseTarget[i];
                }
            }
            i += 3;
            continue;
        }
        auto x = line.find('x');
        auto colon = line.find(':');
        auto width = std::stoull(
            line.substr(0, x)
        );
        auto height = std::stoull(
            line.substr(x + 1, colon - x)
        );

        Region r {
            width, height, {}
        };

        std::stringstream ss;
        ss << line.substr(colon + 1);

        uint64_t count;
        while (ss >> count) {
            r.shapeCounts.push_back(count);
        }

        if (r.shapeCounts.size() != 6) {
            throw std::runtime_error("Bad girl - " + std::to_string(r.shapeCounts.size()));
        }

        regions.push_back(r);
    }
}

common::Output Day12::part1() {
    uint64_t sum = 0;
    for (const auto& region : regions) {
        uint64_t requiredArea = 0;
        for (size_t shapeIdx = 0; shapeIdx < region.shapeCounts.size(); ++shapeIdx) {
            const auto& shapeCount = region.shapeCounts.at(shapeIdx);
            requiredArea += shapeCount * shapes.at(shapeIdx).area;
        }

        if (requiredArea < region.width * region.height) {
            ++sum;
        } else {
            std::cout << "Discard region size " << region.width << "," << region.height << std::endl;
        }
    }
    return sum;
}

common::Output Day12::part2() {
    return 0ull;
}

}
