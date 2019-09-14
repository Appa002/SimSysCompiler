#include <utility>

//
// Created by a_mod on 03.06.2019.
//

#include "NumLValueStructure.h"
#include "NumRValueStructure.h"
#include "NumIValueStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"
#include "Structure/Structures/Bool/BoolRValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Error/Errors.h>
#include <Structure/ImmediatAccessible.h>

ACC::NumLValueStructure::NumLValueStructure(std::string const &access)
        : NumStructure(ValueCategory::lvalue), access(access) {

}

void ACC::NumLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::NumLValueStructure::operatorCopy(std::vector<std::shared_ptr<Structure>> objList, ACC::Code &code) {
   auto & obj = objList[0];
    if(obj->type != Type("num", 8)){
        obj = obj->operatorNum(code);
    }

    if (obj->vCategory == ValueCategory::lvalue) {
        auto *objAsLvalue = dynamic_cast<AsmAccessible *>(obj.get());

        auto &fn = code.getFnSymbol();

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        fn.writeLine("mov " + regStr + ", [" + objAsLvalue->getAccess() + "]");
        fn.writeLine("mov [ " + access + " ], " + regStr);
        code.freeRegister(reg);
    }
    else if (obj->vCategory == ValueCategory::rvalue) {
        auto *objAsR = dynamic_cast<RegisterAccessible *>(obj.get());

        auto &fn = code.getFnSymbol();

        fn.writeLine("mov [ " + access + " ], " + registerToString(8, objAsR->getRegister()));
    }
    else if (obj->vCategory == ValueCategory::ivalue){
        auto *objAsI = dynamic_cast<ImmediatAccessible*>(obj.get());


        auto &fn = code.getFnSymbol();
        if(obj->type.size == 8)
            fn.writeLine("mov qword [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 4)
            fn.writeLine("mov dword [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 2)
            fn.writeLine("mov word [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 1)
            fn.writeLine("mov byte [ " + access + " ], " + objAsI->getValue());    }
    return nullptr;
}

std::string const &ACC::NumLValueStructure::getAccess() const {
    return access;
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorChar(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "num", "char");
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorNum(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorBool(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "num", "bool");
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorPtr(Code &code, Type pointingTo) {
    throw errors::TypeConversion(nullptr, "num", "ptr");
}

bool ACC::NumLValueStructure::hasConversionTo(const ACC::Type &id) {
    return id == Type("id", 8);
}
