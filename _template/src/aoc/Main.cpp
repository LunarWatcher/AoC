#include "aoc/days/Day1.hpp"
#include <memory>
#include <common/Runner.hpp>

int main(int argc, const char* argv[]) {
    using namespace aoc2019;
    common::Runner::run(argc, argv, 2019, {
        std::make_shared<Day1>(),
    });
}
