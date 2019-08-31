//
// Created by a_mod on 07.06.2019.
//

#include "BoolLValueStructure.h"
#include "BoolIValueStructure.h"
#include <Assembly/Code.h>
#include <General/utils.h>
#include <General/builtinTypes.h>
#include <Error/Errors.h>
#include <Structure/RegisterAccessible.h>

ACC::BoolLValueStructure::BoolLValueStructure(std::string access)
        : BoolStructure(ValueCategory::lvalue), access(std::move(access))
{

}


void ACC::BoolLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::BoolLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> obj, ACC::Code & code) {
    if(obj->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, obj->type.id, "copy");


    if(obj->vCategory == ValueCategory::lvalue) {
        auto &fn = code.getFnSymbol();
        auto *objAsLvalue = dynamic_cast<AsmAccessible *>(obj.get());

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(1, reg);

        fn.writeLine("mov " + regStr + ", [" + objAsLvalue->getAccess() + "]");
        fn.writeLine("mov [ " + access + " ], " + regStr);

        code.freeRegister(reg);

    } else if (obj->vCategory == ValueCategory::rvalue){
        auto &fn = code.getFnSymbol();
        auto *objAsR = dynamic_cast<RegisterAccessible*>(obj.get());

        fn.writeLine("mov [ " + access + " ], " + registerToString(1,objAsR->getRegister()));

    }else if (obj->vCategory == ValueCategory::ivalue){
        auto &fn = code.getFnSymbol();
        auto *objAsI = dynamic_cast<ImmediatAccessible*>(obj.get());

        fn.writeLine("mov byte [ " + access + " ], " + objAsI->getValue());
    }
    return nullptr;
}

std::string const &ACC::BoolLValueStructure::getAccess() const {
    return access;
}

std::shared_ptr<ACC::Structure> ACC::BoolLValueStructure::operatorChar(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "bool", "char");
}

std::shared_ptr<ACC::Structure> ACC::BoolLValueStructure::operatorNum(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "bool", "num");
}

std::shared_ptr<ACC::Structure> ACC::BoolLValueStructure::operatorBool(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::BoolLValueStructure::operatorPtr(ACC::Code &code, ACC::Type pointingTo) {
    throw errors::TypeConversion(nullptr, "bool", "ptr");
}

bool ACC::BoolLValueStructure::hasConversionTo(const Type &id) {
    return id == Type("bool", 1);
}
