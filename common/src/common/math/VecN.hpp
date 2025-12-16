#pragma once

#include <vector>
#include <cassert>
#include <iostream>

namespace common {

template <typename T>
struct VecN {
    std::vector<T> values = {};

    T euclidean() const {
        return euclidean(
            {
                std::vector<T>(values.size(), 0)
            }
        );
    }
    T euclidean(const VecN<T>& origin) const {
        assert(origin.values.size() == values.size());
        T out = 0;

        for (size_t i = 0; i < values.size(); ++i) {
            auto delta = origin.values.at(i) - values.at(i);
            out += delta * delta;
        }

        return out;
    }

    VecN operator+(const VecN<T>& other) const {
        assert(other.values.size() == values.size());
        std::vector<T> newValues(this->values.size(), 0);

        for (size_t i = 0; i < newValues.size(); ++i) {
            newValues.at(i) = this->values.at(i) + other.values.at(i);
        }

        return VecN<T> { newValues };
    }

    bool operator==(const VecN<T>& other) const {
        assert(other.values.size() == values.size());

        for (size_t i = 0; i < values.size(); ++i) {
            if(this->values.at(i) != other.values.at(i)) {
                return false;
            }
        }
        return true;
    }
};

}
