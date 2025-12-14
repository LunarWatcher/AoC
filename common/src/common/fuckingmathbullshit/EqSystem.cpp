#include "EqSystem.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

namespace common {

EqSystem::EqSystem(

    size_t variables,
    const std::vector<int64_t>& solutions
):
    mat(
        solutions.size(),
        std::vector<int64_t>(variables + 1, 0)
    ),
    solutions(solutions),
    pivots(solutions.size(), std::numeric_limits<size_t>::max()),
    variables(variables)
{
    // Populate the solutions column
    for (size_t i = 0; i < solutions.size(); ++i) {
        mat.at(i).back() = solutions.at(i);
    }
}

void EqSystem::gaussEliminate() {

    size_t pivotRow = 0;
    size_t pivotCol = 0;

    // Terminology reminders to self:
    // mxn: m rows * n cols
    // Translation: 
    auto rows = mat.size();
    auto cols = mat.at(0).size();
    // Reorder
    while (
        pivotRow < rows
        // We subtract 1 to prevent the solutions col from being eliminated, when it doesn't contain anything of 
        // value. 
        && pivotCol < cols - 1
    ) {
        size_t iMax = 0;
        int64_t maxElem = -1;
        for (size_t i = pivotRow; i < rows; ++i) {
            auto val = std::abs(mat.at(i).at(pivotCol));
            if (val > maxElem) {
                maxElem = val;
                iMax = i;
            }
        }

        if (mat.at(iMax).at(pivotCol) == 0) {
            ++pivotCol;
        } else {
            auto& refPivotRow = mat.at(pivotRow);
            std::swap(
                mat.at(pivotRow),
                mat.at(iMax)
            );

            pivots.at(pivotRow) = pivotCol;

            for (size_t i = pivotRow + 1; i < rows; ++i) {
                if (i == pivotRow) {
                    continue;
                }
                auto& rRow = mat.at(i);

                // double m = (double) rRow.at(pivotCol) / (double) refPivotRow.at(pivotCol);
                // std::cout << "eliminate pivotCol=" << pivotCol  << " on " << i 
                //     << " using m=" << m << " and pivotRow=" << pivotRow
                //     << std::endl;
                // for (auto& row : mat) {
                //     for (auto& val : row) {
                //         std::cout << val << " ";
                //     }
                //     std::cout << std::endl;
                // }
                // rRow.at(pivotCol) = 0;
                auto a = rRow.at(pivotCol);
                if (a == 0) {
                    continue;
                }
                auto b = refPivotRow.at(pivotCol);

                auto l = std::lcm(a, b);
                mult(
                    rRow,
                    l / b
                );
                auto refPivotRowCopy = refPivotRow;
                mult(
                    refPivotRowCopy,
                    l / a
                );

                sub(
                    rRow,
                    refPivotRowCopy
                );

            }

            ++pivotRow;
            ++pivotCol;
        }
    }

    for (size_t i = 0; i < mat.size(); ++i) {
        auto& row = mat.at(i);
        auto& pivot = pivots.at(i);
        if (pivot == std::numeric_limits<size_t>::max()) {
            // No pivots here
            continue;
        }
        ++pivotVariables;

        if (row.at(pivot) < 0) {
            for (auto& it : row) {
                it *= -1;
            }
        }
    }
    for (size_t i = 0; i < variables; ++i) {
        if (std::find(
            pivots.begin(), pivots.end(), i
        ) == pivots.end()) {
            freeVariables.push_back(i);
        }
    }
}
int64_t EqSystem::sum(
    const std::vector<IntermediateEquation>& eq,
    const std::unordered_map<size_t, int64_t>& freeVariables
) {
    int64_t sum = 0;
    for (auto& equation : eq) {
        sum += equation.compute(
            freeVariables
        );
    }
    return sum;
}

std::vector<int64_t> EqSystem::solveForSmallestTotalWithMinConstraints(
    int64_t min
) {
    std::vector<int64_t> out(variables, 0);

    /*
     * Given
     * [
     * 1, 0, 0, 1, 0, -1 | 2
     * 0, 1, 0, 0, 0, 1 | 5
     * 0, 0, 1, 1, 0, -1 | 1
     * 0, 0, 0, 0, 1, 1 | 3
     * ]
     *
     * We know:
     * 1*x0 + 1*x3 - 1*x5 = 2
     * 1*x1 + 1*x5 = 5
     * 1*x2 + 1*x3 - 1*x5 = 1
     * 1*x4 + 1*x5 = 3
     *
     * 1*x0 = - 1*x3 + 1*x5 + 2
     * 1*x1 = - 1*x5 + 5
     * 1*x2 = - 1*x3 + 1*x5 + 1
     * 1*x4 = - 1*x5 + 3
     */
    std::vector<IntermediateEquation> equations;
    for (size_t i = 0; i < mat.size(); ++i) {
        auto& row = mat.at(i);
        auto& pivot = pivots.at(i);
        if (pivot == std::numeric_limits<size_t>::max()) {
            // No pivots, so empty row. Not worth processing
            continue;
        }
        std::unordered_map<size_t, int64_t> remainingVariables;
        for (auto& j : freeVariables) {
            auto& value = row.at(j);
            if (value != 0) {
                remainingVariables[j] 
                    // *-1 because we're moving it to the other side of the equation
                    = value * (-1);
            }
        }
        assert (pivot != variables);
        equations.push_back({
            pivot,
            remainingVariables,
            row.back()
        });
    }

    for (auto& equation : equations) {
        if (equation.variables.size() == 0) {
            out.at(equation.variable) = equation.integerPart;
        }
    }

    if (this->freeVariables.size() > 0) {
        std::unordered_map<size_t, int64_t> bruteForcedFreeVariables;
        for (auto& freeIdx : this->freeVariables) {
            bruteForcedFreeVariables[freeIdx] = min;
        }

        std::queue<decltype(bruteForcedFreeVariables)> q;
        q.push(bruteForcedFreeVariables);

        int64_t minSystemValue = sum(equations, bruteForcedFreeVariables);
        decltype(bruteForcedFreeVariables) minState = bruteForcedFreeVariables;
        while (q.size()) {
            auto state = q.front();
            q.pop();
            for (size_t i = 0; i < state.size(); ++i) {
                auto variableIdx = this->freeVariables.at(i);
                auto newState = state;

                int64_t systemValue = 0;

                bool recoverablyBad = false;
                for (auto& eq : equations) {
                    auto v = eq.compute(
                        newState
                    );
                    systemValue += v;
                    // Prevent infinite downward spirals
                    if (v < 0) {
                        if (eq.compute(state) >= v) {
                            recoverablyBad = true;
                            continue;
                        }
                        goto bad;
                    }

                }
                // Discard solution if it doesn't decrease the overall cost
                // This may discard some solutions where it doesn't grow fast enough, but it'll be good enough for
                // 2025d10p2
                if (!recoverablyBad && systemValue < minSystemValue) {
                    std::cout << systemValue << " replaces " << minSystemValue << std::endl;
                    minSystemValue = systemValue;
                    minState = newState;
                    newState.at(variableIdx) += 1;

                    q.push(newState);
                } else if (recoverablyBad) {
                    newState.at(variableIdx) += 1;
                    q.push(newState);
                }
bad:
                continue;
            }
        }
        assert(minState.size() == freeVariables.size());

        for (auto& equation : equations) {
            if (equation.variables.size() != 0) {
                out.at(equation.variable) = equation.compute(
                    minState
                );
            }

            std::cout << "eq x_n = " << out.at(equation.variable) << std::endl;
        }
        for (auto& [v, value] : minState) {
            std::cout
                << out.at(v) << " -> "
                << value << std::endl;
            out.at(v) = value;
        }
    }

    return out;
}

int64_t& EqSystem::operator()(size_t row, size_t col) {
    // The other size checks are managed by the vectors
    if (col == variables) {
        throw std::runtime_error("Cannot modify the solutions column after initialisation");
    }
    return mat.at(row).at(col);
}

std::ostream& operator<<(std::ostream& ss, const EqSystem& system) {
    ss << "[\n";
    for (auto& row : system.getMat()) {
        ss << " ";
        for (size_t colIdx = 0; colIdx < row.size(); ++colIdx) {
            if (colIdx != 0 && colIdx != row.size() - 1) {
                ss << ", ";
            } else if (colIdx == row.size() - 1) {
                ss << " | ";
            }

            ss << row.at(colIdx);
        }
        ss << "\n";
    }
    return ss << "]\n";
}

void EqSystem::sub(
    std::vector<int64_t>& lhs,
    std::vector<int64_t>& rhs
) {
    for (size_t i = 0; i < lhs.size(); ++i) {
        lhs.at(i) -= rhs.at(i);
    }
}

void EqSystem::mult(
    std::vector<int64_t>& lhs,
    int64_t val
) {
    for (auto& v : lhs) {
        v *= val;
    }
}

}
