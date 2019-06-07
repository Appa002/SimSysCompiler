#include <utility>

//
// Created by a_mod on 03.06.2019.
//

#include "NumLValueStructure.h"
#include "NumRValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorForNext(ACC::Code &code) {
    return Structure::operatorForNext(code);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorForDone(std::shared_ptr<Structure> limit,
                                                                        ACC::Code &code) {
    return Structure::operatorForDone(limit, code);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorCopy(std::shared_ptr<Structure> address,
                                                                     ACC::Code &code) {
    if(address->vCategory == ValueCategory::lvalue) {
        auto &fn = code.getFnSymbol();
        auto *addressAsLValue = dynamic_cast<NumLValueStructure *>(address.get());

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        fn.writeLine("mov " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->access + " ], " + regStr);

        return std::make_shared<NumLValueStructure>(addressAsLValue->access);
    }
    return nullptr;
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorAdd(std::shared_ptr<Structure> amount, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto* amountAsElem = dynamic_cast<ElementaryStructure*>(amount.get());

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(8, lhs);
    std::string rhsAsString = registerToString(8, rhs);

    this->loadToRegister(lhs, code);
    amountAsElem->loadToRegister(rhs, code);

    fn.writeLine("add "+lhsAsString+", " + rhsAsString);

    code.freeRegister(rhs);

    return std::make_shared<NumRValueStructure>(lhs);

}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorSubtract(std::shared_ptr<Structure> amount,
                                                                         ACC::Code &code) {
    return Structure::operatorSubtract(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::NumLValueStructure::operatorMultiplication(std::shared_ptr<Structure> amount, ACC::Code &code) {
    return Structure::operatorMultiplication(amount, code);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorDivision(std::shared_ptr<Structure> amount,
                                                                         ACC::Code &code) {
    return Structure::operatorDivision(amount, code);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorEqual(std::shared_ptr<Structure> other, ACC::Code &code) {
    return Structure::operatorEqual(other, code);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorNotEqual(std::shared_ptr<Structure> other,
                                                                         ACC::Code &code) {
    return Structure::operatorNotEqual(other, code);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorLess(std::shared_ptr<Structure> other, ACC::Code &code) {
    return Structure::operatorLess(other, code);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorGreater(std::shared_ptr<Structure> other,
                                                                        ACC::Code &code) {
    return Structure::operatorGreater(other, code);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorLessEqual(std::shared_ptr<Structure> other,
                                                                          ACC::Code &code) {
    return Structure::operatorLessEqual(other, code);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorGreaterEqual(std::shared_ptr<Structure> other,
                                                                             ACC::Code &code) {
    return Structure::operatorGreaterEqual(other, code);
}

ACC::NumLValueStructure::NumLValueStructure(std::string const &access)
: access(access), ElementaryStructure(ValueCategory::lvalue, BuiltIns::numType){

}

void ACC::NumLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", [" + access + "]");
}
