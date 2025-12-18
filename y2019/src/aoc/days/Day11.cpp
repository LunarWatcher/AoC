#include "Day11.hpp"
#include "common/loader/Loader.hpp"
#include "common/math/Vec.hpp"
#include <aoc/intcode/IntCode.hpp>
#include <unordered_set>

namespace aoc2019 {

void Day11::parse() {
    this->prog = {
        common::Loader::loadSingleLineIntVector<int64_t>(
            this->path
        )
    };
}

common::Output Day11::part1() {

    IntCode computer(this->prog);
    computer.input.push(0);


    std::unordered_map<uint64_t, bool> visited;

    common::Direction d{0};
    common::Vec2 pos(0, 0);
    while (!computer.hasHalted()) {
        computer.run();

        if (computer.hasHalted()) {
            break;
        }

        auto encoded = (((uint64_t) (int) pos.x + 10000) << 32) | (uint64_t) (int) (pos.y + 10000);
        // std::cout << encoded << " " << pos.x << "," << pos.y << std::endl;
        auto colour = (bool) computer.output.next();
        computer.run();
        auto direction = computer.output.next() == 0 ? -1 : 1;

        visited[encoded] = colour;
        d += direction;
        pos += d;

        auto newEncoded = ((uint64_t) (int) pos.x + 10000) << 32 | (uint64_t) (int) (pos.y + 10000);
        computer.input.push(visited[newEncoded] ? 1 : 0);
    }

    return visited.size();
}

common::Output Day11::part2() {
    IntCode computer(this->prog);
    computer.input.push(1);


    std::vector<std::vector<bool>> map;

    common::Direction d{0};
    common::Vec2 pos(0,0);
    while (!computer.hasHalted()) {
        computer.run();

        if (computer.hasHalted()) {
            break;
        }

        auto colour = (bool) computer.output.next();
        computer.run();
        auto direction = computer.output.next() == 0 ? -1 : 1;
        if ((size_t) pos.y + 1 >= map.size()) {
            map.resize(
                pos.y + 2,
                std::vector<bool>(
                    map.size() == 0 
                        ? 0
                        : map.at(0).size()
                )
            );
        }

        if ((size_t) pos.x + 1 >= map.at(0).size()) {
            for (auto& row : map) {
                row.resize(pos.x + 2);
            }
        }

        map.at(pos.y).at(pos.x) = colour;
        d += direction;
        pos += d;

        computer.input.push(map.at(pos.y).at(pos.x));
    }

    std::stringstream out;
    out << "\n";
    for (size_t y = 0; y < map.size() - 1; ++y) {
        std::string buffer;
        for (size_t x = 0; x < map.at(0).size() - 1; ++x) {
            if (map.at(y).at(x)) {
                out << buffer << "#";
                buffer.clear();
            } else {
                buffer += " ";
            }
        }
        out << "\n";
    }
    return out.str();
}

}
