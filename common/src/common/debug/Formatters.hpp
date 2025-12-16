#pragma once

#include <vector>
#include <set>
#include <ostream>

// TODO: these really should be std::format, but std::formatter is being a pile of shit and I cannot be bothered dealing
// with it right now

template <typename T, typename Alloc = std::allocator<T>>
std::ostream& operator<<(std::ostream& ss, const std::vector<T, Alloc>& vec) {
    ss << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0) {
            ss << ", ";
        }
        ss << vec.at(i);
    }
    ss << "]";
    return ss;
}

template <typename T, typename Alloc = std::allocator<T>>
std::ostream& operator<<(std::ostream& ss, const std::set<T, Alloc>& set) {
    ss << "[";
    size_t i = 0;
    for (const auto& val : set) {
        if (i != 0) {
            ss << ", ";
        }
        ++i;
        ss << val;
        
    }
    ss << "]";
    return ss;
}

