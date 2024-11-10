#include "registers.hpp"

Registers::Registers(void) {
    for (int i = 0; i < 0x09; ++i) {
        *(((uint8 *) &this->a) + i) = 0;
    }
}

uint16 Registers::get_af(void) {
    return this->af;
}

void Registers::set_af(uint16 value) {
    this->af = value & 0xFFF0;
}

uint16 Registers::get_bc(void) {
    return this->bc;
}

void Registers::set_bc(uint16 value) {
    this->bc = value;
}

uint16 Registers::get_de(void) {
    return this->de;
}

void Registers::set_de(uint16 value) {
    this->de = value;
}

uint16 Registers::get_hl(void) {
    return this->hl;
}

void Registers::set_hl(uint16 value) {
    this->hl = value;
}
