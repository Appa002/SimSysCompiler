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
#include <Structure/Structures/Char/CharRValueStructure.h>
#include <Structure/Structures/Bool/BoolRValueStructure.h>
#include <Error/Errors.h>
#include <Types/TypeTable.h>

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorForDone(std::shared_ptr<ACC::Structure> limit, ACC::Code &code) {
    return Structure::operatorForDone(limit, code);
}

std::shared_ptr<ACC::Structure> ACC::PtrStructure::operatorForNext(ACC::Code & code) {
    return Structure::operatorForNext(code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorAdd(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    if(amount->type != Type("num", 8))
        throw errors::InvalidType(nullptr, "Arithmetic operator expects right hand side to be of type `num`");

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

    return std::make_shared<PtrRValueStructure>(lhs, type);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorSubtract(std::shared_ptr<ACC::Structure> amount, ACC::Code & code) {
    if(amount->type != Type("num", 8))
        throw errors::InvalidType(nullptr, "Arithmetic operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto *amountAsElem = dynamic_cast<ElementaryStructure *>(amount.get());

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(8, lhs);
    std::string rhsAsString = registerToString(8, rhs);

    this->loadToRegister(lhs, code);
    amountAsElem->loadToRegister(rhs, code);

    fn.writeLine("sub " + lhsAsString + ", " + rhsAsString);

    code.freeRegister(rhs);


    return std::make_shared<NumRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorMultiplication(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    throw errors::Unique(nullptr, "Multiplication with pointers is invalid.");
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorDivision(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    throw errors::Unique(nullptr, "Division with pointers is invalid.");
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    if(!(other->type == Type("num", 8) || other->type ==this->type))
        throw errors::InvalidType(nullptr, "Comparision operator expects right hand side to be of type `num` or `ptr`");


    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("sete " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorNotEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    if(!(other->type == Type("num", 8) || other->type ==this->type))
        throw errors::InvalidType(nullptr, "Comparision operator expects right hand side to be of type `num` or `ptr`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setne " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorLess(std::shared_ptr<ACC::Structure> other, ACC::Code &code){
    if(!(other->type == Type("num", 8) || other->type ==this->type))
        throw errors::InvalidType(nullptr, "Comparision operator expects right hand side to be of type `num` or `ptr`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setl " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorGreater(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    if(!(other->type == Type("num", 8) || other->type ==this->type))
        throw errors::InvalidType(nullptr, "Comparision operator expects right hand side to be of type `num` or `ptr`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setg " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorLessEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    if(!(other->type == Type("num", 8) || other->type ==this->type))
        throw errors::InvalidType(nullptr, "Comparision operator expects right hand side to be of type `num` or `ptr`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setle " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorGreaterEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    if(!(other->type == Type("num", 8) || other->type ==this->type))
        throw errors::InvalidType(nullptr, "Comparision operator expects right hand side to be of type `num` or `ptr`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setge " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

ACC::PtrStructure::PtrStructure(ValueCategory v, Type t) : ElementaryStructure(v, t){

}

std::shared_ptr<ACC::Structure> ACC::PtrStructure::operatorDereference(ACC::Code &code) {
    Type underlying = Type(type.id, TypeTable::get()->getSize(type.id));


    auto& fn = code.getFnSymbol();
    Register reg = code.getFreeRegister();

    this->loadToRegister(reg, code);
    fn.writeLine("mov "+registerToString(underlying.size, reg)+", ["+registerToString(8, reg)+"]");

    if (underlying == Type("num", 8))
        return std::make_shared<NumRValueStructure>(reg);

    else if (underlying == Type("char", 1))
        return std::make_shared<CharRValueStructure>(reg);

    else if (underlying == Type("bool", 1))
        return std::make_shared<BoolRValueStructure>(reg);
    code.freeRegister(reg);
    return nullptr;
}
