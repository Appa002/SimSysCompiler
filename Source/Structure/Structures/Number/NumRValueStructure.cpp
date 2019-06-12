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

ACC::NumRValueStructure::NumRValueStructure(ACC::Register reg)
        : reg(reg), NumStructure(ValueCategory::rvalue) {
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorCopy(std::shared_ptr<Structure> address,
                                                                      ACC::Code &code) {
    if(address->type == Type(BuiltIns::charType)){
        auto thisAsChar = operatorChar(code);
        return thisAsChar->operatorCopy(address, code);
    } else if (address->type == Type(BuiltIns::ptrType)){
        auto thisAsPtr = operatorPtr(code, Type(address->type.getPointingTo()));
        return thisAsPtr->operatorCopy(address, code);
    }

    if(address->type != Type(BuiltIns::numType))
        throw std::runtime_error("Can't convert type `num` to receiving type.");

    if (address->vCategory == ValueCategory::rvalue) {
        auto *addressAsNum = dynamic_cast<ElementaryStructure *>(address.get());
        Register other = code.getFreeRegister();
        addressAsNum->loadToRegister(other, code);
        return std::make_shared<NumRValueStructure>(other);
    }

    if (address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLvalue = dynamic_cast<AsmAccessible *>(address.get());
        auto &fn = code.getFnSymbol();

        fn.writeLine("mov [" + addressAsLvalue->getAccess() + "], " + registerToString(8, reg));

        return address;
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
    return std::make_shared<CharRValueStructure>(reg);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorNum(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorBool(ACC::Code &code) {
    throw std::runtime_error("No viable conversion of type `num` to type `bool`.");
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorPtr(Code &code, Type pointingTo) {
    return std::make_shared<PtrRValueStructure>(reg, pointingTo);
}
