#include <stdio.h>
#include <stdlib.h>
#include "cpu.hpp"
#define TODO printf("TO BE IMPLEMENTED\n");

CPU::CPU(void) {
    this->registers = Registers();
    this->bus = MemoryBus();
    this->pc = 0;
}

void CPU::step(void) {
    uint8 instruction_byte = this->bus.read_byte(this->pc);
    bool prefixed = instruction_byte == 0xCB;
    if (prefixed) {
        instruction_byte = this->bus.read_byte(this->pc + 1);
    }

    Instruction instruction = Instruction::from_byte(instruction_byte, prefixed);
    if (instruction.getId() == INSTR_ERR) {
        exit(-1);
    }

    this->pc = this->execute(instruction);
}

uint16 CPU::execute(Instruction instruction) {
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

    case INSTR_ADDHL16: {
        InstructionData data = instruction.getData();
        Target16Register reg = ((Addhl16InstructionData&) data).get_target();
        uint8 val = *((&this->registers.af) + reg);
        this->registers.hl = this->addhl16(val);
        break;
    }

    case INSTR_ADC: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((AdcInstructionData&) data).getTarget();
        uint8 val = *((&this->registers.a) + reg);
        this->registers.a = this->adc(val);
        break;
    }

    case INSTR_SUB: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((SubInstructionData&) data).getTarget();
        uint8 val = *((&this->registers.a) + reg);
        this->registers.a = this->sub(val);
        break;
    }
        
    case INSTR_SBC: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((SbcInstructionData&) data).getTarget();
        uint8 val = *((&this->registers.a) + reg);
        this->registers.a = this->sub(val);
        break;
    }

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

    case INSTR_CP: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((CpInstructionData&) data).getTarget();
        uint8 val = *((&this->registers.a) + reg);
        this->cp(val);
        break;
    }

    case INSTR_INC: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((IncInstructionData&) data).getTarget();
        this->inc(reg);
        break;
    }

    case INSTR_INC16: {
        InstructionData data = instruction.getData();
        Target16Register reg = ((Inc16InstructionData&) data).get_target();
        this->inc16(reg);
        break;
    }

    case INSTR_DEC: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((DecInstructionData&) data).getTarget();
        this->dec(reg);
        break;
    }

    case INSTR_DEC16: {
        InstructionData data = instruction.getData();
        Target16Register reg = ((Dec16InstructionData&) data).get_target();
        this->dec16(reg);
        break;
    }

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

    case INSTR_BIT: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((BitInstructionData&) data).getTarget();
        uint8 bit = ((BitInstructionData&) data).get_bit_position();
        this->bit(reg, bit);
        break;
    }

    case INSTR_RESET: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((ResetInstructionData&) data).getTarget();
        uint8 bit = ((ResetInstructionData&) data).get_bit_position();
        this->reset(reg, bit);
        break;
    }

    case INSTR_SET: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((SetInstructionData&) data).getTarget();
        uint8 bit = ((SetInstructionData&) data).get_bit_position();
        this->set(reg, bit);
        break;
    }

    case INSTR_SRL: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((SrlInstructionData&) data).getTarget();
        this->srl(reg);
        break;
    }

    case INSTR_RR: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((RrInstructionData&) data).getTarget();
        this->rr(reg);
        break;
    }
       
    case INSTR_RL: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((RlInstructionData&) data).getTarget();
        this->rl(reg);
        break;
    }

    case INSTR_RRC: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((RrcInstructionData&) data).getTarget();
        this->rrc(reg);
        break;
    }

    case INSTR_RLC: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((RlcInstructionData&) data).getTarget();
        this->rlc(reg);
        break;
    }

    case INSTR_SRA: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((SraInstructionData&) data).getTarget();
        this->sra(reg);
        break;
    }

    case INSTR_SLA: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((SlaInstructionData&) data).getTarget();
        this->sla(reg);
        break;
    }

    case INSTR_SWAP: {
        InstructionData data = instruction.getData();
        TargetRegister reg = ((SwapInstructionData&) data).getTarget();
        this->swap(reg);
        break;
    }

    case INSTR_ERR: {
        exit(-2);
    }
    };
    return this->pc + 1;
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

uint16 CPU::addhl16(uint16 value) {
    uint16 new_val = this->registers.hl + value;
    this->registers.f.C = new_val < this->registers.hl && new_val < value;
    this->registers.f.Z = new_val == 0;
    this->registers.f.S = false;
    this->registers.f.H = (this->registers.hl & 0xFF) + (value & 0xFF) > 0xF;
    return new_val;
}


uint8 CPU::adc(uint8 value) {
    uint16 new_val = (uint16) this->registers.a + (uint16) value + (uint16) this->registers.f.C;
    this->registers.f.C = new_val > 0xFF;
    this->registers.f.Z = (new_val & 0xFF) == 0;
    this->registers.f.S = false;
    this->registers.f.H = ((this->registers.a ^ value ^ new_val) & 0x10) > 0;
    return (uint8) (new_val & 0xFF);
}

