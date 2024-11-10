#include "instruction.hpp"

Instruction::Instruction(InstructionId id, InstructionData data) {
    this->id = id;
    this->data = data;
}

InstructionId Instruction::getId(void) {
    return this->id;
}

InstructionData Instruction::getData(void) {
    return this->data;
}

TargetRegister TargetInstructionData::getTarget(void) {
    return this->target;
}
