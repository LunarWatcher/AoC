#pragma once

#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

namespace common::Loader {

template <typename T>
T naiveLoader(const std::string& line) {
    return T(line);
}

template <typename T>
std::vector<T> loadVector(std::filesystem::path input, std::function<T(const std::string& line)> parser) {
    std::ifstream f(input);
    if (!f) {
        throw std::runtime_error("Failed to find " + input.string());
    }

    std::vector<T> out;
    std::string buff;
    while (std::getline(f, buff)) {
        out.push_back(
            parser(buff)
        );
    }
    return out;
}

}
