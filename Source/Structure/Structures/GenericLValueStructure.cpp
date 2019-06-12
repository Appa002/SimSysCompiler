#include <utility>

//
// Created by a_mod on 07.06.2019.
//

#include <Assembly/Code.h>
#include <Structure/Structures/Char/CharRValueStructure.h>
#include <Structure/Structures/Bool/BoolRValueStructure.h>
#include <Structure/Structures/Number/NumRValueStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <Structure/Structures/Bool/BoolLValueStructure.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>
#include "GenericLValueStructure.h"

ACC::GenericLValueStructure::GenericLValueStructure(ACC::Type type, std::string access)
: ElementaryStructure(ValueCategory::lvalue, type), access(std::move(access))
{

}

void ACC::GenericLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(type.getSize(), reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::GenericLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->vCategory == ValueCategory::lvalue) {
        auto &fn = code.getFnSymbol();
        auto *addressAsLValue = dynamic_cast<AsmAccessible *>(address.get());

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(type.getSize(), reg);

        fn.writeLine("mov " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);
        code.freeRegister(reg);

        return address;
    }
    return nullptr;
}

std::string const &ACC::GenericLValueStructure::getAccess() const {
    return access;
}

std::shared_ptr<ACC::Structure> ACC::GenericLValueStructure::operatorChar(ACC::Code &code) {
    return std::make_shared<CharLValueStructure>(access);
}

std::shared_ptr<ACC::Structure> ACC::GenericLValueStructure::operatorNum(ACC::Code &code) {
    return std::make_shared<NumLValueStructure>(access);
}

std::shared_ptr<ACC::Structure> ACC::GenericLValueStructure::operatorBool(ACC::Code &code) {
    return std::make_shared<BoolLValueStructure>(access);
}

std::shared_ptr<ACC::Structure> ACC::GenericLValueStructure::operatorPtr(Code &code, Type pointingTo) {
    return std::make_shared<PtrLValueStructure>(access, pointingTo);

}

