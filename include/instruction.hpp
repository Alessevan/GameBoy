#pragma once
#include "integers.hpp"

enum InstructionId {
    INSTR_NOP,
    INSTR_ADD,
    INSTR_ADDHL,
    INSTR_ADC,
    INSTR_SUB,
    INSTR_SBC,
    INSTR_AND,
    INSTR_OR,
    INSTR_XOR,
    INSTR_CP,
    INSTR_INC,
    INSTR_DEC,
    INSTR_CCF,
    INSTR_SCF,
    INSTR_RRA,
    INSTR_RLA,
    INSTR_RRCA,
    INSTR_RLCA,
    INSTR_CPL,
    INSTR_BIT,
    INSTR_RESET,
    INSTR_SET,
    INSTR_SRL,
    INSTR_RR,
    INSTR_RL,
    INSTR_RRC,
    INSTR_RLC,
    INSTR_SRA,
    INSTR_SLA,
    INSTR_SWAP
};

class InstructionData {
    friend class Instruction;
};

enum TargetRegister {
    A = 0x00,
    B = 0x02,
    C = 0x01,
    D = 0x04,
    E = 0x03,
    H = 0x06,
    L = 0x05
};

class TargetInstructionData : public InstructionData {
    TargetRegister target;
protected:
    TargetInstructionData(TargetRegister);
public:
    TargetRegister getTarget(void);

    friend class Instruction;
};

class NoInstructionData : public InstructionData {
};

class Instruction {
    InstructionId id;
    InstructionData data;
public:
    Instruction(InstructionId, InstructionData);
    InstructionId getId(void);
    InstructionData getData(void);
    friend class CPU;
};

/**
 * ADD Instruction
 */
class AddInstructionData : public TargetInstructionData {
    AddInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class AddInstruction;
};

class AddInstruction : public Instruction {
public:
    AddInstruction(TargetRegister reg) : Instruction(INSTR_ADD, AddInstructionData(reg)) {}
};

/**
 * ADDHL Instruction
 */
class AddhlInstructionData : public TargetInstructionData {
    AddhlInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class AddhlInstruction;
};

class AddhlInstruction : public Instruction {
public:
    AddhlInstruction(TargetRegister reg) : Instruction(INSTR_ADDHL, AddhlInstructionData(reg)) {}
};

/**
 * ADC Instruction
 */
class AdcInstructionData : public TargetInstructionData {
    AdcInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class AdcInstruction;
};

class AdcInstruction : public Instruction {
public:
    AdcInstruction(TargetRegister reg) : Instruction(INSTR_ADC, AdcInstructionData(reg)) {}
};

/**
 * SUB Instruction
 */
class SubInstructionData : public TargetInstructionData {
    SubInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class SubInstruction;
};

class SubInstruction : public Instruction {
public:
    SubInstruction(TargetRegister reg) : Instruction(INSTR_SUB, SubInstructionData(reg)) {}
};

/**
 * SBC Instruction
 */
class SbcInstructionData : public TargetInstructionData {
    SbcInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class SbcInstruction;
};

class SbcInstruction : public Instruction {
public:
    SbcInstruction(TargetRegister reg) : Instruction(INSTR_SBC, SbcInstructionData(reg)) {}
};


/**
 * AND Instruction
 */
class AndInstructionData : public TargetInstructionData {
    AndInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class AndInstruction;
};

class AndInstruction : public Instruction {
public:
    AndInstruction(TargetRegister reg) : Instruction(INSTR_AND, AndInstructionData(reg)) {}
};


/**
 * OR Instruction
 */
class OrInstructionData : public TargetInstructionData {
    OrInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class OrInstruction;
};

class OrInstruction : public Instruction {
public:
    OrInstruction(TargetRegister reg) : Instruction(INSTR_OR, OrInstructionData(reg)) {}
}; 


/**
 * XOR Instruction
 */
class XorInstructionData : public TargetInstructionData {
    XorInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class XorInstruction;
};

class XorInstruction : public Instruction {
public:
    XorInstruction(TargetRegister reg) : Instruction(INSTR_XOR, XorInstructionData(reg)) {}
};


/**
 * CP Instruction
 */
class CpInstructionData : public TargetInstructionData {
    CpInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class CpInstruction;
};

class CpInstruction : public Instruction {
public:
    CpInstruction(TargetRegister reg) : Instruction(INSTR_CP, CpInstructionData(reg)) {}
};

