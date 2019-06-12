//
// Created by a_mod on 08.06.2019.
//

#include "CharLValueStructure.h"

#include <utility>

//
// Created by a_mod on 03.06.2019.
//

#include "CharStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"
#include "Structure/Structures/Bool/BoolRValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>

ACC::CharLValueStructure::CharLValueStructure(std::string const &access)
        : CharStructure(ValueCategory::lvalue), access(access) {

}

void ACC::CharLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(1, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::CharLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code &code) {
    if (address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLValue = dynamic_cast<AsmAccessible *>(address.get());
        auto &fn = code.getFnSymbol();

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(1, reg);

        fn.writeLine("mov " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);
        code.freeRegister(reg);

        return address;
    }

    return nullptr;
}

std::string const &ACC::CharLValueStructure::getAccess() const {
    return access;
}



