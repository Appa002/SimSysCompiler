//
// Created by a_mod on 08.06.2019.
//

#include <General/builtinTypes.h>
#include "BoolStructure.h"
#include "BoolRValueStructure.h"
#include <Assembly/Code.h>

std::shared_ptr<ACC::Structure>
ACC::BoolStructure::operatorEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    dynamic_cast<BoolStructure*>(other.get())->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("sete " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::BoolStructure::operatorNotEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    dynamic_cast<BoolStructure*>(other.get())->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setne " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::BoolStructure::operatorLess(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    dynamic_cast<BoolStructure*>(other.get())->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setl " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::BoolStructure::operatorGreater(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    dynamic_cast<BoolStructure*>(other.get())->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setg " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::BoolStructure::operatorLessEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    dynamic_cast<BoolStructure*>(other.get())->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setle " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::BoolStructure::operatorGreaterEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    dynamic_cast<BoolStructure*>(other.get())->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setge " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

ACC::BoolStructure::BoolStructure(ACC::ValueCategory v) : ElementaryStructure(v, Type("bool", 1)){

}
