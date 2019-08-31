//
// Created by a_mod on 07.06.2019.
//

#include "NumRValueStructure.h"
#include "NumLValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/Char/CharRValueStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Error/Errors.h>
#include <Structure/ImmediatAccessible.h>

ACC::NumRValueStructure::NumRValueStructure(ACC::Register reg)
        : reg(reg), NumStructure(ValueCategory::rvalue) {
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorCopy(std::shared_ptr<Structure> obj,
                                                                      ACC::Code &code) {
    if(obj->type != Type("num", 8))
        obj = obj->operatorNum(code);

    if (obj->vCategory == ValueCategory::rvalue) {
        auto *objAsL = dynamic_cast<RegisterAccessible *>(obj.get());
        auto&& fn = code.getFnSymbol();

        fn.writeLine("mov " + registerToString(8, this->reg) + ", " + registerToString(8, objAsL->getRegister()));

    }
    else if (obj->vCategory == ValueCategory::lvalue) {
        auto *objAsL = dynamic_cast<AsmAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();

        fn.writeLine("mov " + registerToString(8, reg) + ", [" + objAsL->getAccess() +"]");
    } else if (obj->vCategory == ValueCategory::ivalue) {
        auto *objAsI = dynamic_cast<ImmediatAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();

        if(obj->type.size == 8)
            fn.writeLine("mov qword "+ registerToString(1, reg) +" " + objAsI->getValue());
        else if(obj->type.size == 4)
            fn.writeLine("mov dword "+ registerToString(1, reg) +", " + objAsI->getValue());
        else if(obj->type.size == 2)
            fn.writeLine("mov word "+ registerToString(1, reg) +", " + objAsI->getValue());
        else if(obj->type.size == 1)
            fn.writeLine("mov byte "+ registerToString(1, reg) +", " + objAsI->getValue());

    }

    return nullptr;
}

void ACC::NumRValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    if (reg == this->reg)
        return;

    auto &fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", " + registerToString(8, this->reg));
}

ACC::Register ACC::NumRValueStructure::getRegister() const {
    return reg;
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorChar(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "num", "char");}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorNum(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorBool(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "num", "bool");

}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorPtr(Code &code, Type pointingTo) {
    return std::make_shared<PtrRValueStructure>(this->reg, pointingTo);

}

bool ACC::NumRValueStructure::hasConversionTo(const ACC::Type &id) {
    return id == Type("num", 8);
}
