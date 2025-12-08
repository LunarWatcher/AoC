#include "IntCode.hpp"
#include <cmath>
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
        workingSet.ram.at(pos) = val;
    }

    this->halted = false;
}

Opcode4 IntCode::resolveOp4(
    const Program& ram,
    size_t opcodeAddr
) {
    // TODO: I'm not happy that these are chained like this. Maybe it makes sense to add some form of helper struct?
    return {
        ram.resolveReference(opcodeAddr + 1),
        ram.resolveReference(opcodeAddr + 2),
        ram.resolveImmediateMode(opcodeAddr + 3)
    };
}

int64_t IntCode::resolveMode(int64_t rawOp, short parameterIdx) {
    return rawOp / int64_t(std::pow<int64_t>(10, parameterIdx + 2)) % 10;
}

int64_t IntCode::run(
    StdStream* in,
    Program* inspect
) {
    // output.data.clear();

    if (cacheWorkingMemory) {
        if (inspect == nullptr) {
            throw std::runtime_error("Bad girl 2");
        }

        if (inspect->ram.size() == 0) {
            *inspect = workingSet;
        }
    }

    // Create a copy of the workingSet instructions to keep a per-run state.
    auto& ram = cacheWorkingMemory ? *inspect : workingSet;

    auto& ptr = ram.ptr;

    bool running = true;
    while (running) {
        auto rawOp = ram.resolveImmediateMode(ptr);
        auto op = rawOp % 100;

        switch (op) {
        case 1: {
            auto val1 = ram.resolve(resolveMode(rawOp, 0), ptr + 1);
            auto val2 = ram.resolve(resolveMode(rawOp, 1), ptr + 2);
            auto dest = ram.resolveImmediateMode(ptr + 3);
            ram.at(dest) = val1 + val2;
            ptr += 4;
        } break;
        case 2: {
            auto val1 = ram.resolve(resolveMode(rawOp, 0), ptr + 1);
            auto val2 = ram.resolve(resolveMode(rawOp, 1), ptr + 2);
            auto dest = ram.resolveImmediateMode(ptr + 3);
            ram.at(dest) = val1 * val2;
            ptr += 4;
        } break;
        case 3: {
            auto dest = ram.resolveImmediateMode(ptr + 1);
            if (in == nullptr) {
                throw std::runtime_error("Bad girl");
            }
            ram.at(dest) = in->next();
            ptr += 2;
        } break;
        case 4: {
            auto value = ram.resolve(resolveMode(rawOp, 0), ptr + 1);
            this->output.push(value);
            ptr += 2;
            running = false;
        } break;

        case 5: {
            auto value = ram.resolve(resolveMode(rawOp, 0), ptr + 1);
            auto jumpTo = ram.resolve(resolveMode(rawOp, 1), ptr + 2);
            if (value != 0) {
                ptr = jumpTo;
            } else {
                ptr += 3;
            }
        } break;
        case 6: {
            auto value = ram.resolve(resolveMode(rawOp, 0), ptr + 1);
            auto jumpTo = ram.resolve(resolveMode(rawOp, 1), ptr + 2);
            if (value == 0) {
                ptr = jumpTo;
            } else {
                ptr += 3;
            }
        } break;

        case 7: {
            auto val1 = ram.resolve(resolveMode(rawOp, 0), ptr + 1);
            auto val2 = ram.resolve(resolveMode(rawOp, 1), ptr + 2);
            auto dest = ram.resolveImmediateMode(ptr + 3);
            ram.at(dest) = (int64_t) val1 < val2;
            ptr += 4;
        } break;
        case 8: {
            auto val1 = ram.resolve(resolveMode(rawOp, 0), ptr + 1);
            auto val2 = ram.resolve(resolveMode(rawOp, 1), ptr + 2);
            auto dest = ram.resolveImmediateMode(ptr + 3);
            ram.at(dest) = (int64_t) val1 == val2;
            ptr += 4;
        } break;

        case 99:
            // std::cout << "HALT" << std::endl;
            running = false;
            this->halted = true;
            break;
        default:
            [[unlikely]]
            throw std::runtime_error("Unknown opcode: " + std::to_string(op));
        }
    }

    // if (inspect != nullptr) {
    //     *inspect = ram;
    // }

    return ram.at(0);
}

int64_t IntCode::runUntilHalted(
    StdStream* in,
    Program* inspect
) {
    int64_t out;
    while (!halted) {
        out = run(in, inspect);
    }
    return out;
}

}
