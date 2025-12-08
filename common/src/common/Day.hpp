#pragma once

#include <cstdint>
#include <filesystem>

namespace common {


using Output = std::variant<int64_t, uint64_t, std::string>;
class Day {
protected:
    std::filesystem::path path;
public:
    Day(int year, const std::string& filename)
        : path("../y" + std::to_string(year) + ("/inputs/") + filename) 
    {}

    virtual ~Day() = default;

    virtual void parse() = 0;
    virtual common::Output part1() = 0;
    virtual common::Output part2() = 0;

    virtual int day() = 0;
};

#define DECLARE_DAY(Year, DayNum) \
    Day##DayNum(const std::string& filename = "day" #DayNum ".txt"): Day(Year, filename) { \
        \
    } \
    int day() override { return DayNum; }
#define DECLARE_CONSTRUCTOR(Year, DayNum, ...) \
    int day() override { return DayNum; } \
    Day##DayNum(const std::string& filename = "day" #DayNum ".txt", __VA_ARGS__): Day(Year, filename)

}
