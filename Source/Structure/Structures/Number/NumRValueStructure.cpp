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

ACC::NumRValueStructure::NumRValueStructure(ACC::Register reg)
        : reg(reg), NumStructure(ValueCategory::rvalue) {
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorCopy(std::shared_ptr<Structure> address,
                                                                      ACC::Code &code) {
    if(address->type == Type("char", 1)){
        auto thisAsChar = operatorChar(code);
        return thisAsChar->operatorCopy(address, code);

    } else if (address->type.isPtr){
        auto thisAsPtr = operatorPtr(code, Type(address->type));
        return thisAsPtr->operatorCopy(address, code);
    }

    if(address->type != Type("num", 8))
        throw errors::InvalidType(nullptr, address->type.id, "copy");


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
    throw errors::TypeConversion(nullptr, "num", "char");}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorNum(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorBool(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "num", "bool");

}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorPtr(Code &code, Type pointingTo) {
    throw errors::TypeConversion(nullptr, "num", "ptr");

}

bool ACC::NumRValueStructure::hasConversionTo(const ACC::Type &id) {
    return id == Type("num", 8);
}
