//
// Created by a_mod on 07.06.2019.
//

#include "BoolLValueStructure.h"
#include <Assembly/Code.h>
#include <General/utils.h>
#include <General/builtinTypes.h>

ACC::BoolLValueStructure::BoolLValueStructure(std::string access)
        : BoolStructure(ValueCategory::lvalue), access(std::move(access))
{

}

std::string const &ACC::BoolLValueStructure::getAccess() {
    return access;
}

void ACC::BoolLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::BoolLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->vCategory == ValueCategory::lvalue) {
        auto &fn = code.getFnSymbol();
        auto *addressAsLValue = dynamic_cast<BoolLValueStructure *>(address.get());

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        fn.writeLine("mov " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->access + " ], " + regStr);

        code.freeRegister(reg);

        return address;
    }
    return nullptr;
}

