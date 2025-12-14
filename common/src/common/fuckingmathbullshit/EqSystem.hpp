#pragma once

#include <cstdint>
#include <vector>


namespace common {

class EqSystem {
private:
    std::vector<std::vector<int64_t>> mat;
    std::vector<int64_t> solutions;

    std::vector<bool> pivots;
public:

};

}
