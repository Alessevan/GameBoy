#include "instruction.hpp"

Instruction::Instruction(InstructionId id, InstructionData data) {
    this->id = id;
    this->data = data;
}

TargetInstructionData::TargetInstructionData(TargetRegister target) {
    this->target = target;
}

Target16InstructionData::Target16InstructionData(Target16Register target) {
    this->target = target;
}

InstructionId Instruction::get_id(void) {
    return this->id;
}

InstructionData Instruction::get_data(void) {
    return this->data;
}

TargetRegister TargetInstructionData::get_target(void) {
    return this->target;
}

Instruction Instruction::from_byte(uint8 byte, bool prefixed) {
    return prefixed ? from_byte_prefixed(byte) : from_byte_not_prefixed(byte);
}

Instruction Instruction::from_byte_prefixed(uint8 byte) {
    switch (byte) {
    case 0x37:
        return SwapInstruction(A);
    case 0x30:
        return SwapInstruction(B);
    case 0x31:
        return SwapInstruction(C);
    case 0x32:
        return SwapInstruction(D);
    case 0x33:
        return SwapInstruction(E);
    case 0x34:
        return SwapInstruction(H);
    case 0x35:
        return SwapInstruction(L);
    case 0x36:
        return SwapInstruction(HL_PTR);

    case 0x07:
        return RlcInstruction(A);
    case 0x00:
        return RlcInstruction(B);
    case 0x01:
        return RlcInstruction(C);
    case 0x02:
        return RlcInstruction(D);
    case 0x03:
        return RlcInstruction(E);
    case 0x04:
        return RlcInstruction(H);
    case 0x05:
        return RlcInstruction(L);
    case 0x06:
        return RlcInstruction(HL_PTR);

    case 0x17:
        return RlInstruction(A);
    case 0x10:
        return RlInstruction(B);
    case 0x11:
        return RlInstruction(C);
    case 0x12:
        return RlInstruction(D);
    case 0x13:
        return RlInstruction(E);
    case 0x14:
        return RlInstruction(H);
    case 0x15:
        return RlInstruction(L);
    case 0x16:
        return RlInstruction(HL_PTR);

    case 0x0F:
        return RrcInstruction(A);
    case 0x08:
        return RrcInstruction(B);
    case 0x09:
        return RrcInstruction(C);
    case 0x0A:
        return RrcInstruction(D);
    case 0x0B:
        return RrcInstruction(E);
    case 0x0C:
        return RrcInstruction(H);
    case 0x0D:
        return RrcInstruction(L);
    case 0x0E:
        return RrcInstruction(HL_PTR);

    case 0x1F:
        return RrInstruction(A);
    case 0x18:
        return RrInstruction(B);
    case 0x19:
        return RrInstruction(C);
    case 0x1A:
        return RrInstruction(D);
    case 0x1B:
        return RrInstruction(E);
    case 0x1C:
        return RrInstruction(H);
    case 0x1D:
        return RrInstruction(L);
    case 0x1E:
        return RrInstruction(HL_PTR);

    case 0x27:
        return SlaInstruction(A);
    case 0x20:
        return SlaInstruction(B);
    case 0x21:
        return SlaInstruction(C);
    case 0x22:
        return SlaInstruction(D);
    case 0x23:
        return SlaInstruction(E);
    case 0x24:
        return SlaInstruction(H);
    case 0x25:
        return SlaInstruction(L);
    case 0x26:
        return SlaInstruction(HL_PTR);

    case 0x2F:
        return SraInstruction(A);
    case 0x28:
        return SraInstruction(B);
    case 0x29:
        return SraInstruction(C);
    case 0x2A:
        return SraInstruction(D);
    case 0x2B:
        return SraInstruction(E);
    case 0x2C:
        return SraInstruction(H);
    case 0x2D:
        return SraInstruction(L);
    case 0x2E:
        return SraInstruction(HL_PTR);

    case 0x3F:
        return SrlInstruction(A);
    case 0x38:
        return SrlInstruction(B);
    case 0x39:
        return SrlInstruction(C);
    case 0x3A:
        return SrlInstruction(D);
    case 0x3B:
        return SrlInstruction(E);
    case 0x3C:
        return SrlInstruction(H);
    case 0x3D:
        return SrlInstruction(L);
    case 0x3E:
        return SrlInstruction(HL_PTR);

    case 0x47:
        return BitInstruction(A);
    case 0x40:
        return BitInstruction(B);
    case 0x41:
        return BitInstruction(C);
    case 0x42:
        return BitInstruction(D);
    case 0x43:
        return BitInstruction(E);
    case 0x44:
        return BitInstruction(H);
    case 0x45:
        return BitInstruction(L);
    case 0x46:
        return BitInstruction(HL_PTR);

    case 0xC7:
        return SetInstruction(A);
    case 0xC0:
        return SetInstruction(B);
    case 0xC1:
        return SetInstruction(C);
    case 0xC2:
        return SetInstruction(D);
    case 0xC3:
        return SetInstruction(E);
    case 0xC4:
        return SetInstruction(H);
    case 0xC5:
        return SetInstruction(L);
    case 0xC6:
        return SetInstruction(HL_PTR);

    case 0x87:
        return ResetInstruction(A);
    case 0x80:
        return ResetInstruction(B);
    case 0x81:
        return ResetInstruction(C);
    case 0x82:
        return ResetInstruction(D);
    case 0x83:
        return ResetInstruction(E);
    case 0x84:
        return ResetInstruction(H);
    case 0x85:
        return ResetInstruction(L);
    case 0x86:
        return ResetInstruction(HL_PTR);

    default:
        return ErrorInstruction();
    }
    return ErrorInstruction();
}

