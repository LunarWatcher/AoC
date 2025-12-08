#pragma once

#include <common/Day.hpp>

#include <vector>

namespace aoc2019 {

struct Image {
    std::vector<std::vector<int>> pixels;
    size_t zeroes = 0, ones = 0, twos = 0;
    Image(size_t width, size_t height, const std::string& data) {
        
        if (data.size() != width * height) {
            throw std::runtime_error("Bad image data");
        }
        std::vector<int> curr;
        for (auto& ch : data) {
            curr.push_back(ch - '0');
            if (ch == '0') {
                ++zeroes;
            } else if (ch == '1') {
                ++ones;
            } else {
                ++twos;
            }

            if (curr.size() == width) {
                pixels.push_back(curr);
                curr.clear();
            }
        }
    }
};

class Day8 : public common::Day {
public:
    const size_t width, height;
    std::vector<Image> images;

    DECLARE_CONSTRUCTOR(2019, 8, size_t width = 25, size_t height = 6), width(width), height(height) {}

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
