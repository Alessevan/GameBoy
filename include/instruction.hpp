#pragma once
#include "integers.hpp"

enum InstructionId {
    INSTR_NOP,
    INSTR_ADD,
    INSTR_ADDHL,
    INSTR_ADDHL16,
    INSTR_ADC,
    INSTR_SUB,
    INSTR_SBC,
    INSTR_AND,
    INSTR_OR,
    INSTR_XOR,
    INSTR_CP,
    INSTR_INC,
    INSTR_INC16,
    INSTR_DEC,
    INSTR_DEC16,
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
    INSTR_SWAP,
    INSTR_JP,
    INSTR_JR,
    INSTR_JPI,
    INSTR_LOAD,
    INSTR_LOAD16,
    INSTR_ERR = 0xFFFF
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
    L = 0x05,
    IMMEDIATE = 0xFE,
    HL_PTR = 0xFF
};

enum Target16Register {
    BC = 0x01,
    DE = 0x02,
    HL = 0x03,
    SP = 0xFF
};

class TargetInstructionData : public InstructionData {
    TargetRegister target;
protected:
    TargetInstructionData(TargetRegister);
public:
    TargetRegister get_target(void);

    friend class Instruction;
};

class Target16InstructionData : public InstructionData {
    Target16Register target;
protected:
    Target16InstructionData(Target16Register);
public:
    Target16Register get_target(void);

    friend class Instruction;
};

class NoInstructionData : public InstructionData {
};

class Instruction {
    InstructionId id;
    InstructionData data;
    static Instruction from_byte_prefixed(uint8);
    static Instruction from_byte_not_prefixed(uint8);
public:
    Instruction(InstructionId, InstructionData);
    InstructionId get_id(void);
    InstructionData get_data(void);
    static Instruction from_byte(uint8, bool);
    friend class CPU;
};

class NoInstruction : public Instruction {
public:
    NoInstruction(void): Instruction(INSTR_NOP, NoInstructionData()) {}
};

class ErrorInstruction : public Instruction {
public:
    ErrorInstruction(void): Instruction(INSTR_ERR, NoInstructionData()) {}
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
 * ADDHL Instruction
 */
class Addhl16InstructionData : public Target16InstructionData {
    Addhl16InstructionData(Target16Register target) : Target16InstructionData(target) {}
    friend class Addhl16Instruction;
};

class Addhl16Instruction : public Instruction {
public:
    Addhl16Instruction(Target16Register reg) : Instruction(INSTR_ADDHL16, Addhl16InstructionData(reg)) {}
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
 * Inc Instruction
 */
class IncInstructionData : public TargetInstructionData {
    IncInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class IncInstruction;
};

class IncInstruction : public Instruction {
public:
    IncInstruction(TargetRegister reg) : Instruction(INSTR_INC, IncInstructionData(reg)) {}
};


/**
 * Inc16 Instruction
 */
class Inc16InstructionData : public Target16InstructionData {
    Inc16InstructionData(Target16Register target) : Target16InstructionData(target) {}
    friend class Inc16Instruction;
};

class Inc16Instruction : public Instruction {
public:
    Inc16Instruction(Target16Register reg) : Instruction(INSTR_INC16, Inc16InstructionData(reg)) {}
};

/**
 * Dec Instruction
 */
class DecInstructionData : public TargetInstructionData {
    DecInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class DecInstruction;
};

class DecInstruction : public Instruction {
public:
    DecInstruction(TargetRegister reg) : Instruction(INSTR_DEC, DecInstructionData(reg)) {}
};

/**
 * DEC16 Instruction
 */
class Dec16InstructionData : public Target16InstructionData {
    Dec16InstructionData(Target16Register target) : Target16InstructionData(target) {}
    friend class Dec16Instruction;
};

class Dec16Instruction : public Instruction {
public:
    Dec16Instruction(Target16Register reg) : Instruction(INSTR_DEC16, Dec16InstructionData(reg)) {}
};


/**
 * CCF Instruction
 */
class CcfInstruction : public Instruction {
public:
    CcfInstruction(void): Instruction(INSTR_CCF, NoInstructionData()) {}
};

/**
 * SCF Instruction
 */
class ScfInstruction : public Instruction {
public:
    ScfInstruction(void): Instruction(INSTR_SCF, NoInstructionData()) {}
};

/**
 * RRA Instruction
 */
class RraInstruction : public Instruction {
public:
    RraInstruction(void): Instruction(INSTR_RRA, NoInstructionData()) {}
};

/**
 * RLA Instruction
 */
class RlaInstruction : public Instruction {
public:
    RlaInstruction(void): Instruction(INSTR_RLA, NoInstructionData()) {}
};

/**
 * RRCA Instruction
 */
class RrcaInstruction : public Instruction {
public:
    RrcaInstruction(void): Instruction(INSTR_RRCA, NoInstructionData()) {}
};

/**
 * RLCA Instruction
 */
class RlcaInstruction : public Instruction {
public:
    RlcaInstruction(void): Instruction(INSTR_RLCA, NoInstructionData()) {}
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
class BitInstructionData : public TargetInstructionData {

    BitInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class BitInstruction;
};

class BitInstruction : public Instruction {
public:
    BitInstruction(TargetRegister reg) : Instruction(INSTR_BIT, BitInstructionData(reg)) {}
};


/**
 * RESET Instruction
 */
class ResetInstructionData : public TargetInstructionData {

    ResetInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class ResetInstruction;
};

class ResetInstruction : public Instruction {
public:
    ResetInstruction(TargetRegister reg) : Instruction(INSTR_RESET, ResetInstructionData(reg)) {}
};

/**
 * RESET Instruction
 */
class SetInstructionData : public TargetInstructionData {

    SetInstructionData(TargetRegister target) : TargetInstructionData(target) {}
    friend class SetInstruction;
};

class SetInstruction : public Instruction {
public:
    SetInstruction(TargetRegister reg) : Instruction(INSTR_SET, SetInstructionData(reg)) {}
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

/**
 * JUMP Instruction
 */
enum JumpTest {
    NOT_ZERO,
    ZERO,
    NOT_CARRY,
    CARRY,
    ALWAYS
};

class JumpInstructionData : public InstructionData {
    JumpTest test;
    JumpInstructionData(JumpTest);
public:
    JumpTest get_test(void);
    friend class JpInstruction;
    friend class JrInstruction;
};

class JpInstruction : public Instruction {
public:
    JpInstruction(JumpTest test) : Instruction(INSTR_JP, JumpInstructionData(test)) {}
};

class JrInstruction : public Instruction {
public:
    JrInstruction(JumpTest test) : Instruction(INSTR_JR, JumpInstructionData(test)) {}
};

class JpiInstruction : public Instruction {
public:
    JpiInstruction() : Instruction(INSTR_JPI, NoInstructionData()) {}
};


/**
 * LOAD
 */
enum LoadTarget {
    LDT_A,
    LDT_B,
    LDT_C,
    LDT_C_PTR,
    LDT_D,
    LDT_E,
    LDT_H,
    LDT_L,
    LDT_BC_PTR,
    LDT_DE_PTR,
    LDT_HL_PTR,
    LDT_HL_D_PTR,
    LDT_HL_I_PTR,
    LDT_IMMEDIATE_PTR,
    LDT_IMMEDIATE_BYTE_PTR
};

enum LoadSource {
    LDS_A,
    LDS_B,
    LDS_C,
    LDS_C_PTR,
    LDS_D,
    LDS_E,
    LDS_H,
    LDS_L,
    LDS_BC_PTR,
    LDS_DE_PTR,
    LDS_HL_PTR,
    LDS_HL_D_PTR,
    LDS_HL_I_PTR,
    LDS_IMMEDIATE_VALUE,
    LDS_IMMEDIATE_PTR,
    LDS_IMMEDIATE_BYTE_PTR
};

class LoadInstructionData: public InstructionData {
    LoadTarget target;
    LoadSource source;
    LoadInstructionData(LoadTarget, LoadSource);
public:
    LoadTarget get_target(void);
    LoadSource get_source(void);
    friend class LoadInstruction;
};

class LoadInstruction: public Instruction {
public:
    LoadInstruction(LoadTarget target, LoadSource source): Instruction(INSTR_LOAD, LoadInstructionData(target, source)) {}
};


enum Load16Target {
    LDT16_BC,
    LDT16_DE,
    LDT16_HL,
    LDT16_SP,
    LDT16_IMMEDIATE_PTR
};

enum Load16Source {
    LDS16_HL,
    LDS16_SP,
    LDS16_IMMEDIATE_SP,
    LDS16_IMMEDIATE_VALUE,
};

class Load16InstructionData: public InstructionData {
    Load16Target target;
    Load16Source source;
    Load16InstructionData(Load16Target, Load16Source);
public:
    Load16Target get_target(void);
    Load16Source get_source(void);
    friend class Load16Instruction;
};

class Load16Instruction: public Instruction {
public:
    Load16Instruction(Load16Target target, Load16Source source): Instruction(INSTR_LOAD16, Load16InstructionData(target, source)) {}
};
