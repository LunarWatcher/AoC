#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>

namespace aoc2019 {

struct Opcode4 {
    int64_t val1, val2;
    int64_t destAddr;
};


struct Program {
    std::vector<int64_t> ram;

    int64_t resolveReference(
        size_t addr
    ) const {
        return ram.at(ram.at(addr));
    }

    int64_t resolveImmediateMode(
        size_t addr
    ) const {
        return ram.at(addr);
    }

    int64_t resolve(
        int64_t mode,
        size_t addr
    ) const {
        if (mode == 0) {
            return resolveReference(addr);
        } else if (mode == 1) {
            return resolveImmediateMode(addr);
        } else {
            [[unlikely]]
            throw std::runtime_error("Unrecognised mode: " + std::to_string(addr));
        }
    }

    int64_t& at(size_t n) { return ram.at(n); }
};

struct StdStream {
    std::vector<int64_t> data;
    /**
     * Read location; only used by input streams
     */
    size_t head = 0;

    int64_t next() { return data.at(head++); }
    void push(int64_t value) { data.push_back(value); }
};

class IntCode {
private:
    Opcode4 resolveOp4(
        const Program& ram,
        size_t opcodeAddr
    );
public:
    StdStream output;

    /**
     * Represents the source instructions.
     */
    Program source;
    /**
     * Represents the instructions we're working on.
     * This is usually a copy of source, but allows for per-part modifications of the instructions without needing to
     * reinitialise the intcode computer.
     */
    Program workingSet;

    IntCode() = default;
    IntCode(const std::vector<int64_t>& instructions);

    int64_t resolveReference(const Program& ram, size_t addr);
    int64_t resolveImmediateMode(const Program& ram, size_t addr);

    int64_t resolveMode(int64_t rawOp, short parameterIdx);

    void inputs(const std::vector<int64_t>& inputs);

    /**
     * Used to recode the working set. Pass an empty vector to reset workingSet to source.
     */
    void recode(
        const std::vector<std::pair<size_t, int64_t>>& modifications
    );

    int64_t run(
        StdStream in = {},
        Program* inspect = nullptr
    );

    int64_t diagnostic() {
        return output.data.back();
    }
};

}
