#pragma once

#include <cstdint>
#include <ostream>
#include <unordered_map>
#include <vector>


namespace common {

template <typename T>
using NaiveMatrix = std::vector<std::vector<T>>;


struct IntermediateEquation {
    size_t variable;
    std::unordered_map<size_t, int64_t> variables;
    int64_t integerPart;

    int64_t compute(
        const std::unordered_map<size_t, int64_t>& globalFreeVariables
    ) const {
        int64_t out = integerPart;
        for (auto& [k, v] : variables) {
            out += globalFreeVariables.at(k)
                * v;
        }
        return out;
    }
};

class EqSystem {
private:
    NaiveMatrix<int64_t> mat;
    // TODO: doesn't really make sense to keep this around if it's merged into the matrix anyway
    std::vector<int64_t> solutions;

    std::vector<size_t> pivots;
    std::vector<size_t> freeVariables;
    const size_t variables;
    size_t pivotVariables = 0;

    int64_t sum(
        const std::vector<IntermediateEquation>& eq,
        const std::unordered_map<size_t, int64_t>& freeVariables
    );
public:
    [[nodiscard("You did a dumdum")]]
    EqSystem(
        size_t variables,
        const std::vector<int64_t>& solutions
    );

    void gaussEliminate();

    [[nodiscard]]
    int64_t& operator()(size_t row, size_t col);

    std::vector<int64_t> solveForSmallestTotalWithMinConstraints(
        int64_t min
    );

    const NaiveMatrix<int64_t>& getMat() const {
        return mat;
    }
};

extern std::ostream& operator<<(std::ostream& ss, const EqSystem& system);

}
