//
// Created by a_mod on 07.06.2019.
//

#include "NumIValueStructure.h"
#include "NumRValueStructure.h"
#include "NumLValueStructure.h"
#include "Structure/Structures/Bool/BoolLValueStructure.h"
#include "Structure/Structures/Bool/BoolRValueStructure.h"
#include <Assembly/Code.h>
#include <General/utils.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Structure/Structures/Char/CharIValueStructure.h>
#include <Structure/Structures/Pointer/PtrIValueStructure.h>

ACC::NumIValueStructure::NumIValueStructure(int64_t value) : value(value), NumStructure(ValueCategory::ivalue) {

}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->type == Type(BuiltIns::charType)){
        auto thisAsChar = operatorChar(code);
        return thisAsChar->operatorCopy(address, code);
    } else if (address->type == Type(BuiltIns::ptrType)){
        auto thisAsPtr = operatorPtr(code, Type(address->type.getPointingTo()));
        return thisAsPtr->operatorCopy(address, code);
    }

    if(address->type != Type(BuiltIns::numType))
        throw std::runtime_error("Can't convert type `num` to receiving type.");


    if(address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLValue = dynamic_cast<AsmAccessible*>(address.get());

        auto &fn = code.getFnSymbol();


        fn.writeLine("mov qword [" + addressAsLValue->getAccess() + "], 0x" + toHex(value));
    }
    return address;
}


void ACC::NumIValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", " + std::to_string(value));
}

int64_t ACC::NumIValueStructure::getValue() const {
    return value;
}

std::shared_ptr<ACC::Structure> ACC::NumIValueStructure::operatorChar(ACC::Code &code) {
    return std::make_shared<CharIValueStructure>((uint8_t)value);
}

std::shared_ptr<ACC::Structure> ACC::NumIValueStructure::operatorNum(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::NumIValueStructure::operatorBool(ACC::Code &code) {
    throw std::runtime_error("Can't convert type `num` to type bool");
}

std::shared_ptr<ACC::Structure> ACC::NumIValueStructure::operatorPtr(Code &code, Type pointingTo) {
    return std::make_shared<PtrIValueStructure>(value, pointingTo);
}

