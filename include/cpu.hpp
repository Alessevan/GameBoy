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
    uint8 subc(uint8);
    uint8 adc(uint8);
    uint8 and_(uint8);
    uint8 or_(uint8);
    uint8 xor_(uint8);
    void cp(uint8);
    void ccf(void);
    void scf(void);
    void rra(void);
    void rla(void);
    void rrca();
    void rlca();
    void cpl(void);
    void swap(uint8);
};
