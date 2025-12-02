#include "aoc/days/Day1.hpp"
#include "aoc/days/Day2.hpp"
#include <memory>
#include <common/Runner.hpp>

int main(int argc, const char* argv[]) {
    using namespace aoc2025;
    common::Runner::run(argc, argv, {
        std::make_shared<Day1>(),
        std::make_shared<Day2>(),
    });
}
