#pragma once

#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <stc/StringUtil.hpp>

namespace common::Loader {

struct Range {
    uint64_t left;
    uint64_t right;

    Range(const std::string& range) {
        left = std::stoull(range.substr(0, range.find('-')));
        right = std::stoull(range.substr(range.find('-') + 1));
    }
};

template <typename T>
T naiveLoader(const std::string& line) {
    return T(line);
}

constexpr inline auto RangeLoader = naiveLoader<Range>;

template <typename T>
std::vector<T> loadVector(std::filesystem::path input, std::function<T(const std::string& line)> parser) {
    std::ifstream f(input);
    if (!f) {
        throw std::runtime_error("Failed to find " + input.string());
    }

    // TODO: This isn't particularly fast. Can we make it more speed?
    std::vector<T> out;
    std::string buff;
    while (std::getline(f, buff)) {
        out.push_back(
            parser(buff)
        );
    }
    return out;
}

template <typename T>
std::vector<T> loadSingleLineVector(
    std::filesystem::path input,
    char delim,
    std::function<T(const std::string& line)> parser
) {
    std::ifstream f(input);
    if (!f) {
        throw std::runtime_error("Failed to find " + input.string());
    }
    std::vector<T> out;

    std::string buff;
    while (std::getline(f, buff, delim)) {
        // TODO: this probably includes a newline that needs to be stripped
        out.push_back(parser(buff));
    }

    return out;
}

}
