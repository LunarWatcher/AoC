#pragma once

#include "Day.hpp"
#include "stc/Colour.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <vector>
#include <iostream>
namespace common::Runner {

using DayList = std::vector<std::shared_ptr<Day>>;
using Clock = std::chrono::high_resolution_clock;

struct GetColourFor {
    double time;
};

inline std::ostream& operator<<(std::ostream& ss, const GetColourFor& v) {
    auto time = v.time;
    if (time < 10) {
        ss << stc::colour::fg<stc::colour::FourBitColour::BRIGHT_GREEN>;
    } else if (time < 250) {
        ss << stc::colour::fg<stc::colour::FourBitColour::GREEN>;
    } else if (time < 500) {
        ss << stc::colour::fg<stc::colour::FourBitColour::YELLOW>;
    } else if (time < 750) {
        ss << stc::colour::fg<stc::colour::FourBitColour::BRIGHT_RED>;
    } else {
        ss << stc::colour::fg<stc::colour::FourBitColour::RED>;
    }
    return ss;
}

struct CombinedPartTimes {
    char identifier;

    double partTimes;
    double parseTimes;

    double total() const { return partTimes + parseTimes; }
};

extern std::ostream& operator<<(std::ostream& ss, const CombinedPartTimes& v);

double runPart(int day, bool partB, double parseTime, std::function<int64_t()> runner);

void run(
    int argc,
    const char* argv[],
    int year, 
    const DayList& implementedDays
);

}
