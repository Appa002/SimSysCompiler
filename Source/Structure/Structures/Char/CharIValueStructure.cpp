//
// Created by a_mod on 08.06.2019.
//

#include "CharIValueStructure.h"

//
// Created by a_mod on 07.06.2019.
//

#include "CharIValueStructure.h"
#include "CharLValueStructure.h"
#include "CharRValueStructure.h"
#include "Structure/Structures/Bool/BoolLValueStructure.h"
#include "Structure/Structures/Bool/BoolRValueStructure.h"
#include <Assembly/Code.h>
#include <General/utils.h>
#include <General/builtinTypes.h>
#include <Error/Errors.h>
#include <Structure/Structures/Number/NumIValueStructure.h>

ACC::CharIValueStructure::CharIValueStructure(uint8_t value) : value(value), CharStructure(ValueCategory::ivalue) {

}


void ACC::CharIValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(1, reg) + ", " + std::to_string(value));
}

std::string ACC::CharIValueStructure::getValue() const {
    return std::to_string(value);
}

std::shared_ptr<ACC::Structure> ACC::CharIValueStructure::operatorChar(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::CharIValueStructure::operatorNum(ACC::Code &code) {
    return std::make_shared<NumIValueStructure>((uint8_t)value);
}

std::shared_ptr<ACC::Structure> ACC::CharIValueStructure::operatorBool(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "char", "bool");
}

std::shared_ptr<ACC::Structure> ACC::CharIValueStructure::operatorPtr(ACC::Code &code, ACC::Type) {
    throw errors::TypeConversion(nullptr, "char", "ptr");
}

bool ACC::CharIValueStructure::hasConversionTo(const Type &id) {
    if(id == Type("char", 1))
        return true;
    else if (id == Type("num", 8))
        return true;

    return false;
}
