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

std::shared_ptr<ACC::Structure>
ACC::BoolIValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->type != Type(BuiltIns::boolType))
        throw errors::InvalidType(nullptr, "ImplementMe", "copy"); //TODO: Type system.

    if(address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLValue = dynamic_cast<AsmAccessible*>(address.get());

        auto &fn = code.getFnSymbol();

        std::string valueAsString = value ? ("1") : ("0");

        fn.writeLine("mov byte [" + addressAsLValue->getAccess() + "], " + valueAsString);
    }
    return address;
}


void ACC::BoolIValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", " + std::to_string(value));
}

bool ACC::BoolIValueStructure::getValue() const {
    return value;
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

