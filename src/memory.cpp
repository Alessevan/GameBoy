#include "memory.hpp"

MemoryBus::MemoryBus(void) {
    for (int i = 0; i < 0xFFFF; ++i)
        this->memory[i] = 0;
}

uint8 MemoryBus::read_byte(uint16 address) {
    return *(this->memory + address);
}

void MemoryBus::write_byte(uint16 address, uint8 value) {
    *(this->memory + address) = value;
}
