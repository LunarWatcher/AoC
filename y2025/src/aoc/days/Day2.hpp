#pragma once

#include <common/Day.hpp>
#include <common/loader/Loader.hpp>

namespace aoc2025 {

class Day2 : public common::Day {
private:
    std::pair<std::string_view, std::string_view> substrHalf(
        const std::string_view& in
    );
public:
    std::vector<common::Loader::Range> ranges;

    DECLARE_DAY(2025, 2);

    void parse() override;
    common::Output part1() override;
    common::Output part2() override;

};

}
