#pragma once

#include <concepts>
#include <numeric>
#include <vector>

namespace common {

template <std::equality_comparable T>
struct DisjointSet {
    size_t maxSize;
    size_t remaining;
    std::vector<T> parent;
    std::vector<T> sizes;

    DisjointSet(size_t maxSize): maxSize(maxSize), remaining(maxSize), parent(maxSize), sizes(maxSize, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    T find(T x) {
        if (parent.at(x) == x) {
            return x;
        }
        return parent.at(x) = find(parent.at(x));
    }

    void link(T a, T b) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return;
        }

        if (sizes.at(a) < sizes.at(b)) {
            std::swap(a, b);
        }

        parent.at(b) = a;
        sizes.at(a) += sizes.at(b);
        remaining -= 1;
    }
};

}
