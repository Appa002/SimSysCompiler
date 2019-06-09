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
    if(address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLValue = (CharLValueStructure *) address.get();

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