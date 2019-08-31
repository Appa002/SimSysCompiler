//
// Created by a_mod on 07.06.2019.
//

#include "PtrIValueStructure.h"
#include "PtrStructure.h"
#include "Structure/Structures/Bool/BoolLValueStructure.h"
#include "Structure/Structures/Bool/BoolRValueStructure.h"
#include <Assembly/Code.h>
#include <General/utils.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Structure/Structures/Char/CharIValueStructure.h>
#include <Structure/Structures/Number/NumIValueStructure.h>
#include <Error/Errors.h>

ACC::PtrIValueStructure::PtrIValueStructure(uint64_t value, Type pointingTo) : value(value),
PtrStructure(ValueCategory::ivalue, pointingTo) {

}


void ACC::PtrIValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", " + std::to_string(value));
}

std::string ACC::PtrIValueStructure::getValue() const {
    return std::to_string(value);
}



std::shared_ptr<ACC::Structure> ACC::PtrIValueStructure::operatorChar(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "char");
}

std::shared_ptr<ACC::Structure> ACC::PtrIValueStructure::operatorNum(ACC::Code &code) {
    return std::make_shared<NumIValueStructure>(value);
}

std::shared_ptr<ACC::Structure> ACC::PtrIValueStructure::operatorBool(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "bool");
}

std::shared_ptr<ACC::Structure> ACC::PtrIValueStructure::operatorPtr(Code &code, Type pointingTo) {
    return std::make_shared<PtrIValueStructure>(value, pointingTo);
}

bool ACC::PtrIValueStructure::hasConversionTo(const ACC::Type &id) {
    return id.isPtr;
}

