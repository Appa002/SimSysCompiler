//
// Created by a_mod on 03.06.2019.
//

#include "Structure.h"
#include <stdexcept>
#include <Structure/Structure.h>

ACC::Structure::~Structure() = default;


std::shared_ptr<ACC::Structure> ACC::Structure::operatorForDone(std::shared_ptr<Structure> limit, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorForNext(Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorCopy(std::shared_ptr<Structure> address, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorAdd(std::shared_ptr<Structure> amount, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorSubtract(std::shared_ptr<Structure> amount, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorMultiplication(std::shared_ptr<Structure> amount, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorDivision(std::shared_ptr<Structure> amount, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorEqual(std::shared_ptr<Structure> other, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorNotEqual(std::shared_ptr<Structure> other, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorLess(std::shared_ptr<Structure> other, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorGreater(std::shared_ptr<Structure> other, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorLessEqual(std::shared_ptr<Structure> other, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorGreaterEqual(std::shared_ptr<Structure> other, Code &code) {
    throw std::runtime_error("Operator not implemented");
}

ACC::Structure::Structure(ACC::ValueCategory valueCategory, Type type)
: vCategory(valueCategory), type(type){

}

std::shared_ptr<ACC::Structure> ACC::Structure::operatorNot(ACC::Code &code) {
    throw std::runtime_error("Operator not implemented");
}

