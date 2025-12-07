#include "Day3.hpp"
#include "common/loader/Loader.hpp"

namespace aoc2019 {

void Day3::parse() {
    this->wires = common::Loader::loadCommaSeparatedLines<common::Loader::DirectionalInstruction>(
        this->path,
        common::Loader::DirectionalInstructionLoader
    );
}

std::unordered_map<WireDirection, std::vector<LineWithPointData>> Day3::convertToWires(
    const std::vector<common::Loader::DirectionalInstruction>& instructions
) {
    std::unordered_map<WireDirection, std::vector<LineWithPointData>> wires;
    int64_t x = 0;
    int64_t y = 0;
    int64_t traveled = 0;

    for (auto& wire : instructions) {
        // std::cout << wire.dir << wire.quantity << ",";
        switch (wire.dir) {
        case 'U':
        case 'D': {
            int64_t dir = wire.dir == 'U' ? 1 : -1;
            LineWithPointData w {
                .start = { x, y },
                .end = { x, y + ((int64_t) wire.quantity) * dir },
                .traveledAtStart = traveled,
            };
            y = w.end.y;

            wires[WireDirection::VERTICAL].push_back(w);
        }
            break;
        case 'L':
        case 'R': {
            int dir = wire.dir == 'R' ? 1 : -1;
            LineWithPointData w {
                .start = { x, y },
                .end = { x + ((int64_t) wire.quantity) * dir, y },
                .traveledAtStart = traveled,
            };
            x = w.end.x;

            wires[WireDirection::HORIZONTAL].push_back(w);
        }
            break;
        default:
            throw std::runtime_error("Unrecognised direction");
        }

        traveled += (int64_t) wire.quantity;
    }

    return wires;
}

uint64_t Day3::part1() {
    auto w1 = convertToWires(this->wires.at(0));
    auto w2 = convertToWires(this->wires.at(1));

    common::Vec2 closest = {99999, 99999};
    for (auto& [dir, wires] : w1) {
        auto intersectingDir = opposite(dir);
        auto& opposingWires = w2.at(intersectingDir);

        for (auto& wire : wires) {
            for (auto& crossingWire : opposingWires) {
                if (wire.linearIntersect(crossingWire)) {
                    common::Vec2 intersect;
                    if (dir == WireDirection::HORIZONTAL) {
                        intersect = {
                            .x = crossingWire.start.x,
                            .y = wire.start.y
                        };
                    } else {
                        intersect = {
                            .x = wire.start.x,
                            .y = crossingWire.start.y
                        };
                    }

                    // std::cout << intersect.x << "," << intersect.y << ", " << intersect.manhatten() << std::endl;
                    if (closest.manhatten() > intersect.manhatten()) {
                        closest = intersect;
                    }
                }
            }
        }
    }

    return closest.manhatten();
}

uint64_t Day3::part2() {
    auto w1 = convertToWires(this->wires.at(0));
    auto w2 = convertToWires(this->wires.at(1));

    std::pair<common::Vec2, int64_t> nearestIntersect = {{0,0}, 99999999ll};
    for (auto& [dir, wires] : w1) {
        auto intersectingDir = opposite(dir);
        auto& opposingWires = w2.at(intersectingDir);

        for (auto& wire : wires) {
            for (auto& crossingWire : opposingWires) {
                if (wire.linearIntersect(crossingWire)) {
                    common::Vec2 intersect;
                    int64_t dist = wire.traveledAtStart + crossingWire.traveledAtStart;
                    if (dir == WireDirection::HORIZONTAL) {
                        intersect = {
                            .x = crossingWire.start.x,
                            .y = wire.start.y
                        };
                    } else {
                        intersect = {
                            .x = wire.start.x,
                            .y = crossingWire.start.y
                        };
                    }

                    dist += (wire.start - intersect).manhatten();
                    dist += (crossingWire.start - intersect).manhatten();

                    if (dist < nearestIntersect.second) {
                        nearestIntersect = { intersect, dist };
                    }

                }
            }
        }
    }

    return nearestIntersect.second;
}

}
