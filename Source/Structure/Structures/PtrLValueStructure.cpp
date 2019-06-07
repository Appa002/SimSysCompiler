//
// Created by a_mod on 07.06.2019.
//

#include "NumRValueStructure.h"
#include "NumLValueStructure.h"
#include "PtrLValueStructure.h"

#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>

ACC::PtrLValueStructure::PtrLValueStructure(std::string access)
: ElementaryLValueStructure(BuiltIns::ptrCharType, access) {

}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorForDone(std::shared_ptr<ACC::Structure> limit, ACC::Code &code) {
    return Structure::operatorForDone(limit, code);
}

std::shared_ptr<ACC::Structure> ACC::PtrLValueStructure::operatorForNext(ACC::Code & code) {
    return Structure::operatorForNext(code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorAdd(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorAdd(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorSubtract(std::shared_ptr<ACC::Structure> amount, ACC::Code & code) {
    return Structure::operatorSubtract(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorMultiplication(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorMultiplication(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorDivision(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    return Structure::operatorDivision(amount, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorNotEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorNotEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorLess(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLess(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorGreater(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreater(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorLessEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorLessEqual(other, code);
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorGreaterEqual(std::shared_ptr<ACC::Structure> other, ACC::Code &code) {
    return Structure::operatorGreaterEqual(other, code);
}

