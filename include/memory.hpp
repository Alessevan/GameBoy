#pragma once
#include "integers.hpp"

class MemoryBus {
    uint8 memory[0xFFFF];

public:
    MemoryBus(void);
    uint8 read_byte(uint16);
    friend class CPU;
};
