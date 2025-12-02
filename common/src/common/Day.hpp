#pragma once

#include <cstdint>
#include <filesystem>

namespace common {

class Day {
protected:
    std::filesystem::path path;
public:
    Day(int year, const std::string& filename)
        : path("../y" + std::to_string(year) + ("/inputs/") + filename) 
    {}

    virtual ~Day() = default;

    virtual void parse() = 0;
    virtual uint64_t part1() = 0;
    virtual uint64_t part2() = 0;

    virtual int day() = 0;
};

#define DECLARE_DAY(Year, DayNum) \
    Day##DayNum(const std::string& filename = "day" #DayNum ".txt"): Day(Year, filename) { \
        \
    } \
    int day() override { return DayNum; }

}
