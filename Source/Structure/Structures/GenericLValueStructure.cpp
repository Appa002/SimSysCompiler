#include <utility>

//
// Created by a_mod on 07.06.2019.
//

#include <Assembly/Code.h>
#include "GenericLValueStructure.h"

ACC::GenericLValueStructure::GenericLValueStructure(ACC::Type type, std::string access)
: ElementaryStructure(ValueCategory::lvalue, type), access(std::move(access))
{

}

std::string const &ACC::GenericLValueStructure::getAccess() {
    return access;
}

void ACC::GenericLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::GenericLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->vCategory == ValueCategory::lvalue) {
        auto &fn = code.getFnSymbol();
        auto *addressAsLValue = dynamic_cast<GenericLValueStructure *>(address.get());

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        fn.writeLine("mov " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->access + " ], " + regStr);

        return address;
    }
    return nullptr;
}

