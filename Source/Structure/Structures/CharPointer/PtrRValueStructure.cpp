#include <utility>

//
// Created by a_mod on 07.06.2019.
//

#include "PtrRValueStructure.h"
#include "PtrLValueStructure.h"
#include <General/builtinTypes.h>
#include <Assembly/Code.h>

ACC::PtrRValueStructure::PtrRValueStructure(std::string access, Type type)
: PtrStructure(ValueCategory::rvalue, type), access(std::move(access)) {

}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->vCategory == ValueCategory::lvalue){
        auto &fn = code.getFnSymbol();
        auto *addressAsLValue = dynamic_cast<GenericLValueStructure *>(address.get());

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        fn.writeLine("lea " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);

        return std::make_shared<PtrLValueStructure>(addressAsLValue->getAccess());
    }
    return nullptr;
}

void ACC::PtrRValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("lea " + registerToString(8, reg) + ", [" + access + "]");
}


