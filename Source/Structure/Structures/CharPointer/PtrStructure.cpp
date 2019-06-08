#include <utility>

//
// Created by a_mod on 07.06.2019.
//

#include "PtrRValueStructure.h"
#include "PtrLValueStructure.h"
#include "PtrStructure.h"
#include <General/builtinTypes.h>
#include <Assembly/Code.h>

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorForDone(std::shared_ptr<ACC::Structure> limit, ACC::Code &code) {
    return Structure::operatorForDone(limit, code);
}

std::shared_ptr<ACC::Structure> ACC::PtrStructure::operatorForNext(ACC::Code & code) {
    return Structure::operatorForNext(code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorAdd(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorAdd(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorSubtract(std::shared_ptr<ACC::Structure> amount, ACC::Code & code) {
    return Structure::operatorSubtract(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorMultiplication(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorMultiplication(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorDivision(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorDivision(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorNotEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorNotEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorLess(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLess(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorGreater(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreater(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorLessEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLessEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrStructure::operatorGreaterEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreaterEqual(other, code);
}

ACC::PtrStructure::PtrStructure(ValueCategory v, Type t) : ElementaryStructure(v, Type(BuiltIns::ptrType)){

}
