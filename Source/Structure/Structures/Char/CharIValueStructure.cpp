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

ACC::CharIValueStructure::CharIValueStructure(uint8_t value) : value(value), CharStructure(ValueCategory::ivalue) {

}

std::shared_ptr<ACC::Structure>
ACC::CharIValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->type == Type(BuiltIns::numType)){
        auto asNum = this->operatorNum(code);
        asNum->operatorCopy(address, code);
    }

    if(address->type  != Type(BuiltIns::charType))
        throw std::runtime_error("Can't convert type `char` to receiving type.");


    if(address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLValue = dynamic_cast<AsmAccessible*>(address.get());

        auto &fn = code.getFnSymbol();

        fn.writeLine("mov byte [" + addressAsLValue->getAccess() + "], 0x" +  toHex(value));
    }
    return address;
}


void ACC::CharIValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(1, reg) + ", " + std::to_string(value));
}

uint8_t ACC::CharIValueStructure::getValue() const {
    return value;
}

std::shared_ptr<ACC::Structure> ACC::CharIValueStructure::operatorChar(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::CharIValueStructure::operatorNum(ACC::Code &code) {
    throw std::runtime_error("No implicit conversion of type `char` to type `num`.");
}

std::shared_ptr<ACC::Structure> ACC::CharIValueStructure::operatorBool(ACC::Code &code) {
    throw std::runtime_error("No implicit conversion of type `char` to type `bool`.");
}

std::shared_ptr<ACC::Structure> ACC::CharIValueStructure::operatorPtr(ACC::Code &code, ACC::Type) {
    throw std::runtime_error("No implicit conversion of type `char` to type `ptr`.");
}
