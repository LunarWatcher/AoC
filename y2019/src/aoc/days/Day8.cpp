#include "Day8.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2019 {

void Day8::parse() {
    auto lines = common::Loader::getRawLinesForProcessing(this->path);
    const auto& line = lines.at(0);

    for (size_t i = 0; i < line.size(); i += width * height) {
        images.push_back(Image {
            width, height,
            line.substr(i, width * height)
        });
    }
}

common::Output Day8::part1() {
    auto match = std::max_element(
        images.begin(), 
        images.end(),
        [](const auto& a, const auto& b) {
        return a.zeroes > b.zeroes;
    });
    return match->ones * match->twos;
}

common::Output Day8::part2() {
    std::stringstream ss;
    ss << "\n";
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            for (auto& im : images) {
                auto val = im.pixels.at(y).at(x);
                if (val == 2) {
                    continue;
                }

                ss << (val == 0 ? '.' : '#');
                break;
            }
        }
        ss << "\n";
    }
    return ss.str();
}

}
