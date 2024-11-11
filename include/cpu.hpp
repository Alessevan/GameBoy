#pragma once
#include "instruction.hpp"
#include "registers.hpp"

class CPU {
public:
    Registers registers;
    uint16 pc;

public:
    CPU(void);
    void execute(Instruction);
    
    uint8 add(uint8);
    uint8 addhl(uint8);
    uint8 sub(uint8);
    uint8 sbc(uint8);
    uint8 adc(uint8);
    uint8 and_(uint8);
    uint8 or_(uint8);
    uint8 xor_(uint8);
    void cp(uint8);
    void inc(uint8);
    void dec(uint8);
    void ccf(void);
    void scf(void);
    void rra(void);
    void rla(void);
    void rrca(void);
    void rlca(void);
    void cpl(void);
    void bit(uint8, uint8);
    void reset(uint8, uint8);
    void set(uint8, uint8);
    void srl(uint8);
    void rr(uint8);
    void rl(uint8);
    void rrc(uint8);
    void rlc(uint8);
    void sra(uint8);
    void sla(uint8);
    void swap(uint8);
};