Instruction Instruction::from_byte_not_prefixed(uint8 byte) {
    switch (byte) {
    case 0x87:
        return AddInstruction(A);
    case 0x80:
        return AddInstruction(B);
    case 0x81:
        return AddInstruction(C);
    case 0x82:
        return AddInstruction(D);
    case 0x83:
        return AddInstruction(E);
    case 0x84:
        return AddInstruction(H);
    case 0x85:
        return AddInstruction(L);
    case 0x86:
        return AddInstruction(HL_PTR);
        // TODO: ADD A,# C6

    case 0x8F:
        return AdcInstruction(A);
    case 0x88:
        return AdcInstruction(B);
    case 0x89:
        return AdcInstruction(C);
    case 0x8A:
        return AdcInstruction(D);
    case 0x8B:
        return AdcInstruction(E);
    case 0x8C:
        return AdcInstruction(H);
    case 0x8D:
        return AdcInstruction(L);
    case 0x8E:
        return AdcInstruction(HL_PTR);
        // TODO: ADC A, # CE

    case 0x97:
        return SubInstruction(A);
    case 0x90:
        return SubInstruction(B);
    case 0x91:
        return SubInstruction(C);
    case 0x92:
        return SubInstruction(D);
    case 0x93:
        return SubInstruction(E);
    case 0x94:
        return SubInstruction(H);
    case 0x95:
        return SubInstruction(L);
    case 0x96:
        return SubInstruction(HL_PTR);
        // TODO: add SUB # D6

    case 0x9F:
        return SbcInstruction(A);
    case 0x98:
        return SbcInstruction(B);
    case 0x99:
        return SbcInstruction(C);
    case 0x9A:
        return SbcInstruction(D);
    case 0x9B:
        return SbcInstruction(E);
    case 0x9C:
        return SbcInstruction(H);
    case 0x9D:
        return SbcInstruction(L);
    case 0x9E:
        return SbcInstruction(HL_PTR);
        // TODO: SBC A, # ??

    case 0xA7:
        return AndInstruction(A);
    case 0xA0:
        return AndInstruction(B);
    case 0xA1:
        return AndInstruction(C);
    case 0xA2:
        return AndInstruction(D);
    case 0xA3:
        return AndInstruction(E);
    case 0xA4:
        return AndInstruction(H);
    case 0xA5:
        return AndInstruction(L);
    case 0xA6:
        return AndInstruction(HL_PTR);
        // TODO: AND # E6

    case 0xB7:
        return OrInstruction(A);
    case 0xB0:
        return OrInstruction(B);
    case 0xB1:
        return OrInstruction(C);
    case 0xB2:
        return OrInstruction(D);
    case 0xB3:
        return OrInstruction(E);
    case 0xB4:
        return OrInstruction(H);
    case 0xB5:
        return OrInstruction(L);
    case 0xB6:
        return OrInstruction(HL_PTR);
        // TODO: OR # F6

    case 0xAF:
        return XorInstruction(A);
    case 0xA8:
        return XorInstruction(B);
    case 0xA9:
        return XorInstruction(C);
    case 0xAA:
        return XorInstruction(D);
    case 0xAB:
        return XorInstruction(E);
    case 0xAC:
        return XorInstruction(H);
    case 0xAD:
        return XorInstruction(L);
    case 0xAE:
        return XorInstruction(HL_PTR);
        // TODO: XOR # EE

    case 0xBF:
        return CpInstruction(A);
    case 0xB8:
        return CpInstruction(B);
    case 0xB9:
        return CpInstruction(C);
    case 0xBA:
        return CpInstruction(D);
    case 0xBB:
        return CpInstruction(E);
    case 0xBC:
        return CpInstruction(H);
    case 0xBD:
        return CpInstruction(L);
    case 0xBE:
        return CpInstruction(HL_PTR);
        // TODO: CP # FE

    case 0x3C:
        return IncInstruction(A);
    case 0x04:
        return IncInstruction(B);
    case 0x0C:
        return IncInstruction(C);
    case 0x14:
        return IncInstruction(D);
    case 0x1C:
        return IncInstruction(E);
    case 0x24:
        return IncInstruction(H);
    case 0x2C:
        return IncInstruction(L);
    case 0x34:
        return IncInstruction(HL_PTR);

    case 0x3D:
        return DecInstruction(A);
    case 0x05:
        return DecInstruction(B);
    case 0x0D:
        return DecInstruction(C);
    case 0x15:
        return DecInstruction(D);
    case 0x1D:
        return DecInstruction(E);
    case 0x25:
        return DecInstruction(H);
    case 0x2D:
        return DecInstruction(L);
    case 0x35:
        return DecInstruction(HL_PTR);

    case 0x09:
        return Addhl16Instruction(BC);
    case 0x19:
        return Addhl16Instruction(DE);
    case 0x29:
        return Addhl16Instruction(HL);
    case 0x39:
        return Addhl16Instruction(SP);
        // TODO: ADDSP

    case 0x03:
        return Inc16Instruction(BC);
    case 0x13:
        return Inc16Instruction(DE);
    case 0x23:
        return Inc16Instruction(HL);
    case 0x33:
        return Inc16Instruction(SP);

    case 0x0B:
        return Dec16Instruction(BC);
    case 0x1B:
        return Dec16Instruction(DE);
    case 0x2B:
        return Dec16Instruction(HL);
    case 0x3B:
        return Dec16Instruction(SP);

    case 0x2F:
        return CplInstruction();

    case 0x3F:
        return CcfInstruction();

    case 0x37:
        return ScfInstruction();

    case 0x07:
        return RlcaInstruction();
    case 0x17:
        return RlaInstruction();

    case 0x0F:
        return RrcaInstruction();
    case 0x1F:
        return RraInstruction();

    case 0x20:
        return JrInstruction(NOT_ZERO);
    case 0x28:
        return JrInstruction(ZERO);
    case 0x30:
        return JrInstruction(NOT_CARRY);
    case 0x38:
        return JrInstruction(CARRY);

    case 0xE9:
        return JpiInstruction();

    case 0x7F:
        return LoadInstruction(LDT_A, LDS_A);
    case 0x78:
        return LoadInstruction(LDT_A, LDS_B);
    case 0x79:
        return LoadInstruction(LDT_A, LDS_C);
    case 0x7A:
        return LoadInstruction(LDT_A, LDS_D);
    case 0x7B:
        return LoadInstruction(LDT_A, LDS_E);
    case 0x7C:
        return LoadInstruction(LDT_A, LDS_H);
    case 0x7D:
        return LoadInstruction(LDT_A, LDS_L);
    case 0x7E:
        return LoadInstruction(LDT_A, LDS_HL_PTR);

    case 0x40:
        return LoadInstruction(LDT_B, LDS_B);
    case 0x41:
        return LoadInstruction(LDT_B, LDS_C);
    case 0x42:
        return LoadInstruction(LDT_B, LDS_D);
    case 0x43:
        return LoadInstruction(LDT_B, LDS_E);
    case 0x44:
        return LoadInstruction(LDT_B, LDS_H);
    case 0x45:
        return LoadInstruction(LDT_B, LDS_L);
    case 0x46:
        return LoadInstruction(LDT_B, LDS_HL_PTR);

    case 0x48:
        return LoadInstruction(LDT_C, LDS_B);
    case 0x49:
        return LoadInstruction(LDT_C, LDS_C);
    case 0x4A:
        return LoadInstruction(LDT_C, LDS_D);
    case 0x4B:
        return LoadInstruction(LDT_C, LDS_E);
    case 0x4C:
        return LoadInstruction(LDT_C, LDS_H);
    case 0x4D:
        return LoadInstruction(LDT_C, LDS_L);
    case 0x4E:
        return LoadInstruction(LDT_C, LDS_HL_PTR);

    case 0x50:
        return LoadInstruction(LDT_D, LDS_B);
    case 0x51:
        return LoadInstruction(LDT_D, LDS_C);
    case 0x52:
        return LoadInstruction(LDT_D, LDS_D);
    case 0x53:
        return LoadInstruction(LDT_D, LDS_E);
    case 0x54:
        return LoadInstruction(LDT_D, LDS_H);
    case 0x55:
        return LoadInstruction(LDT_D, LDS_L);
    case 0x56:
        return LoadInstruction(LDT_D, LDS_HL_PTR);

    case 0x58:
        return LoadInstruction(LDT_E, LDS_B);
    case 0x59:
        return LoadInstruction(LDT_E, LDS_C);
    case 0x5A:
        return LoadInstruction(LDT_E, LDS_D);
    case 0x5B:
        return LoadInstruction(LDT_E, LDS_E);
    case 0x5C:
        return LoadInstruction(LDT_E, LDS_H);
    case 0x5D:
        return LoadInstruction(LDT_E, LDS_L);
    case 0x5E:
        return LoadInstruction(LDT_E, LDS_HL_PTR);

    case 0x60:
        return LoadInstruction(LDT_H, LDS_B);
    case 0x61:
        return LoadInstruction(LDT_H, LDS_C);
    case 0x62:
        return LoadInstruction(LDT_H, LDS_D);
    case 0x63:
        return LoadInstruction(LDT_H, LDS_E);
    case 0x64:
        return LoadInstruction(LDT_H, LDS_H);
    case 0x65:
        return LoadInstruction(LDT_H, LDS_L);
    case 0x66:
        return LoadInstruction(LDT_H, LDS_HL_PTR);

    case 0x68:
        return LoadInstruction(LDT_L, LDS_B);
    case 0x69:
        return LoadInstruction(LDT_L, LDS_C);
    case 0x6A:
        return LoadInstruction(LDT_L, LDS_D);
    case 0x6B:
        return LoadInstruction(LDT_L, LDS_E);
    case 0x6C:
        return LoadInstruction(LDT_L, LDS_H);
    case 0x6D:
        return LoadInstruction(LDT_L, LDS_L);
    case 0x6E:
        return LoadInstruction(LDT_L, LDS_HL_PTR);

    case 0x70:
        return LoadInstruction(LDT_HL_PTR, LDS_B);
    case 0x71:
        return LoadInstruction(LDT_HL_PTR, LDS_C);
    case 0x72:
        return LoadInstruction(LDT_HL_PTR, LDS_D);
    case 0x73:
        return LoadInstruction(LDT_HL_PTR, LDS_E);
    case 0x74:
        return LoadInstruction(LDT_HL_PTR, LDS_H);
    case 0x75:
        return LoadInstruction(LDT_HL_PTR, LDS_L);
    case 0x36:
        return LoadInstruction(LDT_HL_PTR, LDS_IMMEDIATE_VALUE);

    case 0x0A:
        return LoadInstruction(LDT_A, LDS_BC_PTR);
    case 0x1A:
        return LoadInstruction(LDT_A, LDS_DE_PTR);
    case 0xFA:
        return LoadInstruction(LDT_A, LDS_IMMEDIATE_PTR);
    case 0x3E:
        return LoadInstruction(LDT_A, LDS_IMMEDIATE_VALUE);

    case 0x47:
        return LoadInstruction(LDT_B, LDS_A);
    case 0x4F:
        return LoadInstruction(LDT_C, LDS_A);
    case 0x57:
        return LoadInstruction(LDT_D, LDS_A);
    case 0x5F:
        return LoadInstruction(LDT_E, LDS_A);
    case 0x67:
        return LoadInstruction(LDT_H, LDS_A);
    case 0x6F:
        return LoadInstruction(LDT_L, LDS_A);
    case 0x02:
        return LoadInstruction(LDT_BC_PTR, LDS_A);
    case 0x12:
        return LoadInstruction(LDT_DE_PTR, LDS_A);
    case 0x77:
        return LoadInstruction(LDT_HL_PTR, LDS_A);
    case 0xEA:
        return LoadInstruction(LDT_IMMEDIATE_PTR, LDS_A);

    case 0xF2:
        return LoadInstruction(LDT_A, LDS_C_PTR);
    case 0xE2:
        return LoadInstruction(LDT_C_PTR, LDS_A);

    case 0x3A:
        return LoadInstruction(LDT_A, LDS_HL_D_PTR);
    case 0x32:
        return LoadInstruction(LDT_HL_D_PTR, LDS_A);
    case 0x2A:
        return LoadInstruction(LDT_A, LDS_HL_I_PTR);
    case 0x22:
        return LoadInstruction(LDT_HL_I_PTR, LDS_A);

    case 0xE0:
        return LoadInstruction(LDT_IMMEDIATE_BYTE_PTR, LDS_A);
    case 0xF0:
        return LoadInstruction(LDT_A, LDS_IMMEDIATE_BYTE_PTR);

    case 0x01:
        return Load16Instruction(LDT16_BC, LDS16_IMMEDIATE_VALUE);
    case 0x11:
        return Load16Instruction(LDT16_DE, LDS16_IMMEDIATE_VALUE);
    case 0x21:
        return Load16Instruction(LDT16_HL, LDS16_IMMEDIATE_VALUE);
    case 0x31:
        return Load16Instruction(LDT16_SP, LDS16_IMMEDIATE_VALUE);

    case 0xF9:
        return Load16Instruction(LDT16_SP, LDS16_HL);
    case 0xF8:
        return Load16Instruction(LDT16_HL, LDS16_IMMEDIATE_SP);

    case 0x08:
        return Load16Instruction(LDT16_IMMEDIATE_PTR, LDS16_SP);

    case 0x00:
        return NoInstruction();
    default:
        return ErrorInstruction();
    }
    return ErrorInstruction();
}

Target16Register Target16InstructionData::get_target(void) {
    return this->target;
}

uint8 TargetBitInstructionData::get_bit_position(void) {
    return this->bit;
}

JumpInstructionData::JumpInstructionData(JumpTest test) {
    this->test = test;
}

JumpTest JumpInstructionData::get_test(void) {
    return this->test;
}

LoadInstructionData::LoadInstructionData(LoadTarget target, LoadSource source) {
    this->target = target;
    this->source = source;
}

LoadTarget LoadInstructionData::get_target(void) {
    return this->target;
}

LoadSource LoadInstructionData::get_source(void) {
    return this->source;
}


Load16InstructionData::Load16InstructionData(Load16Target target, Load16Source source) {
    this->target = target;
    this->source = source;
}

Load16Target Load16InstructionData::get_target(void) {
    return this->target;
}

Load16Source Load16InstructionData::get_source(void) {
    return this->source;
}
