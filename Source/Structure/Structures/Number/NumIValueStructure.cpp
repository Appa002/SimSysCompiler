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

ACC::NumIValueStructure::NumIValueStructure(int64_t value) : value(value), NumStructure(ValueCategory::ivalue) {

}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLValue = (NumLValueStructure *) address.get();

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
