//
// Created by a_mod on 07.06.2019.
//

#include "NumRValueStructure.h"
#include <Structure/Structure.h>
#include <Assembly/Code.h>

ACC::NumRValueStructure::NumRValueStructure(ACC::Register reg) : reg(reg){

}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorForDone(std::shared_ptr<Structure> limit,
                                                                        ACC::Code &code) {
    return Structure::operatorForDone(limit, code);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorForNext(ACC::Code &code) {
    return Structure::operatorForNext(code);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorCopy(std::shared_ptr<Structure> address,
                                                                     ACC::Code &code) {
    auto* addressAsNum = dynamic_cast<ElementaryStructure*>(address.get());
    Register other = code.getFreeRegister();
    addressAsNum->loadToRegister(other, code);
    return std::make_shared<NumRValueStructure>(other);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorAdd(std::shared_ptr<Structure> amount, ACC::Code &code) {
    auto& fn = code.getFnSymbol();

    auto* amountAsNum = dynamic_cast<ElementaryStructure*>(amount.get());

    Register other = code.getFreeRegister();
    amountAsNum->loadToRegister(other, code);

    std::string meAsString = registerToString(8, reg);
    std::string otherAsString = registerToString(8, other);

    fn.writeLine("add " + meAsString + ", " + otherAsString);
    code.freeRegister(other);
    return nullptr;
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorSubtract(std::shared_ptr<Structure> amount,
                                                                         ACC::Code &code) {
    auto& fn = code.getFnSymbol();

    auto* amountAsNum = dynamic_cast<ElementaryStructure*>(amount.get());

    Register other = code.getFreeRegister();
    amountAsNum->loadToRegister(other, code);

    std::string meAsString = registerToString(8, reg);
    std::string otherAsString = registerToString(8, other);

    fn.writeLine("sub " + meAsString + ", " + otherAsString);
    code.freeRegister(other);
    return nullptr;
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorMultiplication(std::shared_ptr<Structure> amount,
                                                                               ACC::Code &code) {
    auto& fn = code.getFnSymbol();

    auto* amountAsNum = dynamic_cast<ElementaryStructure*>(amount.get());

    Register other = code.getFreeRegister();
    amountAsNum->loadToRegister(other, code);

    std::string meAsString = registerToString(8, reg);
    std::string otherAsString = registerToString(8, other);

    fn.writeLine("imul " + meAsString + ", " + otherAsString);
    code.freeRegister(other);
    return nullptr;
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorDivision(std::shared_ptr<Structure> amount,
                                                                         ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto* amountAsNum = dynamic_cast<ElementaryStructure*>(amount.get());

    code.reserveRegister(Register::rD);
    code.reserveRegister(Register::rA);
    code.reserveRegister(Register::rC);

    fn.writeLine("mov rdx, 0");

    if(reg != Register::rA)
        fn.writeLine("mov rax, " + registerToString(8, reg));

    amountAsNum->loadToRegister(Register::rC, code);

    fn.writeLine("div rcx");
    fn.writeLine("mov "+ registerToString(8, reg) + ", rax");

    code.freeRegister(Register::rD);
    code.freeRegister(Register::rC);
    code.freeRegister(Register::rA);

    return nullptr;
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorEqual(std::shared_ptr<Structure> other, ACC::Code &code) {
    return Structure::operatorEqual(other, code);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorNotEqual(std::shared_ptr<Structure> other,
                                                                         ACC::Code &code) {
    return Structure::operatorNotEqual(other, code);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorLess(std::shared_ptr<Structure> other, ACC::Code &code) {
    return Structure::operatorLess(other, code);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorGreater(std::shared_ptr<Structure> other,
                                                                        ACC::Code &code) {
    return Structure::operatorGreater(other, code);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorLessEqual(std::shared_ptr<Structure> other,
                                                                          ACC::Code &code) {
    return Structure::operatorLessEqual(other, code);
}

std::shared_ptr<ACC::Structure> ACC::NumRValueStructure::operatorGreaterEqual(std::shared_ptr<Structure> other,
                                                                             ACC::Code &code) {
    return Structure::operatorGreaterEqual(other, code);
}


void ACC::NumRValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    if(reg == this->reg)
        return;

    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", " + registerToString(8, this->reg));
}
