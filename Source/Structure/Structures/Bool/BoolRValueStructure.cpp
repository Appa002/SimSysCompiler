//
// Created by a_mod on 07.06.2019.
//

#include <General/builtinTypes.h>
#include "BoolRValueStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"
#include "BoolLValueStructure.h"
#include <Assembly/Code.h>
#include <Error/Errors.h>

ACC::BoolRValueStructure::BoolRValueStructure(ACC::Register reg) : BoolStructure(ValueCategory::rvalue), reg(reg){
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure>
ACC::BoolRValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, address->type.id, "copy");

    if(address->vCategory == ValueCategory::rvalue){
        auto addressAsBool = dynamic_cast<BoolRValueStructure*>(address.get());
        loadToRegister(addressAsBool->reg, code);
        return std::make_shared<BoolRValueStructure>(addressAsBool->reg);
    }

    if(address->vCategory == ValueCategory::lvalue){
        auto addressAsLValue = dynamic_cast<AsmAccessible*>(address.get());
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

ACC::Register ACC::BoolRValueStructure::getRegister() const {
    return reg;
}


std::shared_ptr<ACC::Structure> ACC::BoolRValueStructure::operatorChar(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "bool", "char");
}

std::shared_ptr<ACC::Structure> ACC::BoolRValueStructure::operatorNum(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "bool", "num");
}

std::shared_ptr<ACC::Structure> ACC::BoolRValueStructure::operatorBool(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::BoolRValueStructure::operatorPtr(ACC::Code &code, ACC::Type pointingTo) {
    throw errors::TypeConversion(nullptr, "bool", "ptr");


}

bool ACC::BoolRValueStructure::hasConversionTo(const Type &id) {
    return id == Type("bool", 1);
}

