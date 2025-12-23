#include "aoc/days/Day1.hpp"
#include "aoc/days/Day2.hpp"
#include "aoc/days/Day3.hpp"
#include "aoc/days/Day4.hpp"
#include "aoc/days/Day5.hpp"
#include "aoc/days/Day6.hpp"
#include "aoc/days/Day7.hpp"
#include "aoc/days/Day8.hpp"
#include "aoc/days/Day9.hpp"
#include "aoc/days/Day10.hpp"
#include "aoc/days/Day11.hpp"
#include "aoc/days/Day12.hpp"
#include "aoc/days/Day13.hpp"
#include "aoc/days/Day14.hpp"
#include "aoc/days/Day15.hpp"
#include <memory>
#include <common/Runner.hpp>

int main(int argc, const char* argv[]) {
    using namespace aoc2019;
    common::Runner::run(argc, argv, 2019, {
        std::make_shared<Day1>(),
        std::make_shared<Day2>(),
        std::make_shared<Day3>(),
        std::make_shared<Day4>(),
        std::make_shared<Day5>(),
        std::make_shared<Day6>(),
        std::make_shared<Day7>(),
        std::make_shared<Day8>(),
        std::make_shared<Day9>(),
        std::make_shared<Day10>(),
        std::make_shared<Day11>(),
        std::make_shared<Day12>(),
        std::make_shared<Day13>(),
        std::make_shared<Day14>(),
        std::make_shared<Day15>(),
    });
}
