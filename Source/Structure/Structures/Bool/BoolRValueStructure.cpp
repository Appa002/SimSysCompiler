//
// Created by a_mod on 07.06.2019.
//

#include <General/builtinTypes.h>
#include "BoolRValueStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"
#include "BoolLValueStructure.h"
#include "BoolIValueStructure.h"
#include <Assembly/Code.h>
#include <Error/Errors.h>

ACC::BoolRValueStructure::BoolRValueStructure(ACC::Register reg) : BoolStructure(ValueCategory::rvalue), reg(reg){
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure>
ACC::BoolRValueStructure::operatorCopy(std::vector<std::shared_ptr<Structure>> objList, ACC::Code & code) {
    auto & obj = objList[0];

    if(obj->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, obj->type.id, "copy");

    if(obj->vCategory == ValueCategory::rvalue){
        auto objAsR = dynamic_cast<RegisterAccessible*>(obj.get());
        auto& fn = code.getFnSymbol();

        fn.writeLine("mov " + registerToString(1, this->reg) + ", " + registerToString(1,objAsR->getRegister()));
        return nullptr;

    }
    else if(obj->vCategory == ValueCategory::lvalue){
        auto objAsL = dynamic_cast<AsmAccessible*>(obj.get());
        auto& fn = code.getFnSymbol();
        fn.writeLine("mov " + registerToString(1, reg) + ", [" + objAsL->getAccess() + "]");
        return nullptr;
    }
    else if(obj->vCategory == ValueCategory::ivalue){
        auto objAsI = dynamic_cast<ImmediatAccessible*>(obj.get());
        auto& fn = code.getFnSymbol();

        if(obj->type.size == 8)
            fn.writeLine("mov qword "+ registerToString(1, reg) +" " + objAsI->getValue());
        else if(obj->type.size == 4)
            fn.writeLine("mov dword "+ registerToString(1, reg) +", " + objAsI->getValue());
        else if(obj->type.size == 2)
            fn.writeLine("mov word "+ registerToString(1, reg) +", " + objAsI->getValue());
        else if(obj->type.size == 1)
            fn.writeLine("mov byte "+ registerToString(1, reg) +", " + objAsI->getValue());

        return nullptr;
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

