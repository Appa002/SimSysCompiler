#include <utility>

//
// Created by a_mod on 03.06.2019.
//

#include "NumLValueStructure.h"
#include "NumRValueStructure.h"
#include "NumIValueStructure.h"
#include "ElementaryLValueStructure.h"
#include "BoolRValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorForNext(ACC::Code &code) {
    auto rValue = operatorAdd(std::make_shared<NumIValueStructure>(1), code);
    rValue->operatorCopy(shared_from_this(), code);
    return shared_from_this();
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorForDone(std::shared_ptr<Structure> limit,
                                                                        ACC::Code &code) {
    // setting rflags such that an equals comparision is false if the loop is done


    if(limit->vCategory == ValueCategory::ivalue){
        auto limitAsI = dynamic_cast<NumIValueStructure*>(limit.get());
        auto& fn = code.getFnSymbol();

        Register lhs = code.getFreeRegister();
        Register rhs = code.getFreeRegister();

        this->loadToRegister(lhs, code);
        limitAsI->loadToRegister(rhs, code);

        fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
        fn.writeLine("setl " + registerToString(1, lhs));
        fn.writeLine("cmp " + registerToString(1, lhs) + ", 1");
    }

    return shared_from_this();
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
    auto& fn = code.getFnSymbol();
    auto* amountAsElem = dynamic_cast<ElementaryStructure*>(amount.get());

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(8, lhs);
    std::string rhsAsString = registerToString(8, rhs);

    this->loadToRegister(lhs, code);
    amountAsElem->loadToRegister(rhs, code);

    fn.writeLine("sub "+lhsAsString+", " + rhsAsString);

    code.freeRegister(rhs);

    return std::make_shared<NumRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure>
ACC::NumLValueStructure::operatorMultiplication(std::shared_ptr<Structure> amount, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto* amountAsElem = dynamic_cast<ElementaryStructure*>(amount.get());

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    std::string lhsAsString = registerToString(8, lhs);
    std::string rhsAsString = registerToString(8, rhs);

    this->loadToRegister(lhs, code);
    amountAsElem->loadToRegister(rhs, code);

    fn.writeLine("imul "+lhsAsString+", " + rhsAsString);

    code.freeRegister(rhs);

    return std::make_shared<NumRValueStructure>(lhs);}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorDivision(std::shared_ptr<Structure> amount,
                                                                         ACC::Code &code) {

    auto& fn = code.getFnSymbol();
    auto amountAsNum = dynamic_cast<ElementaryStructure*>(amount.get());

    code.reserveRegister(Register::rD);
    code.reserveRegister(Register::rA);
    code.reserveRegister(Register::rC);

    fn.writeLine("mov rdx, 0");

    this->loadToRegister(Register::rA, code);
    amountAsNum->loadToRegister(Register::rC, code);

    fn.writeLine("div rcx");

    Register reg = code.getFreeRegister();
    fn.writeLine("mov " + registerToString(8, reg)  + ", rax");

    code.freeRegister(Register::rA);
    code.freeRegister(Register::rD);
    code.freeRegister(Register::rC);

    return std::make_shared<NumRValueStructure>(reg);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorEqual(std::shared_ptr<Structure> other, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure*>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("sete " + registerToString(1, lhs));

    code.freeRegister(rhs);


    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorNotEqual(std::shared_ptr<Structure> other,
                                                                         ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure*>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setne " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorLess(std::shared_ptr<Structure> other, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure*>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setl " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorGreater(std::shared_ptr<Structure> other,
                                                                        ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure*>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setg " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorLessEqual(std::shared_ptr<Structure> other,
                                                                          ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure*>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setle " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

std::shared_ptr<ACC::Structure> ACC::NumLValueStructure::operatorGreaterEqual(std::shared_ptr<Structure> other,
                                                                             ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto otherAsElementary = dynamic_cast<ElementaryStructure*>(other.get());

    Register rhs = code.getFreeRegister();
    Register lhs = code.getFreeRegister();

    this->loadToRegister(lhs, code);
    otherAsElementary->loadToRegister(rhs, code);

    fn.writeLine("cmp " + registerToString(8, lhs) + ", " + registerToString(8, rhs));
    fn.writeLine("setge " + registerToString(1, lhs));

    code.freeRegister(rhs);
    return std::make_shared<BoolRValueStructure>(lhs);
}

ACC::NumLValueStructure::NumLValueStructure(std::string const &access)
: ElementaryLValueStructure(BuiltIns::numType, access){

}
