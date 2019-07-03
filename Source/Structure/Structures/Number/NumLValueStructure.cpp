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

ACC::NumLValueStructure::NumLValueStructure(std::string const &access)
        : NumStructure(ValueCategory::lvalue), access(access) {

}

void ACC::NumLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::NumLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code &code) {
    if(address->type == Type(BuiltIns::charType)){
        auto thisAsChar = operatorChar(code);
        return thisAsChar->operatorCopy(address, code);
    } else if (address->type == Type(BuiltIns::ptrType)){
        auto thisAsPtr = operatorPtr(code, Type(address->type.getPointingTo()));
        return thisAsPtr->operatorCopy(address, code);
    }

    if(address->type != Type(BuiltIns::numType))
        throw std::runtime_error("Can't convert type `num` to receiving type.");



    if (address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLValue = dynamic_cast<AsmAccessible *>(address.get());

        auto &fn = code.getFnSymbol();

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        fn.writeLine("mov " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);
        code.freeRegister(reg);

        return address;
    }
    return nullptr;
}

std::string const &ACC::NumLValueStructure::getAccess() const {
    return access;
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorChar(ACC::Code &code) {
    throw std::runtime_error("No implicit conversion between `num` to `char`");
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorNum(ACC::Code &code) {
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorBool(ACC::Code &code) {
    throw std::runtime_error("No implicit conversion between `num` to `bool`");
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorPtr(Code &code, Type pointingTo) {
    throw std::runtime_error("No implicit conversion between `num` to `ptr`");
}
