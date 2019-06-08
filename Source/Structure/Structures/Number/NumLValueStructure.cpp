#include <utility>

//
// Created by a_mod on 03.06.2019.
//

#include "NumLValueStructure.h"
#include "NumRValueStructure.h"
#include "NumIValueStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"
#include "Structure/Structures/Bool/BoolRValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>

ACC::NumLValueStructure::NumLValueStructure(std::string const &access)
: NumStructure(ValueCategory::lvalue), access(access){

}

void ACC::NumLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::NumLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->vCategory == ValueCategory::lvalue) {
        auto &fn = code.getFnSymbol();
        auto *addressAsLValue = dynamic_cast<GenericLValueStructure *>(address.get());

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        fn.writeLine("mov " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);
        code.freeRegister(reg);

        return address;
    }
    return nullptr;
}

std::string ACC::NumLValueStructure::getAccess() const {
    return access;
}
