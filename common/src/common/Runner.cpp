#include "Runner.hpp"
#include <chrono>
#include <iostream>
#include <stc/Colour.hpp>

#if __has_include(<sys/resource.h>)
#include <sys/resource.h>
#define HAS_ULIMIT
#endif

namespace common {

double Runner::runPart(
    int day,
    bool partB,
    double parseTime,
    bool borked,
    std::function<common::Output()> runner
) {
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
            << "): ";

            if (borked) {
                std::cerr << stc::colour::use<stc::colour::Typography::BOLD>
                    << stc::colour::fg<stc::colour::FourBitColour::RED>
                    << "[!!BORKED!!] "
                    << stc::colour::reset;
            }
            
        std::cerr << val 
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
#ifdef HAS_ULIMIT
    rlimit r {
        .rlim_cur = 
            // 1 KiB
            1024ll
            // 1 MiB
            * 1024ll
            // 1 GiB
            * 1024ll
            // 8 GiB
            * 8ll,
        .rlim_max = 
            // 1 KiB
            1024ll
            // 1 MiB
            * 1024ll
            // 1 GiB
            * 1024ll
            // 16 GiB
            * 16ll
    };
    setrlimit(
        RLIMIT_AS,
        &r
    );
#endif
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
        partA.partTimes += runPart(day->day(), false, parseTime, day->p1borked(), [&]() {
            return day->part1();
        });

        partB.partTimes += runPart(day->day(), true, parseTime, day->p2borked(), [&]() {
            return day->part2();
        });
    }

    std::cerr
        << "\n" 
        << partA
        << partB;
}

}
