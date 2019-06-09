//
// Created by a_mod on 08.06.2019.
//

#include "CharStructure.h"

//
// Created by a_mod on 08.06.2019.
//

#include <General/builtinTypes.h>
#include "CharStructure.h"
#include "CharIValueStructure.h"
#include "CharRValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <Structure/Structures/Bool/BoolRValueStructure.h>
#include <Structure/Structures/Bool/BoolLValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/Number/NumStructure.h>
#include <Structure/Structures/Number/NumIValueStructure.h>

ACC::CharStructure::CharStructure(ACC::ValueCategory v) : ElementaryStructure(v, Type(BuiltIns::charType)) {

}


std::shared_ptr<ACC::Structure> ACC::CharStructure::operatorForNext(ACC::Code &code) {
    auto rValue = operatorAdd(std::make_shared<NumIValueStructure>(1), code);
    rValue->operatorCopy(shared_from_this(), code);
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::CharStructure::operatorForDone(std::shared_ptr<Structure> limit,
                                                                   ACC::Code &code) {
    // setting rflags such that an equals comparision is false if the loop is done


    auto limitAsI = dynamic_cast<CharStructure *>(limit.get());
    auto &fn = code.getFnSymbol();

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    limitAsI->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setle " + registerToString(1, lhs));
    fn.writeLine("cmp " + registerToString(1, lhs) + ", 1");

    code.freeRegister({lhs, rhs});

    return nullptr;
}


std::shared_ptr<ACC::Structure>
ACC::CharStructure::operatorAdd(std::shared_ptr<Structure> amount, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto *amountAsElem = dynamic_cast<NumStructure *>(amount.get());

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(1, lhs);
    std::string rhsAsString = registerToString(1, rhs); /* TODO: Compiler warning about size. */

    this->loadToRegister(lhs, code);
    amountAsElem->loadToRegister(rhs, code);

    fn.writeLine("add " + lhsAsString + ", " + rhsAsString);

    code.freeRegister(rhs);


    return std::make_shared<CharRValueStructure>(lhs);

}

std::shared_ptr<ACC::Structure> ACC::CharStructure::operatorSubtract(std::shared_ptr<Structure> amount,
                                                                    ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto *amountAsElem = dynamic_cast<NumStructure *>(amount.get());

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(1, lhs);
    std::string rhsAsString = registerToString(1, rhs); /* TODO: Compiler warning about size. */

    this->loadToRegister(lhs, code);
    amountAsElem->loadToRegister(rhs, code);

    fn.writeLine("sub " + lhsAsString + ", " + rhsAsString);

    code.freeRegister(rhs);


    return std::make_shared<CharRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::CharStructure::operatorMultiplication(std::shared_ptr<Structure> amount, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto *amountAsElem = dynamic_cast<NumStructure *>(amount.get());

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(1, lhs);
    std::string rhsAsString = registerToString(1, rhs); /* TODO: Compiler warning about size. */

    this->loadToRegister(lhs, code);
    amountAsElem->loadToRegister(rhs, code);

    fn.writeLine("imul " + lhsAsString + ", " + rhsAsString);

    code.freeRegister(rhs);


    return std::make_shared<CharRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::CharStructure::operatorDivision(std::shared_ptr<Structure> amount,
                                                                    ACC::Code &code) {

    auto &fn = code.getFnSymbol();
    auto amountAsNum = dynamic_cast<NumStructure *>(amount.get());

    code.reserveRegister(Register::rD);
    code.reserveRegister(Register::rA);
    code.reserveRegister(Register::rC);

    fn.writeLine("mov dl, 0");

    this->loadToRegister(Register::rA, code);
    amountAsNum->loadToRegister(Register::rC, code); /*TODO:Add warning about size. */

    fn.writeLine("div cl");

    Register reg = code.getFreeRegister();
    fn.writeLine("mov " + registerToString(8, reg) + ", rax");

    code.freeRegister(Register::rA);
    code.freeRegister(Register::rD);
    code.freeRegister(Register::rC);

    return std::make_shared<CharRValueStructure>(reg);
}

std::shared_ptr<ACC::Structure>
ACC::CharStructure::operatorEqual(std::shared_ptr<Structure> other, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("sete " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::CharStructure::operatorNotEqual(std::shared_ptr<Structure> other,
                                                                    ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get()); //TODO: Proper type conversion...

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setne " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::CharStructure::operatorLess(std::shared_ptr<Structure> other, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setl " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::CharStructure::operatorGreater(std::shared_ptr<Structure> other,
                                                                   ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setg " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::CharStructure::operatorLessEqual(std::shared_ptr<Structure> other,
                                                                     ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setle " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::CharStructure::operatorGreaterEqual(std::shared_ptr<Structure> other,
                                                                        ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure *>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(1, lhs) + ", " + registerToString(1, rhs));
    fn.writeLine("setge " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}