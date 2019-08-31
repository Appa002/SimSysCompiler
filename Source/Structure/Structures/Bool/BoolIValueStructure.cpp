//
// Created by a_mod on 07.06.2019.
//

#include "BoolIValueStructure.h"
#include "Structure/Structures/Bool/BoolLValueStructure.h"
#include "Structure/Structures/Bool/BoolRValueStructure.h"
#include <Assembly/Code.h>
#include <General/utils.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Structure/Structures/Char/CharIValueStructure.h>
#include <Structure/Structures/Number/NumIValueStructure.h>
#include <Error/Errors.h>

ACC::BoolIValueStructure::BoolIValueStructure(bool value) : value(value),
BoolStructure(ValueCategory::ivalue) {

}

void ACC::BoolIValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", " + std::to_string(value));
}

std::shared_ptr<ACC::Structure> ACC::BoolIValueStructure::operatorChar(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "bool", "char");
}

std::shared_ptr<ACC::Structure> ACC::BoolIValueStructure::operatorNum(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "bool", "num");
}

std::shared_ptr<ACC::Structure> ACC::BoolIValueStructure::operatorBool(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::BoolIValueStructure::operatorPtr(Code &code, Type) {
    throw errors::TypeConversion(nullptr, "bool", "ptr");
}

bool ACC::BoolIValueStructure::hasConversionTo(const Type &id) {
    return id == Type("bool", 1);
}

std::string ACC::BoolIValueStructure::getValue() const {
    return value ? ("0") : ("1");
}

