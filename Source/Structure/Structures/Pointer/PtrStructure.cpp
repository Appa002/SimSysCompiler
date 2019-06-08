#include <utility>

//
// Created by a_mod on 07.06.2019.
//

#include "PtrRValueStructure.h"
#include "PtrLValueStructure.h"
#include "PtrStructure.h"
#include <General/builtinTypes.h>
#include <Assembly/Code.h>
#include <Structure/Structures/Number/NumRValueStructure.h>

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorForDone(std::shared_ptr<ACC::Structure> limit, ACC::Code &code) {
    return Structure::operatorForDone(limit, code);
}

std::shared_ptr<ACC::Structure> ACC::PtrStructure::operatorForNext(ACC::Code & code) {
    return Structure::operatorForNext(code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorAdd(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto *amountAsElem = dynamic_cast<ElementaryStructure *>(amount.get());

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(8, lhs);
    std::string rhsAsString = registerToString(8, rhs);

    this->loadToRegister(lhs, code);
    amountAsElem->loadToRegister(rhs, code);

    fn.writeLine("add " + lhsAsString + ", " + rhsAsString);

    code.freeRegister(rhs);

    return std::make_shared<PtrRValueStructure>(lhs, Type(type.getPointingTo()));
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorSubtract(std::shared_ptr<ACC::Structure> amount, ACC::Code & code) {
    return Structure::operatorSubtract(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorMultiplication(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorMultiplication(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorDivision(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorDivision(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorNotEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorNotEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorLess(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLess(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorGreater(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreater(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorLessEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLessEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorGreaterEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreaterEqual(other, code);
}

ACC::PtrStructure::PtrStructure(ValueCategory v, Type t) : ElementaryStructure(v, Type(BuiltIns::ptrType, t.getPointingTo())){

}

std::shared_ptr<ACC::Structure> ACC::PtrStructure::operatorDereference(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    Register reg = code.getFreeRegister();

    this->loadToRegister(reg, code);
    fn.writeLine("mov "+registerToString(type.getPointingTo().getSize(), reg)+", ["+registerToString(8, reg)+"]");
    return std::make_shared<NumRValueStructure>(reg);
}
