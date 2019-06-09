#include <utility>

#include <utility>

//
// Created by a_mod on 07.06.2019.
//

#include "PtrRValueStructure.h"
#include "PtrLValueStructure.h"
#include <General/builtinTypes.h>
#include <Assembly/Code.h>

ACC::PtrRValueStructure::PtrRValueStructure(Register reg, Type type)
: PtrStructure(ValueCategory::rvalue, type), reg(reg) {
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->vCategory == ValueCategory::lvalue){
        auto *addressAsLValue = dynamic_cast<PtrLValueStructure *>(address.get());
        if(addressAsLValue != nullptr) {
            auto &fn = code.getFnSymbol();

            Register reg = code.getFreeRegister();
            std::string regStr = registerToString(8, reg);

            if(!access.empty())
                fn.writeLine("lea " + regStr + ", [" + access + "]");
            else
                fn.writeLine("mov " + regStr + ", " + registerToString(8, this->reg));
            fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);
            code.freeRegister(reg);

            return std::make_shared<PtrLValueStructure>(addressAsLValue->getAccess(), type);
        }else{
            auto &fn = code.getFnSymbol();
            auto *addressAsLValue = dynamic_cast<GenericLValueStructure *>(address.get());

            Register reg = code.getFreeRegister();
            std::string regStr = registerToString(8, reg);

            if(!access.empty())
                fn.writeLine("lea " + regStr + ", [" + access + "]");
            else
                fn.writeLine("mov " + regStr + ", " + registerToString(8, this->reg));
            fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);
            code.freeRegister(reg);

            return std::make_shared<PtrLValueStructure>(addressAsLValue->getAccess(), type);
        }
    }
    return nullptr;
}

void ACC::PtrRValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    if(!access.empty())
        fn.writeLine("lea " + registerToString(8, reg) + ", [" + access + "]");
    else
        fn.writeLine("mov " + registerToString(8, reg) + ", " + registerToString(8, this->reg));
}

ACC::PtrRValueStructure::PtrRValueStructure(std::string access, ACC::Type type)
: PtrStructure(ValueCategory::rvalue, type), access(std::move(access)), reg(Register::r15){
}


