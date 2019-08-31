#include <utility>

#include <utility>

//
// Created by a_mod on 07.06.2019.
//

#include "PtrRValueStructure.h"
#include "PtrLValueStructure.h"
#include <General/builtinTypes.h>
#include <Assembly/Code.h>
#include <Structure/Structures/Number/NumRValueStructure.h>
#include <Error/Errors.h>
#include <Structure/ImmediatAccessible.h>

ACC::PtrRValueStructure::PtrRValueStructure(Register reg, Type type)
        : PtrStructure(ValueCategory::rvalue, type), reg(reg) {
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> obj, ACC::Code &code) {
    if(!obj->type.isPtr)
        obj = obj->operatorPtr(code, type);


    if (obj->vCategory == ValueCategory::lvalue) {
        auto *objAsL = dynamic_cast<AsmAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();

        if (!access.empty()) {
            Register reg = code.getFreeRegister();
            fn.writeLine("mov " + registerToString(8, reg) + ", [" + objAsL->getAccess() + "]");
            fn.writeLine("mov [" + access + "], " + registerToString(8, reg));
            code.freeRegister(reg);
        } else
            fn.writeLine("mov " + registerToString(8, this->reg) + ", [" + objAsL->getAccess() + "]");

    } else if (obj->vCategory == ValueCategory::rvalue) {
        auto *objAsR = dynamic_cast<RegisterAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();

        if (!access.empty()) {
            fn.writeLine("mov [" + access + "], " + registerToString(8, objAsR->getRegister()));
        } else
            fn.writeLine("mov " + registerToString(8, this->reg) + ", [" + registerToString(8, objAsR->getRegister()) + "]");

    }else if (obj->vCategory == ValueCategory::ivalue) {
        auto *objAsI = dynamic_cast<ImmediatAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();

        if (!access.empty()) {
            if(obj->type.size == 8)
                fn.writeLine("mov qword [" + access + "], " + objAsI->getValue());
            else if(obj->type.size == 4)
                fn.writeLine("mov dword [" + access + "], " + objAsI->getValue());
            else if(obj->type.size == 2)
                fn.writeLine("mov word [" + access + "], " + objAsI->getValue());
            else if(obj->type.size == 1)
                fn.writeLine("mov byte [" + access + "], " + objAsI->getValue());

        } else{
            if(obj->type.size == 8)
                fn.writeLine("mov qword" + registerToString(8, this->reg) + ", " + objAsI->getValue());
            else if(obj->type.size == 4)
                fn.writeLine("mov dword" + registerToString(8, this->reg) + ", " + objAsI->getValue());
            else if(obj->type.size == 2)
                fn.writeLine("mov word" + registerToString(8, this->reg) + ", " + objAsI->getValue());
            else if(obj->type.size == 1)
                fn.writeLine("mov byte" + registerToString(8, this->reg) + ", " + objAsI->getValue());

        }
    }

    return nullptr;
}

void ACC::PtrRValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    if (!access.empty())
        fn.writeLine("lea " + registerToString(8, reg) + ", [" + access + "]");
    else
        fn.writeLine("mov " + registerToString(8, reg) + ", " + registerToString(8, this->reg));
}

ACC::PtrRValueStructure::PtrRValueStructure(std::string access, ACC::Type type)
        : PtrStructure(ValueCategory::rvalue, type), access(std::move(access)), reg(Register::r15) {
}

ACC::Register ACC::PtrRValueStructure::getRegister() const {
    return reg;
}

std::shared_ptr<ACC::Structure> ACC::PtrRValueStructure::operatorChar(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "char");
}

std::shared_ptr<ACC::Structure> ACC::PtrRValueStructure::operatorNum(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "num");
}

std::shared_ptr<ACC::Structure> ACC::PtrRValueStructure::operatorBool(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "bool");
}

std::shared_ptr<ACC::Structure> ACC::PtrRValueStructure::operatorPtr(ACC::Code &code, ACC::Type pointingTo) {
    return std::make_shared<PtrRValueStructure>(reg, pointingTo);
}

bool ACC::PtrRValueStructure::hasConversionTo(const ACC::Type &id) {
    return id.isPtr;
}


