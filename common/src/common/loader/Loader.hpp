#pragma once

#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <stc/StringUtil.hpp>

/**
 * Defines the standard loader structures. 
 *
 * For now, this module is in an expansion phase. More Stuff:tm: is added on demand. Refactoring is attempted when
 * needed, but there's a lot of different puzzle inputs wher the path to standardisation won't be clear until Later:tm:.
 * There will therefore be some redundancy.
 */
namespace common::Loader {

struct Range {
    uint64_t left;
    uint64_t right;

    Range(const std::string& range) {
        left = std::stoull(range.substr(0, range.find('-')));
        right = std::stoull(range.substr(range.find('-') + 1));
    }
};

struct IntStream {
    std::vector<int64_t> data;

    IntStream(const std::string& line) {
        for (auto& ch : line) {
            data.push_back(ch - '0');
        }
    }
};

template <typename T>
T naiveLoader(const std::string& line) {
    return T{line};
}

constexpr inline auto RangeLoader = naiveLoader<Range>;
constexpr inline auto IntStreamLoader = naiveLoader<IntStream>;

template <typename T>
std::vector<T> loadVector(const std::filesystem::path& input, std::function<T(const std::string& line)> parser) {
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
std::vector<std::vector<T>> mapLoader(
    const std::filesystem::path& input,
    std::function<T(char)> parser
) {
    std::ifstream f(input);
    if (!f) {
        throw std::runtime_error("Failed to find " + input.string());
    }

    std::vector<std::vector<T>> out;
    std::vector<T> line;
    char ch;
    while (f >> ch) {
        line.push_back(parser(ch));
        if (f.peek() == '\n') {
            out.push_back(line);
            line.clear();
            f.ignore();
        }
    }
    if (!line.empty()) {
        out.push_back(line);
    }
    return out;

}

template <typename T>
std::vector<T> loadIntVector(const std::filesystem::path& input) {
    std::ifstream f(input);
    if (!f) {
        throw std::runtime_error("Failed to find " + input.string());
    }

    // TODO: This isn't particularly fast. Can we make it more speed?
    std::vector<T> out;
    T val;
    
    while (f >> val) {
        out.push_back(val);
    }

    return out;
}

template <typename T>
std::vector<T> loadSingleLineVector(
    const std::filesystem::path& input,
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

template <typename T>
std::vector<T> loadSingleLineIntVector(
    const std::filesystem::path& input
) {
    std::ifstream f(input);
    if (!f) {
        [[unlikely]]
        throw std::runtime_error("Failed to find " + input.string());
    }
    std::vector<T> out;

    T val;
    while (f >> val) {
        out.push_back(val);

        if (f.peek() == ',') {
            f.ignore();
        }
    }

    return out;
}

}
