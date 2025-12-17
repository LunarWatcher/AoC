#include "IntCode.hpp"
#include <cmath>
#include <string>
#include <stdexcept>
#include <iostream>

namespace aoc2019 {

IntCode::IntCode(
    const Program& prog
) : ram(prog) {

}

void IntCode::recode(
    const std::vector<std::pair<size_t, int64_t>>& modifications
) {
    for (const auto& [pos, val] : modifications) {
        this->ram.ram.at(pos) = val;
    }
}

Opcode4 IntCode::resolveOp4(
    Program& ram,
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

int64_t IntCode::run() {
    // output.data.clear();

    bool running = true;
    while (running) {
        auto rawOp = ram.resolveImmediateMode(ptr);
        auto op = rawOp % 100;

        switch (op) {
        case 1: {
            auto val1 = ram.resolve(resolveMode(rawOp, 0), ptr + 1);
            auto val2 = ram.resolve(resolveMode(rawOp, 1), ptr + 2);
            auto dest = ram.resolveImmRelMode(resolveMode(rawOp, 2), ptr + 3);
            ram.at(dest) = val1 + val2;
            ptr += 4;
        } break;
        case 2: {
            auto val1 = ram.resolve(resolveMode(rawOp, 0), ptr + 1);
            auto val2 = ram.resolve(resolveMode(rawOp, 1), ptr + 2);
            auto dest = ram.resolveImmRelMode(resolveMode(rawOp, 2), ptr + 3);
            ram.at(dest) = val1 * val2;
            ptr += 4;
        } break;
        case 3: {
            auto dest = ram.resolveImmRelMode(resolveMode(rawOp, 0), ptr + 1);
            ram.at(dest) = input.next();
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
            auto dest = ram.resolveImmRelMode(resolveMode(rawOp, 2), ptr + 3);
            ram.at(dest) = (int64_t) val1 < val2;
            ptr += 4;
        } break;
        case 8: {
            auto val1 = ram.resolve(resolveMode(rawOp, 0), ptr + 1);
            auto val2 = ram.resolve(resolveMode(rawOp, 1), ptr + 2);
            auto dest = ram.resolveImmRelMode(resolveMode(rawOp, 2), ptr + 3);
            ram.at(dest) = (int64_t) val1 == val2;
            ptr += 4;
        } break;

        case 9: {
            auto val = ram.resolve(
                resolveMode(rawOp, 0), ptr + 1
            );
            ram.relativeBase += val;
            ram.ensureSpace(ram.relativeBase);
            ptr += 2;
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

int64_t IntCode::runUntilHalted() {
    int64_t out;
    while (!halted) {
        out = run();
    }
    return out;
}

}
