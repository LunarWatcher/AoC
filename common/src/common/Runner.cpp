#include "Runner.hpp"
#include <chrono>
#include <iostream>
#include <stc/Colour.hpp>

namespace common {

void Runner::runPart(int day, bool partB, double parseTime, std::function<int64_t()> runner) {
    auto start = Clock::now();
    auto result = runner();
    auto end = Clock::now();

    auto partTime = std::chrono::duration<double, std::milli>(end - start)
        .count();

    std::cout << "Day " << std::format("{:>2}", day) << ", part " << (partB ? "B" : "A")
        << " ("
            << GetColourFor{parseTime}
            << std::format("{:<10}", parseTime)
            << stc::colour::reset
            << " + "
            << GetColourFor{partTime}
            << stc::colour::use<stc::colour::Typography::BOLD>
            << std::format("{:<10}", partTime)
            << stc::colour::reset
        << "): "
        << result
        << std::endl;
    

}

void Runner::run(int argc, const char* argv[], const DayList& implementedDays) {
    std::vector<std::string> args {
        argv + 1, argv + argc
    };

    std::cout 
        << stc::colour::use<stc::colour::Typography::BOLD>
        << "                Parse (ms)   Part (ms)"
        << stc::colour::reset
        << std::endl;
    for (auto& day : implementedDays) {
        
        auto start = Clock::now();
        day->parse();
        auto end = Clock::now();
        auto parseTime = std::chrono::duration<double, std::milli>(
            end - start
        )
            .count();

        runPart(day->day(), false, parseTime, [&]() {
            return day->part1();
        });

        runPart(day->day(), true, parseTime, [&]() {
            return day->part2();
        });

    }
}

}
