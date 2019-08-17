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

std::shared_ptr<ACC::Structure>
ACC::PtrIValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->type == Type(BuiltIns::numType)){
        auto thisAsNum = operatorNum(code);
        return thisAsNum->operatorCopy(address, code);
    }

    if(address->type != Type(BuiltIns::ptrType))
        throw errors::InvalidType(nullptr, "ImplementMe", "copy"); //TODO: Type system.

    if(address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLValue = dynamic_cast<AsmAccessible*>(address.get());

        auto &fn = code.getFnSymbol();

        fn.writeLine("mov qword [" + addressAsLValue->getAccess() + "], 0x" + toHex(value));
    }
    return address;
}


void ACC::PtrIValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", " + std::to_string(value));
}

uint64_t ACC::PtrIValueStructure::getValue() const {
    return value;
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

