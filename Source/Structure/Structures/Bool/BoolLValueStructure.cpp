//
// Created by a_mod on 07.06.2019.
//

#include "BoolLValueStructure.h"
#include <Assembly/Code.h>
#include <General/utils.h>
#include <General/builtinTypes.h>
#include <Error/Errors.h>

ACC::BoolLValueStructure::BoolLValueStructure(std::string access)
        : BoolStructure(ValueCategory::lvalue), access(std::move(access))
{

}


void ACC::BoolLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::BoolLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, address->type.id, "copy");


    if(address->vCategory == ValueCategory::lvalue) {
        auto &fn = code.getFnSymbol();
        auto *addressAsLValue = dynamic_cast<AsmAccessible *>(address.get());

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        fn.writeLine("mov " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);

        code.freeRegister(reg);

        return address;
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
