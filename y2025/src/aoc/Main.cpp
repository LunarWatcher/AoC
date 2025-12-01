#include "aoc/days/Day1.hpp"
#include <memory>
#include <common/Runner.hpp>

int main(int argc, const char* argv[]) {
    common::Runner::run(argc, argv, {
        std::make_shared<aoc2025::Day1>()
    });
}
