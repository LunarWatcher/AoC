#pragma once

#include <functional>
#include <vector>
#include <iostream>
namespace common {

template <typename T>
struct CappedBinarySearchList {
    const size_t cap;
    std::vector<T> items;
    std::function<bool(const T& a, const T& b)> comparator;

    CappedBinarySearchList(
        size_t cap,
        const decltype(comparator)& comparator = std::less<T>()
    ) : cap(cap), comparator(comparator) {
        items.reserve(cap + 1);
    } 

    void add(const T& it) {
        if (!items.empty() && comparator(items.back(), it)) {
            return;
        }
        auto search = std::lower_bound(
            items.begin(), items.end(), it, comparator
        );
        if (search == items.end()) {
            if (items.size() < cap) {
                items.push_back(it);
            }
        } else {
            items.insert(search, it);
        }

        if (items.size() > cap) {
            items.pop_back();
        }
    }

    T& at(size_t i) {
        return items.at(i);
    }
    const T& at(size_t i) const {
        return items.at(i);
    }
};

}
