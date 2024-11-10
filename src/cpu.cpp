#include <stdio.h>
#include "cpu.hpp"
#define TODO printf("TO BE IMPLEMENTED\n");

CPU::CPU(void) {
    this->registers = Registers();
    this->pc = 0;
}

void CPU::execute(Instruction instruction) {
    switch (instruction.getId()) {
    case INSTR_NOP: { break; }
    case INSTR_ADD: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((AddInstructionData&) data).getTarget();
        uint8 val = *((&this->registers.a) + reg);
        this->registers.a = this->add(val);
        break;
    }

    case INSTR_ADDHL: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((AddhlInstructionData&) data).getTarget();
        uint8 val = *((&this->registers.a) + reg);
        this->registers.a = this->addhl(val);
        break;
    }

    case INSTR_ADC: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((AdcInstructionData&) data).getTarget();
        uint8 val = *((&this->registers.a) + reg);
        this->registers.a = this->adc(val);
        break;
    }

    case INSTR_SUB:
    case INSTR_SBC:
        TODO;
        break;

    case INSTR_AND: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((AndInstructionData&) data).getTarget();
        uint8 val = *((&this->registers.a) + reg);
        this->registers.a = this->and_(val);
        break;
    }

    case INSTR_OR: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((OrInstructionData&) data).getTarget();
        uint8 val = *((&this->registers.a) + reg);
        this->registers.a = this->or_(val);
        break;
    }

    case INSTR_XOR: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((XorInstructionData&) data).getTarget();
        uint8 val = *((&this->registers.a) + reg);
        this->registers.a = this->xor_(val);
        break;
    }

    case INSTR_CP:
    case INSTR_INC:
    case INSTR_DEC:
        TODO;
        break;

    case INSTR_CCF: {
        this->ccf();
        break;
    }

    case INSTR_SCF: {
        this->scf();
        break;
    }

    case INSTR_RRA: {
        this->rra();
        break;
    }

    case INSTR_RLA: {
        this->rla();
        break;
    }

    case INSTR_RRCA: {
        this->rrca();
        break;
    }

    case INSTR_RLCA: {
        this->rlca();
        break;
    }

    case INSTR_CPL: {
        this->registers.a = ~this->registers.a;
        break;
    }

    case INSTR_BIT:
    case INSTR_RESET:
    case INSTR_SET:
    case INSTR_SRL:
    case INSTR_RR:
    case INSTR_RL:
    case INSTR_RRC:
    case INSTR_RRL:
    case INSTR_SRA:
    case INSTR_SLA:
        TODO;
        break;

    case INSTR_SWAP: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((SwapInstructionData&) data).getTarget();
        this->swap(reg);
        break;
    }
    }
}

uint8 CPU::add(uint8 value) {
    uint8 new_val = this->registers.a + value;
    this->registers.f.C = new_val < this->registers.a && new_val < value;
    this->registers.f.Z = new_val == 0;
    this->registers.f.S = false;
    this->registers.f.H = (this->registers.a & 0xF) + (value & 0xF) > 0xF;
    return new_val;
}

uint8 CPU::addhl(uint8 value) {
    uint8 val = this->add(value);
    this->registers.set_hl(this->registers.get_hl() + value);
    return val;
}

uint8 CPU::adc(uint8 value) {
    uint16 new_val = (uint16) this->registers.a + (uint16) value + (uint16) this->registers.f.C;
    this->registers.f.C = new_val > 0xFF;
    this->registers.f.Z = (new_val & 0xFF) == 0;
    this->registers.f.S = false;
    this->registers.f.H = ~((uint16) this->registers.a ^ (uint16) value) & ((uint16) this->registers.a ^ new_val);
    return (uint8) (new_val & 0xFF);
}

uint8 CPU::sub(uint8 value) {
    uint8 sub_val = this->registers.a - value;
    this->registers.f.Z = sub_val == 0;
    this->registers.f.S = true;
    this->registers.f.H = true;
    this->registers.f.C = false;
    return sub_val;
}

uint8 CPU::and_(uint8 value) {
    uint8 and_value = this->registers.a & value;
    this->registers.f.Z = and_value == 0;
    this->registers.f.S = false;
    this->registers.f.H = true;
    this->registers.f.C = false;
    return and_value;
}

uint8 CPU::or_(uint8 value) {
    uint8 or_value = this->registers.a | value;
    this->registers.f.Z = or_value == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = false;
    return or_value;
}

uint8 CPU::xor_(uint8 value) {
    uint8 xor_value = this->registers.a ^ value;
    this->registers.f.Z = xor_value == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = false;
    return xor_value;
}

void CPU::cp(uint8 value) {
    this->sub(value);
}

void CPU::ccf(void) {
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = true ^ this->registers.f.C;
}

void CPU::scf(void) {
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = true;
}

void CPU::rra(void) {
    uint8 bit = this->registers.a & 0b1;
    this->registers.a >>= 1;
    this->registers.a &= ~(0x80);
    this->registers.a |= (this->registers.f.C ? 1 : 0) << 7;
    this->registers.f.Z = this->registers.a == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = bit == 1;
}

void CPU::rla(void) {
    uint8 bit = this->registers.a & 0x80;
    this->registers.a <<= 1;
    this->registers.a &= ~(0b1);
    this->registers.a |= (this->registers.f.C ? 1 : 0);
    this->registers.f.Z = this->registers.a == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = bit == 1;
}

void CPU::rrca(void) {
    uint8 bit = this->registers.a & 0b1;
    this->registers.a >>= 1;
    this->registers.a &= ~(0x80);
    this->registers.a |= bit << 7;
    this->registers.f.Z = this->registers.a == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = bit == 1;
}

void CPU::rlca(void) {
    uint8 bit = this->registers.a & 0x80;
    this->registers.a <<= 1;
    this->registers.a &= ~(0b1);
    this->registers.a |= bit;
    this->registers.f.Z = this->registers.a == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = bit == 1;
}

void CPU::cpl(void) {
    this->registers.a = ~this->registers.a;
}

void CPU::swap(uint8 reg) {
    uint8 *reg_ptr = (&this->registers.a) + reg;
    uint8 upper = (*reg_ptr) >> 4;
    *reg_ptr <<= 4;
    *reg_ptr |= upper;
    this->registers.f.Z = *reg_ptr == 0;
    this->registers.f.S =false;
    this->registers.f.H = false;
    this->registers.f.C = false;
}