uint8 CPU::sub(uint8 value) {
    uint8 sub_val = this->registers.a - value;
    this->registers.f.Z = sub_val == 0;
    this->registers.f.S = true;
    this->registers.f.H = (sub_val & 0x0F) > (this->registers.a & 0x0F);
    this->registers.f.C = sub_val > this->registers.a;
    return sub_val;
}

uint8 CPU::sbc(uint8 value) {
    uint8 sbc_val = this->registers.a - value - this->registers.f.C;
    this->registers.f.Z = sbc_val == 0;
    this->registers.f.S = true;
    this->registers.f.H = (sbc_val & 0x0F) > (this->registers.a & 0x0F);
    this->registers.f.C = sbc_val > this->registers.a;
    return sbc_val;
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

void CPU::inc(uint8 reg) {
    uint8 *reg_ptr = &this->registers.a + reg;
    ++*reg_ptr;
    this->registers.f.Z = *reg_ptr == 0;
    this->registers.f.S = false;
    this->registers.f.H = (this->registers.a & 0xF) + 1 > 0xF;
}

void CPU::inc16(uint16 reg) {
    uint16 *reg_ptr = &this->registers.af + reg;
    ++*reg_ptr;
}

void CPU::dec(uint8 reg) {
    uint8 *reg_ptr = &this->registers.a + reg;
    uint8 old_val = *reg_ptr;
    --*reg_ptr;
    this->registers.f.Z = *reg_ptr == 0;
    this->registers.f.S = false;
    this->registers.f.H = (*reg_ptr & 0x0F) > (old_val & 0x0F);
}

void CPU::dec16(uint16 reg) {
    uint16 *reg_ptr = &this->registers.af + reg;
    --*reg_ptr;
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
    uint8 bit = (this->registers.a & 0x80) >> 7;
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
    uint8 bit = (this->registers.a & 0x80) >> 7;
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

void CPU::bit(uint8 reg, uint8 b) {
    this->registers.f.Z = *((&this->registers.a) + reg) & (0b1 << b);
    this->registers.f.S = false;
    this->registers.f.H = true;
}

void CPU::reset(uint8 reg, uint8 b) {
    *((&this->registers.a) + reg) &= ~(0b1 << b);
}

void CPU::set(uint8 reg, uint8 b) {
    *((&this->registers.a) + reg) |= (0b1 << b);
}

void CPU::srl(uint8 reg) {
    *((&this->registers.a) + reg) >>= 1;
    *((&this->registers.a) + reg) &= ~0x80;
}

void CPU::rr(uint8 reg) {
    uint8 *reg_ptr = &this->registers.a + reg;
    uint8 bit = *reg_ptr & 0b1;
    *reg_ptr >>= 1;
    *reg_ptr &= ~(0x80);
    *reg_ptr |= (this->registers.f.C ? 1 : 0) << 7;
    this->registers.f.Z = *reg_ptr == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = bit == 1;
}

void CPU::rl(uint8 reg) {
    uint8 *reg_ptr = (&this->registers.a) + reg;
    uint8 bit = (*reg_ptr & 0x80) >> 7;
    *reg_ptr <<= 1;
    *reg_ptr &= ~(0x80);
    *reg_ptr |= (this->registers.f.C ? 1 : 0);
    this->registers.f.Z = *reg_ptr == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = bit == 1;
}

void CPU::rrc(uint8 reg) {
    uint8 *reg_ptr = &this->registers.a + reg;
    uint8 bit = *reg_ptr & 0b1;
    *reg_ptr >>= 1;
    *reg_ptr &= ~(0x80);
    *reg_ptr |= bit << 7;
    this->registers.f.Z = *reg_ptr == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = bit == 1;
}

void CPU::rlc(uint8 reg) {
    uint8 *reg_ptr = &this->registers.a + reg;
    uint8 bit = (*reg_ptr & 0x80) >> 7;
    *reg_ptr <<= 1;
    *reg_ptr &= ~(0b1);
    *reg_ptr |= bit;
    this->registers.f.Z = *reg_ptr == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = bit == 1;
}

void CPU::sra(uint8 reg) {
    uint8 *reg_ptr = &this->registers.a + reg;
    uint8 bit = *reg_ptr & 0b1;
    *reg_ptr >>= 1;
    *reg_ptr |= (*reg_ptr & 0x7F) << 7;
    this->registers.f.Z = *reg_ptr == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = bit == 1;
}

void CPU::sla(uint8 reg) {
    uint8 *reg_ptr = &this->registers.a + reg;
    uint8 bit = (*reg_ptr & 0x80) >> 7;
    *reg_ptr <<= 1;
    *reg_ptr |= bit << 7;
    this->registers.f.Z = *reg_ptr == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = bit == 1;
}

void CPU::swap(uint8 reg) {
    uint8 *reg_ptr = (&this->registers.a) + reg;
    uint8 upper = (*reg_ptr) >> 4;
    *reg_ptr <<= 4;
    *reg_ptr |= upper;
    this->registers.f.Z = *reg_ptr == 0;
    this->registers.f.S = false;
    this->registers.f.H = false;
    this->registers.f.C = false;
}
