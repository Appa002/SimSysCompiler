#include "PtrLValueStructure.h"

#include <utility>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <Error/Errors.h>


ACC::PtrLValueStructure::PtrLValueStructure(std::string access, ACC::Type type)
        : PtrStructure(ValueCategory::lvalue, type), access(std::move(access)) {

}

void ACC::PtrLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code &code) {
    if(address->type == Type(BuiltIns::numType)){
        auto thisAsNum = operatorNum(code);
        return thisAsNum->operatorCopy(address, code);
    }

    if(address->type != Type(BuiltIns::ptrType))
        throw errors::InvalidType(nullptr, "ImplementMe", "copy"); //TODO: Type system.

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

std::string const &ACC::PtrLValueStructure::getAccess() const {
    return access;
}

std::shared_ptr<ACC::Structure> ACC::PtrLValueStructure::operatorChar(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "char");
}

std::shared_ptr<ACC::Structure> ACC::PtrLValueStructure::operatorNum(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "num");
}

std::shared_ptr<ACC::Structure> ACC::PtrLValueStructure::operatorBool(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "bool");
}

std::shared_ptr<ACC::Structure> ACC::PtrLValueStructure::operatorPtr(ACC::Code &code, ACC::Type pointingTo) {
    return std::make_shared<PtrLValueStructure>(access, pointingTo);
}
