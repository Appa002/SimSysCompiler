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

ACC::CharRValueStructure::CharRValueStructure(ACC::Register reg)
        : reg(reg), CharStructure(ValueCategory::rvalue) {
    registerInUse.push_back(reg);
}

std::shared_ptr<ACC::Structure> ACC::CharRValueStructure::operatorCopy(std::shared_ptr<Structure> address,
                                                                       ACC::Code &code) {
    if (address->vCategory == ValueCategory::rvalue) {
        auto *addressAsNum = dynamic_cast<ElementaryStructure *>(address.get());
        Register other = code.getFreeRegister();
        addressAsNum->loadToRegister(other, code);
        return std::make_shared<CharRValueStructure>(other);
    }

    if (address->vCategory == ValueCategory::lvalue) {
        auto *addressAsLvalue = dynamic_cast<AsmAccessible *>(address.get());

        auto &fn = code.getFnSymbol();

        fn.writeLine("mov [" + addressAsLvalue->getAccess() + "], " + registerToString(1, reg));

        return address;
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
