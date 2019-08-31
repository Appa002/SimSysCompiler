//
// Created by a_mod on 08.06.2019.
//

#include "CharRValueStructure.h"
//
// Created by a_mod on 07.06.2019.
//

#include "CharRValueStructure.h"
#include "CharLValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/GenericLValueStructure.h>
#include <Structure/Structures/Number/NumRValueStructure.h>
#include <Error/Errors.h>
#include <Structure/ImmediatAccessible.h>

ACC::CharRValueStructure::CharRValueStructure(ACC::Register reg)
        : reg(reg), CharStructure(ValueCategory::rvalue) {
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure> ACC::CharRValueStructure::operatorCopy(std::shared_ptr<Structure> obj,
                                                                       ACC::Code &code){
    if(obj->type != Type("char", 1))
        obj = obj->operatorChar(code);


    if (obj->vCategory == ValueCategory::rvalue) {
        auto *objAsR = dynamic_cast<RegisterAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();


        fn.writeLine("mov " + registerToString(1, reg) +  ", " + registerToString(1, objAsR->getRegister()));

        return nullptr;
    }

    else if (obj->vCategory == ValueCategory::lvalue) {
        auto *objASL = dynamic_cast<AsmAccessible *>(obj.get());

        auto &fn = code.getFnSymbol();

        fn.writeLine("mov " + registerToString(1, reg) + ", [" + objASL->getAccess() + "]");

        return obj;
    }
    else if (obj->vCategory == ValueCategory::ivalue) {
        auto *objAsI = dynamic_cast<ImmediatAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();


        fn.writeLine("mov " + registerToString(1, reg) +  ", " + objAsI->getValue());

        return nullptr;
    }


    return nullptr;
}

void ACC::CharRValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    if (reg == this->reg)
        return;

    auto &fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(1, reg) + ", " + registerToString(1, this->reg));
}

ACC::Register ACC::CharRValueStructure::getRegister() const {
    return reg;
}

std::shared_ptr<ACC::Structure> ACC::CharRValueStructure::operatorChar(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::CharRValueStructure::operatorNum(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "char", "num");

}

std::shared_ptr<ACC::Structure> ACC::CharRValueStructure::operatorBool(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "char", "bool");

}

std::shared_ptr<ACC::Structure> ACC::CharRValueStructure::operatorPtr(ACC::Code &code, ACC::Type pointingTo) {
    throw errors::TypeConversion(nullptr, "char", "ptr");

}

bool ACC::CharRValueStructure::hasConversionTo(const Type &id) {
    return id == Type("char", 1);
}
