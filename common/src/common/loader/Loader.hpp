#pragma once

#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <unordered_map>
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

    Range(): left(0), right(0) {  }
    Range(const std::string& range) {
        left = std::stoull(range.substr(0, range.find('-')));
        right = std::stoull(range.substr(range.find('-') + 1));
    }
};

struct DirectionalInstruction {
    char dir;
    uint64_t quantity;

    DirectionalInstruction(const std::string& dir) {
        this->dir = dir[0];
        this->quantity = std::stoull(
            dir.substr(1)
        );
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
constexpr inline auto DirectionalInstructionLoader = naiveLoader<DirectionalInstruction>;

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

template <typename K, typename V>
std::unordered_map<K, std::vector<V>> loadLinkedStringMap(
    const std::filesystem::path& input,
    std::function<std::pair<K, V>(const std::string&)> parser
) {
    std::unordered_map<K, std::vector<V>> out;

    std::ifstream f(input);
    if (!f) {
        throw std::runtime_error("Failed to find " + input.string());
    }

    std::string buff;
    while (std::getline(f, buff)) {
        auto [k, v] = parser(buff);
        out[k].push_back(v);
    }

    return out;
}

template <typename T>
std::vector<std::vector<T>> loadMap(
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
std::vector<std::pair<int64_t, int64_t>> loadSimpleMap(
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

/**
 * This should not be used unless absolutely necessary. All input parsing beyond day-specific logic should be converted
 * into reusable functions in case it returns. Use this if you've never seen a specific kind of parsing before, and
 * can't standardise without more sample sizes
 *
 * (Note that can be done with loadVector<string>, but it's separated to more easily find references for stuff that may
 * be refactorable)
 * 
 *
 * ## Current uses
 *
 * * Column parsing where all N lines are required for each column to be valid: 
 *     * 2025 day 6
 */
inline std::vector<std::string> getRawLinesForProcessing(
    const std::filesystem::path& input
) {
    std::ifstream f(input);
    if (!f) {
        throw std::runtime_error("Failed to find " + input.string());
    }

    std::vector<std::string> out;
    std::string buff;
    while (std::getline(f, buff)) {
        out.push_back(
            buff
        );
    }
    return out;

}

template <typename T>
std::vector<std::vector<T>> loadCommaSeparatedLines(
    const std::filesystem::path& input,
    std::function<T(const std::string&)> parser
) {
    std::ifstream f(input);
    if (!f) {
        throw std::runtime_error("Failed to find " + input.string());
    }

    std::vector<std::vector<T>> out;
    std::string buff;
    while (std::getline(f, buff)) {
        std::vector<T> intermediate;
        std::stringstream ss;
        ss << buff;

        std::string sb;
        while (std::getline(ss, sb, ',')) {
            intermediate.push_back(
                parser(sb)
            );
        }

        out.push_back(intermediate);
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

template <typename T>
T splitLoader(
    const std::filesystem::path& input,
    std::function<void(T&, const std::string& line, int mode)> parser,
    std::function<bool(const std::string& line, int currMode)> modeChecker = [](const std::string& l, int) {
        return l == "";
    },
    bool modeChangeIsParsed = false
) {
    std::ifstream f(input);
    if (!f) {
        throw std::runtime_error("Failed to find " + input.string());
    }
    T out;

    std::string buff;
    int mode = 0;
    while (std::getline(f, buff)) {
        if (modeChecker(buff, mode)) {
            ++mode;
            if (!modeChangeIsParsed) {
                continue;
            }
        }
        parser(
            out, buff, mode
        );
    }

    return out;

}

}
