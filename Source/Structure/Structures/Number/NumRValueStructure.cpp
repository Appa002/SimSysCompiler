//
// Created by a_mod on 07.06.2019.
//

#include "NumRValueStructure.h"
#include "NumLValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>

ACC::NumRValueStructure::NumRValueStructure(ACC::Register reg)
: reg(reg), NumStructure(ValueCategory::rvalue){
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorCopy(std::shared_ptr<Structure> address,
                                                                     ACC::Code &code) {
    if(address->vCategory == ValueCategory::rvalue) {
        auto *addressAsNum = dynamic_cast<ElementaryStructure *>(address.get());
        Register other = code.getFreeRegister();
        addressAsNum->loadToRegister(other, code);
        return std::make_shared<NumRValueStructure>(other);
    }

    if(address->vCategory == ValueCategory::lvalue){
        auto *addressAsLvalue = dynamic_cast<NumLValueStructure *>(address.get());
        if(addressAsLvalue) {
            auto &fn = code.getFnSymbol();

            fn.writeLine("mov [" + addressAsLvalue->getAccess() + "], " + registerToString(8, reg));

            return address;
        }else{
            auto *addressAsLvalue = dynamic_cast<GenericLValueStructure *>(address.get());

            auto &fn = code.getFnSymbol();

            fn.writeLine("mov [" + addressAsLvalue->getAccess() + "], " + registerToString(8, reg));

            return address;
        }
    }

    return nullptr;
}

void ACC::NumRValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    if(reg == this->reg)
        return;

    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", " + registerToString(8, this->reg));
}
