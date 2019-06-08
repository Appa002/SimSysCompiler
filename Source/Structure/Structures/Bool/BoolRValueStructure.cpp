//
// Created by a_mod on 07.06.2019.
//

#include <General/builtinTypes.h>
#include "BoolRValueStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"
#include "BoolLValueStructure.h"
#include <Assembly/Code.h>

ACC::BoolRValueStructure::BoolRValueStructure(ACC::Register reg) : BoolStructure(ValueCategory::rvalue), reg(reg){

}

std::shared_ptr<ACC::Structure>
ACC::BoolRValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->vCategory == ValueCategory::rvalue){
        auto addressAsBool = dynamic_cast<BoolRValueStructure*>(address.get());
        loadToRegister(addressAsBool->reg, code);
        return std::make_shared<BoolRValueStructure>(addressAsBool->reg);
    }

    if(address->vCategory == ValueCategory::lvalue){
        auto addressAsLValue = dynamic_cast<GenericLValueStructure*>(address.get());
        auto& fn = code.getFnSymbol();
        fn.writeLine("mov [" + addressAsLValue->getAccess() + "], " + registerToString(1, reg));
        return std::make_shared<BoolLValueStructure>(addressAsLValue->getAccess());
    }
    return nullptr;
}

void ACC::BoolRValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    if(this->reg == reg)
        return;
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(1, reg) + ", " + registerToString(1, this->reg));
}

