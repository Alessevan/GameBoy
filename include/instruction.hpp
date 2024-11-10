#pragma once

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
    INSTR_RRL,
    INSTR_SRA,
    INSTR_SLA,
    INSTR_SWAP
};

class InstructionData {
    friend class Instruction;
};

enum TargetRegister {
    A = 0x00,
    B = 0x01,
    C = 0x02,
    D = 0x03,
    E = 0x04,
    H = 0x05,
    L = 0x06
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
 * CPL Instruction
 */
class CplInstruction : public Instruction {
public:
    CplInstruction(void): Instruction(INSTR_CPL, NoInstructionData()) {}
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
