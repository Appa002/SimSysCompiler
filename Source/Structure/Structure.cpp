//
// Created by a_mod on 03.06.2019.
//

#include "Structure.h"
#include <stdexcept>
#include <Structure/Structure.h>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>
#include <Error/Errors.h>

ACC::Structure::~Structure() = default;


std::shared_ptr<ACC::Structure> ACC::Structure::operatorForDone(std::shared_ptr<Structure> limit, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorForDone");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorForNext(Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorForNext");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorCopy(std::vector<std::shared_ptr<Structure>> objList, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorCopy");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorAdd(std::shared_ptr<Structure> amount, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorAdd");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorSubtract(std::shared_ptr<Structure> amount, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorSubtract");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorMultiplication(std::shared_ptr<Structure> amount, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorMultiplication");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorDivision(std::shared_ptr<Structure> amount, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorDivision");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorEqual(std::shared_ptr<Structure> other, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorEqual");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorNotEqual(std::shared_ptr<Structure> other, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorNotEqual");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorLess(std::shared_ptr<Structure> other, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorLess");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorGreater(std::shared_ptr<Structure> other, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorGreater");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorLessEqual(std::shared_ptr<Structure> other, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorLessEqual");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorGreaterEqual(std::shared_ptr<Structure> other, Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorGreaterEqual");
}

ACC::Structure::Structure(ACC::ValueCategory valueCategory, Type type)
: vCategory(valueCategory), type(type){
}


std::shared_ptr<ACC::Structure> ACC::Structure::operatorNot(ACC::Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorNot");
}

void ACC::Structure::cleanUp(Code& code) {
    code.freeRegister(registerInUse);
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorDereference(ACC::Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorDereference");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorChar(ACC::Code &code) {
    throw errors::InvalidType(nullptr, "char", "copy");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorNum(ACC::Code &code) {
    throw errors::InvalidType(nullptr, "num", "copy");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorBool(ACC::Code &code) {
    throw errors::InvalidType(nullptr, "bool", "copy");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorPtr(Code &code, Type pointingTo) {
    throw errors::InvalidType(nullptr, "ptr", "copy");
}

std::shared_ptr<ACC::Structure>
ACC::Structure::operatorModulo(std::shared_ptr<ACC::Structure> amount, ACC::Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorModulo");
}

bool ACC::Structure::hasConversionTo(const Type &id) {
    return true;
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorDot(ACC::Code &code, std::string member) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorDot");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorOr(std::shared_ptr<Structure> other, ACC::Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorOr");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorAnd(std::shared_ptr<Structure> other, ACC::Code &code) {
    throw errors::UnimplementedFunction(nullptr, this->type.id, "operatorAnd");
}





