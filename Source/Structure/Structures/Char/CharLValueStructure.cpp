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

ACC::CharLValueStructure::CharLValueStructure(std::string const &access)
        : CharStructure(ValueCategory::lvalue), access(access) {

}

void ACC::CharLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(1, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::CharLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code &code) {
    if(address->type == Type(BuiltIns::numType)){
        auto asNum = this->operatorNum(code);
        asNum->operatorCopy(address, code);
    }

    if(address->type  != Type(BuiltIns::charType))
        throw std::runtime_error("Can't convert type `char` to receiving type.");


    if (address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLValue = dynamic_cast<AsmAccessible *>(address.get());
        auto &fn = code.getFnSymbol();

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(1, reg);

        fn.writeLine("mov " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);
        code.freeRegister(reg);

        return address;
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
    throw std::runtime_error("No implicit conversion of  type `char` to type num");
}

std::shared_ptr<ACC::Structure> ACC::CharLValueStructure::operatorBool(ACC::Code &code) {
    throw std::runtime_error("No implicit conversion of  type `char` to type bool");
}

std::shared_ptr<ACC::Structure> ACC::CharLValueStructure::operatorPtr(ACC::Code &code, ACC::Type) {
    throw std::runtime_error("No implicit conversion of  type `char` to type ptr");
}


