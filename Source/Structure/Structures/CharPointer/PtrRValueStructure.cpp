#include <utility>

//
// Created by a_mod on 07.06.2019.
//

#include "PtrRValueStructure.h"
#include "PtrLValueStructure.h"
#include <General/builtinTypes.h>
#include <Assembly/Code.h>

ACC::PtrRValueStructure::PtrRValueStructure(std::string access)
: ElementaryStructure(ValueCategory::rvalue, BuiltIns::ptrCharType), access(std::move(access)) {

}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorForDone(std::shared_ptr<ACC::Structure> limit, ACC::Code &code) {
    return Structure::operatorForDone(limit, code);
}

std::shared_ptr<ACC::Structure> ACC::PtrRValueStructure::operatorForNext(ACC::Code & code) {
    return Structure::operatorForNext(code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->vCategory == ValueCategory::lvalue){
        auto &fn = code.getFnSymbol();
        auto *addressAsLValue = dynamic_cast<GenericLValueStructure *>(address.get());

        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        fn.writeLine("lea " + regStr + ", [" + access + "]");
        fn.writeLine("mov [ " + addressAsLValue->getAccess() + " ], " + regStr);

        return std::make_shared<PtrLValueStructure>(addressAsLValue->getAccess());
    }
    return nullptr;
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorAdd(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorAdd(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorSubtract(std::shared_ptr<ACC::Structure> amount, ACC::Code & code) {
    return Structure::operatorSubtract(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorMultiplication(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorMultiplication(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorDivision(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorDivision(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorNotEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorNotEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorLess(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLess(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorGreater(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreater(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorLessEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLessEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrRValueStructure::operatorGreaterEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreaterEqual(other, code);
}

void ACC::PtrRValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("lea " + registerToString(8, reg) + ", [" + access + "]");
}