/**
 * CPL Instruction
 */
class CplInstruction : public Instruction {
public:
    CplInstruction(void): Instruction(INSTR_CPL, NoInstructionData()) {}
};

class TargetBitInstructionData : public TargetInstructionData {
protected:
    uint8 bit;
    
    TargetBitInstructionData(TargetRegister target, uint8 bit) : TargetInstructionData(target) {
        this->bit = bit;
    }

public:
    uint8 get_bit_position(void);
};

/**
 * BIT Instruction
 */
class BitInstructionData : public TargetBitInstructionData {
    
    BitInstructionData(TargetRegister target, uint8 bit) : TargetBitInstructionData(target, bit) {}
    friend class BitInstruction;
};

class BitInstruction : public Instruction {
public:
    BitInstruction(TargetRegister reg, uint8 bit) : Instruction(INSTR_BIT, BitInstructionData(reg, bit)) {}
};


/**
 * RESET Instruction
 */
class ResetInstructionData : public TargetBitInstructionData {
    
    ResetInstructionData(TargetRegister target, uint8 bit) : TargetBitInstructionData(target, bit) {}
    friend class ResetInstruction;
};

class ResetInstruction : public Instruction {
public:
    ResetInstruction(TargetRegister reg, uint8 bit) : Instruction(INSTR_RESET, ResetInstructionData(reg, bit)) {}
};

/**
 * RESET Instruction
 */
class SetInstructionData : public TargetBitInstructionData {
    
    SetInstructionData(TargetRegister target, uint8 bit) : TargetBitInstructionData(target, bit) {}
    friend class SetInstruction;
};

class SetInstruction : public Instruction {
public:
    SetInstruction(TargetRegister reg, uint8 bit) : Instruction(INSTR_SET, SetInstructionData(reg, bit)) {}
};


/**
 * SRL Instruction
 */
class SrlInstructionData : public TargetInstructionData {
    SrlInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class SrlInstruction;
};

class SrlInstruction : public Instruction {
public:
    SrlInstruction(TargetRegister reg) : Instruction(INSTR_SRL, SrlInstructionData(reg)) {}
};

/**
 * RR Instruction
 */
class RrInstructionData : public TargetInstructionData {
    RrInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class RrInstruction;
};

class RrInstruction : public Instruction {
public:
    RrInstruction(TargetRegister reg) : Instruction(INSTR_RR, RrInstructionData(reg)) {}
};



/**
 * RL Instruction
 */
class RlInstructionData : public TargetInstructionData {
    RlInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class RlInstruction;
};

class RlInstruction : public Instruction {
public:
    RlInstruction(TargetRegister reg) : Instruction(INSTR_RL, RlInstructionData(reg)) {}
};

/**
 * RRC Instruction
 */
class RrcInstructionData : public TargetInstructionData {
    RrcInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class RrcInstruction;
};

class RrcInstruction : public Instruction {
public:
    RrcInstruction(TargetRegister reg) : Instruction(INSTR_RRC, RrcInstructionData(reg)) {}
};


/**
 * RLC Instruction
 */
class RlcInstructionData : public TargetInstructionData {
    RlcInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class RlcInstruction;
};

class RlcInstruction : public Instruction {
public:
    RlcInstruction(TargetRegister reg) : Instruction(INSTR_RLC, RlcInstructionData(reg)) {}
};


/**
 * SRA Instruction
 */
class SraInstructionData : public TargetInstructionData {
    SraInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class SraInstruction;
};

class SraInstruction : public Instruction {
public:
    SraInstruction(TargetRegister reg) : Instruction(INSTR_SRA, SraInstructionData(reg)) {}
};


/**
 * SLA Instruction
 */
class SlaInstructionData : public TargetInstructionData {
    SlaInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class SlaInstruction;
};

class SlaInstruction : public Instruction {
public:
    SlaInstruction(TargetRegister reg) : Instruction(INSTR_SLA, SlaInstructionData(reg)) {}
};

/**
 * SWAP Instruction
 */

class SwapInstructionData : public TargetInstructionData {
    SwapInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class SwapInstruction;
};

class SwapInstruction : public Instruction {
public:
    SwapInstruction(TargetRegister reg) : Instruction(INSTR_SWAP, SwapInstructionData(reg)) {}
};
