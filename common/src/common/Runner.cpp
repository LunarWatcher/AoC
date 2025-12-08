#include "Runner.hpp"
#include <chrono>
#include <iostream>
#include <stc/Colour.hpp>

namespace common {

double Runner::runPart(int day, bool partB, double parseTime, std::function<common::Output()> runner) {
    auto start = Clock::now();
    auto result = runner();
    auto end = Clock::now();

    auto partTime = std::chrono::duration<double, std::milli>(end - start)
        .count();

        
    std::visit([&](const auto& val) {

        std::cerr
            << "Day " << std::format("{:>2}", day) << ", part " << (partB ? "B" : "A")
            << " ("
            << GetColourFor{parseTime}
            << std::format("{:>15.15}", parseTime)
            << "ms"
            << stc::colour::reset
            << " + "
            << GetColourFor{partTime}
            << stc::colour::use<stc::colour::Typography::BOLD>
            << std::format("{:>15.15}", partTime)
            << "ms"
            << stc::colour::reset
            << "): "
            << val 
            << std::endl;
    }, result);
    
    return partTime;
}

std::ostream& Runner::operator<<(std::ostream& ss, const CombinedPartTimes& v) {
    return ss
        << "       Total "
        << v.identifier << ": "
        << std::format("{:>15.15}", v.parseTimes)
        << "ms"
        << " + "
        << std::format("{:>15.15}", v.partTimes)
        << "ms"
        << " = "
        << std::format("{:>15.15}", v.total())
        << "ms"
        << std::endl;
}

void Runner::run(
    int argc,
    const char* argv[],
    int year, 
    const DayList& implementedDays
) {
    std::vector<std::string> args {
        argv + 1, argv + argc
    };

    std::cerr
        << stc::colour::use<stc::colour::Typography::BOLD>
        // Total width: 16 (up to first paren) + 17 (first col) + 3 (" + ")
        // + 17 (second col) + 3 ("): ") + 17 (reserved by the totals col; agian 15 + 2)
        // = 73
        << std::format("{:^73}", "Advent of Code - " + std::to_string(year))
        << "\n"
        << std::format("{:=^73}", "")
        << "\n\n"
        // 16: the length of the "Day xx, part A ("
        << std::format("{:>16}", "")
        // 17: 15 (max num width) + 2 ("ms")
        << std::format("{:>17}", "Parse") << " + "
        << std::format("{:>17}", "Part")
        << stc::colour::reset
        << std::endl;

    CombinedPartTimes partA { 'A', 0, 0 }, partB { 'B', 0, 0 };

    for (auto& day : implementedDays) {
        
        auto start = Clock::now();
        day->parse();
        auto end = Clock::now();
        auto parseTime = std::chrono::duration<double, std::milli>(
            end - start
        )
            .count();

        partA.parseTimes += parseTime;
        partB.parseTimes += parseTime;
        partA.partTimes += runPart(day->day(), false, parseTime, [&]() {
            return day->part1();
        });

        partB.partTimes += runPart(day->day(), true, parseTime, [&]() {
            return day->part2();
        });
    }

    std::cerr
        << "\n" 
        << partA
        << partB;
}

}
