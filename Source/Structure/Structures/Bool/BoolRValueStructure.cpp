//
// Created by a_mod on 07.06.2019.
//

#include <General/builtinTypes.h>
#include "BoolRValueStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"
#include "BoolLValueStructure.h"
#include <Assembly/Code.h>

ACC::BoolRValueStructure::BoolRValueStructure(ACC::Register reg) : ElementaryStructure(ValueCategory::rvalue,
Type(BuiltIns::boolType)), reg(reg){

}

std::shared_ptr<ACC::Structure>
ACC::BoolRValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> address, ACC::Code & code) {
    if(address->vCategory == ValueCategory::rvalue){
        auto addressAsBool = dynamic_cast<BoolRValueStructure*>(address.get());
        loadToRegister(addressAsBool->reg, code);
        return std::make_shared<BoolRValueStructure>(addressAsBool->reg);
    }

    if(address->vCategory == ValueCategory::lvalue){
        auto addressAsLValue = dynamic_cast<GenericLValueStructure*>(address.get());
        auto& fn = code.getFnSymbol();
        fn.writeLine("mov [" + addressAsLValue->getAccess() + "], " + registerToString(1, reg));
        return std::make_shared<BoolLValueStructure>(addressAsLValue->getAccess());
    }
    return nullptr;
}

std::shared_ptr<ACC::Structure>
ACC::BoolRValueStructure::operatorEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::BoolRValueStructure::operatorNotEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorNotEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::BoolRValueStructure::operatorLess(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLess(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::BoolRValueStructure::operatorGreater(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreater(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::BoolRValueStructure::operatorLessEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLessEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::BoolRValueStructure::operatorGreaterEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreaterEqual(other, code);
}

void ACC::BoolRValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    if(this->reg == reg)
        return;
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(1, reg) + ", " + registerToString(1, this->reg));
}

