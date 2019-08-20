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

ACC::PtrRValueStructure::PtrRValueStructure(Register reg, Type type)
        : PtrStructure(ValueCategory::rvalue, type), reg(reg) {
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code &code) {
    if(address->type == Type("num", 8)){
        auto thisAsNum = operatorNum(code);
        return thisAsNum->operatorCopy(address, code);
    }

    if(!address->type.isPtr)
        throw errors::InvalidType(nullptr, address->type.id, "copy");



    if (address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLValue = dynamic_cast<AsmAccessible *>(address.get());
        auto &fn = code.getFnSymbol();

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        if (!access.empty())
            fn.writeLine("lea " + regStr + ", [" + access + "]");
        else
            fn.writeLine("mov " + regStr + ", " + registerToString(8, this->reg));
        fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);
        code.freeRegister(reg);

        return std::make_shared<PtrLValueStructure>(addressAsLValue->getAccess(), type);
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


