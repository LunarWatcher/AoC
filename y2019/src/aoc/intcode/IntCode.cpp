#include "IntCode.hpp"
#include <string>
#include <stdexcept>
#include <iostream>

namespace aoc2019 {

IntCode::IntCode(
    const std::vector<int64_t>& instructions
) : source(instructions), workingSet(instructions) {

}

void IntCode::recode(
    const std::vector<std::pair<size_t, int64_t>>& modifications
) {
    workingSet = source;
    for (const auto& [pos, val] : modifications) {
        workingSet.at(pos) = val;
    }
}

Opcode4 IntCode::resolveOp4(
    const Program& ram,
    size_t opcodeAddr
) {
    // TODO: I'm not happy that these are chained like this. Maybe it makes sense to add some form of helper struct?
    return {
        ram.at(
            ram.at(opcodeAddr + 1)
        ),
        ram.at(
            ram.at(opcodeAddr + 2)
        ),
        ram.at(opcodeAddr + 3)
    };
}

int64_t IntCode::run(
    Program* inspect
) {
    // Create a copy of the workingSet instructions to keep a per-run state.
    auto ram = workingSet;

    size_t ptr = 0;

    bool running = true;
    while (running) {
        auto op = ram.at(ptr);

        switch (op) {
        case 1: {
            auto ops = resolveOp4(ram, ptr);
            ram.at(ops.destAddr) = ops.val1 + ops.val2;
            ptr += 4;
        } break;
        case 2: {
            auto ops = resolveOp4(ram, ptr);
            ram.at(ops.destAddr) = ops.val1 * ops.val2;
            ptr += 4;
        } break;
        case 99:
            // std::cout << "HALT" << std::endl;
            running = false;
            break;
        default:
            [[unlikely]]
            throw std::runtime_error("Unknown opcode: " + std::to_string(op));
        }
    }

    if (inspect != nullptr) {
        *inspect = ram;
    }

    return ram.at(0);
}

}
