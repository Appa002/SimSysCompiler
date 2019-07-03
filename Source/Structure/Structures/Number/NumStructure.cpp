//
// Created by a_mod on 08.06.2019.
//

#include <General/builtinTypes.h>
#include "NumStructure.h"
#include "NumRValueStructure.h"
#include "NumLValueStructure.h"
#include "NumIValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <Structure/Structures/Bool/BoolRValueStructure.h>
#include <Structure/Structures/Bool/BoolLValueStructure.h>
#include <General/builtinTypes.h>

ACC::NumStructure::NumStructure(ACC::ValueCategory v) : ElementaryStructure(v, Type(BuiltIns::numType)) {

}


std::shared_ptr<ACC::Structure> ACC::NumStructure::operatorForNext(ACC::Code &code) {
    auto rValue = operatorAdd(std::make_shared<NumIValueStructure>(1), code);
    rValue->operatorCopy(shared_from_this(), code);
    rValue->cleanUp(code);
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::NumStructure::operatorForDone(std::shared_ptr<Structure> limit,
                                                                         ACC::Code &code) {
    if(limit->type != Type(BuiltIns::numType))
        throw std::runtime_error("Limit of for loop needs to be of type `num`. (Thrown in operatorForDone)");

    // setting rflags such that an equals comparision is false if the loop is done


    auto limitAsI = dynamic_cast<NumStructure *>(limit.get());
    auto &fn = code.getFnSymbol();

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    limitAsI->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setl " + registerToString(1, lhs));
    fn.writeLine("cmp " + registerToString(1, lhs) + ", 1");

    code.freeRegister({lhs, rhs});

    return nullptr;
}


std::shared_ptr<ACC::Structure>
ACC::NumStructure::operatorAdd(std::shared_ptr<Structure> amount, ACC::Code &code) {
    if(amount->type != Type(BuiltIns::numType))
        throw std::runtime_error("Arithmetic operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto *amountAsElem = dynamic_cast<NumStructure *>(amount.get());

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(8, lhs);
    std::string rhsAsString = registerToString(8, rhs);

    this->loadToRegister(lhs, code);
    amountAsElem->loadToRegister(rhs, code);

    fn.writeLine("add " + lhsAsString + ", " + rhsAsString);

    code.freeRegister(rhs);
    

    return std::make_shared<NumRValueStructure>(lhs);

}

std::shared_ptr<ACC::Structure> ACC::NumStructure::operatorSubtract(std::shared_ptr<Structure> amount,
                                                                          ACC::Code &code) {
    if(amount->type != Type(BuiltIns::numType))
        throw std::runtime_error("Arithmetic operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto *amountAsElem = dynamic_cast<NumStructure *>(amount.get());

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
ACC::NumStructure::operatorMultiplication(std::shared_ptr<Structure> amount, ACC::Code &code) {
    if(amount->type != Type(BuiltIns::numType))
        throw std::runtime_error("Arithmetic operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto *amountAsElem = dynamic_cast<NumStructure *>(amount.get());

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(8, lhs);
    std::string rhsAsString = registerToString(8, rhs);

    this->loadToRegister(lhs, code);
    amountAsElem->loadToRegister(rhs, code);

    fn.writeLine("imul " + lhsAsString + ", " + rhsAsString);

    code.freeRegister(rhs);
    

    return std::make_shared<NumRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::NumStructure::operatorDivision(std::shared_ptr<Structure> amount,
                                                                          ACC::Code &code) {
    if(amount->type != Type(BuiltIns::numType))
        throw std::runtime_error("Arithmetic operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto amountAsNum = dynamic_cast<NumStructure *>(amount.get());

    code.reserveRegister(Register::rD);
    code.reserveRegister(Register::rA);
    code.reserveRegister(Register::rC);

    fn.writeLine("mov rdx, 0");

    this->loadToRegister(Register::rA, code);
    amountAsNum->loadToRegister(Register::rC, code);

    fn.writeLine("div rcx");

    Register reg = code.getFreeRegister();
    fn.writeLine("mov " + registerToString(8, reg) + ", rax");

    code.freeRegister(Register::rA);
    code.freeRegister(Register::rD);
    code.freeRegister(Register::rC);

    return std::make_shared<NumRValueStructure>(reg);
}

std::shared_ptr<ACC::Structure>
ACC::NumStructure::operatorEqual(std::shared_ptr<Structure> other, ACC::Code &code) {
    if(other->type != Type(BuiltIns::numType))
        throw std::runtime_error("Comparision operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<NumStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("sete " + registerToString(1, lhs));

    code.freeRegister(rhs);
    

    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::NumStructure::operatorNotEqual(std::shared_ptr<Structure> other,
                                                                          ACC::Code &code) {
    if(other->type != Type(BuiltIns::numType))
        throw std::runtime_error("Comparision operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<NumStructure *>(other.get());

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
ACC::NumStructure::operatorLess(std::shared_ptr<Structure> other, ACC::Code &code) {
    if(other->type != Type(BuiltIns::numType))
        throw std::runtime_error("Comparision operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<NumStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setl " + registerToString(1, lhs));

    code.freeRegister(rhs);
    

    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::NumStructure::operatorGreater(std::shared_ptr<Structure> other,
                                                                         ACC::Code &code) {
    if(other->type != Type(BuiltIns::numType))
        throw std::runtime_error("Comparision operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<NumStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setg " + registerToString(1, lhs));

    code.freeRegister(rhs);
    

    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::NumStructure::operatorLessEqual(std::shared_ptr<Structure> other,
                                                                           ACC::Code &code) {
    if(other->type != Type(BuiltIns::numType))
        throw std::runtime_error("Comparision operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<NumStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setle " + registerToString(1, lhs));

    code.freeRegister(rhs);
    

    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::NumStructure::operatorGreaterEqual(std::shared_ptr<Structure> other,
                                                                              ACC::Code &code) {
    if(other->type != Type(BuiltIns::numType))
        throw std::runtime_error("Comparision operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<NumStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setge " + registerToString(1, lhs));

    code.freeRegister(rhs);
    

    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::NumStructure::operatorModulo(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    if(other->type != Type(BuiltIns::numType))
        throw std::runtime_error("Arithmetic operator expects right hand side to be of type `num`");

    auto &fn = code.getFnSymbol();
    auto amountAsNum = dynamic_cast<NumStructure *>(other.get());

    code.reserveRegister(Register::rD);
    code.reserveRegister(Register::rA);
    code.reserveRegister(Register::rC);

    fn.writeLine("mov rdx, 0");

    this->loadToRegister(Register::rA, code);
    amountAsNum->loadToRegister(Register::rC, code);

    fn.writeLine("div rcx");

    Register reg = code.getFreeRegister();
    fn.writeLine("mov " + registerToString(8, reg) + ", rdx"); // Div stores in rax quotient and rdx stores remainder.

    code.freeRegister(Register::rA);
    code.freeRegister(Register::rD);
    code.freeRegister(Register::rC);

    return std::make_shared<NumRValueStructure>(reg);
}
