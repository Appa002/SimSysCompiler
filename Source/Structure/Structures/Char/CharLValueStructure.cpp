//
// Created by a_mod on 08.06.2019.
//

#include "CharLValueStructure.h"

#include <utility>

//
// Created by a_mod on 03.06.2019.
//

#include "CharStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"
#include "Structure/Structures/Bool/BoolRValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>
#include <Error/Errors.h>
#include <Structure/ImmediatAccessible.h>

ACC::CharLValueStructure::CharLValueStructure(std::string const &access)
        : CharStructure(ValueCategory::lvalue), access(access) {

}

void ACC::CharLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(1, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::CharLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> obj, ACC::Code &code) {
    if (obj->type != Type("char", 1))
        obj = obj->operatorChar(code);

    if (obj->vCategory == ValueCategory::lvalue) {
        auto *objAsL = dynamic_cast<AsmAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(1, reg);

        fn.writeLine("mov " + regStr + ", [" + objAsL->getAccess() + "]");
        fn.writeLine("mov [ " + access + " ], " + regStr);
        code.freeRegister(reg);

        return nullptr;
    } else if (obj->vCategory == ValueCategory::rvalue) {
        auto *objAsR = dynamic_cast<RegisterAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();


        fn.writeLine("mov [ " + access + " ], " + registerToString(1, objAsR->getRegister()));

        return nullptr;
    } else if (obj->vCategory == ValueCategory::ivalue) {
        auto *objAsI = dynamic_cast<ImmediatAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();

        if(obj->type.size == 8)
            fn.writeLine("mov qword [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 4)
            fn.writeLine("mov dword [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 2)
            fn.writeLine("mov word [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 1)
            fn.writeLine("mov byte [ " + access + " ], " + objAsI->getValue());

    }

    return nullptr;
}

std::string const &ACC::CharLValueStructure::getAccess() const {
    return access;
}


std::shared_ptr<ACC::Structure> ACC::CharLValueStructure::operatorChar(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::CharLValueStructure::operatorNum(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "char", "num");
}

std::shared_ptr<ACC::Structure> ACC::CharLValueStructure::operatorBool(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "char", "bool");

}

std::shared_ptr<ACC::Structure> ACC::CharLValueStructure::operatorPtr(ACC::Code &code, ACC::Type) {
    throw errors::TypeConversion(nullptr, "char", "ptr");

}

bool ACC::CharLValueStructure::hasConversionTo(const Type &id) {
    return id == Type("char", 1);
}


