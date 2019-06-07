//
// Created by a_mod on 07.06.2019.
//

#include "NumIValueStructure.h"
#include "NumRValueStructure.h"
#include "NumLValueStructure.h"
#include <Assembly/Code.h>
#include <General/utils.h>
#include <General/builtinTypes.h>

ACC::NumIValueStructure::NumIValueStructure(int64_t value) : value(value), ElementaryStructure(ValueCategory::ivalue, BuiltIns::numType) {

}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorForDone(std::shared_ptr<ACC::Structure> limit, ACC::Code &code) {
    return Structure::operatorForDone(limit, code);
}

std::shared_ptr<ACC::Structure> ACC::NumIValueStructure::operatorForNext(ACC::Code & code) {
    return Structure::operatorForNext(code);
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    auto* addressAsLValue = (NumLValueStructure*)address.get();

    auto& fn = code.getFnSymbol();

    std::string buffered = toHex(value);
    buffered = std::string((4 - buffered.size()) * 2, '0') + buffered;

    fn.writeLine("mov qword [" + addressAsLValue->getAccess() + "], 0x" + buffered);

    return address;
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorAdd(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto* amountAsNum = dynamic_cast<ElementaryStructure*>(amount.get());
    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(8, lhs);
    std::string rhsAsString = registerToString(8, rhs);

    this->loadToRegister(lhs, code);
    amountAsNum->loadToRegister(rhs, code);

    fn.writeLine("add " + lhsAsString + ", " + rhsAsString);

    code.freeRegister(rhs);

    return std::make_shared<NumRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorSubtract(std::shared_ptr<ACC::Structure> amount, ACC::Code & code) {
    auto& fn = code.getFnSymbol();
    auto* amountAsNum = dynamic_cast<ElementaryStructure*>(amount.get());
    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(8, lhs);
    std::string rhsAsString = registerToString(8, rhs);

    this->loadToRegister(lhs, code);
    amountAsNum->loadToRegister(rhs, code);

    fn.writeLine("sub " + lhsAsString + ", " + rhsAsString);

    code.freeRegister(rhs);

    return std::make_shared<NumRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorMultiplication(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorMultiplication(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorDivision(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorDivision(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorNotEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorNotEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorLess(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLess(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorGreater(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreater(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorLessEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLessEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::NumIValueStructure::operatorGreaterEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreaterEqual(other, code);
}

void ACC::NumIValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", " + std::to_string(value));
}

int64_t ACC::NumIValueStructure::getValue() const {
    return value;
}
