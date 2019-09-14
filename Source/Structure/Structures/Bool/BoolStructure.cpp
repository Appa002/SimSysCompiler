//
// Created by a_mod on 08.06.2019.
//

#include <General/builtinTypes.h>
#include "BoolStructure.h"
#include "BoolRValueStructure.h"
#include <Assembly/Code.h>
#include <Error/Errors.h>

std::shared_ptr<ACC::Structure>
ACC::BoolStructure::operatorEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {

    if(other->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, other->type.id, "equal");

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

    if(other->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, other->type.id, "not equal");

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

    if(other->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, other->type.id, "less");

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

    if(other->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, other->type.id, "greater");

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

    if(other->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, other->type.id, "less or equal");

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

    if(other->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, other->type.id, "greater or equal");

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

std::shared_ptr<ACC::Structure> ACC::BoolStructure::operatorOr(std::shared_ptr<Structure> other, ACC::Code &code) {

    if(other->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, other->type.id, "or");

    auto& fn = code.getFnSymbol();
    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    dynamic_cast<BoolStructure*>(other.get())->loadToRegister(rhs, code);

    fn.writeLine("or " + registerToString(1, lhs) + ", " + registerToString(1, rhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);

}

std::shared_ptr<ACC::Structure> ACC::BoolStructure::operatorAnd(std::shared_ptr<Structure> other, ACC::Code &code) {
    if(other->type != Type("bool", 1))
        throw errors::InvalidType(nullptr, other->type.id, "and");

    auto& fn = code.getFnSymbol();
    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    dynamic_cast<BoolStructure*>(other.get())->loadToRegister(rhs, code);

    fn.writeLine("and " + registerToString(1, lhs) + ", " + registerToString(1, rhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}
