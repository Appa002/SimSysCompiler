//
// Created by a_mod on 10.02.2019.
//

#include <Logger/Logger.h>
#include "Code.h"

ACC::Dependency &ACC::Code::getVarSymbol(std::string sym) {
    if (varTable.find(sym) == varTable.end())
        throw std::runtime_error("Unknown variable: " + sym);
    else
        return varTable.at(sym);
}

ACC::Dependency &ACC::Code::emplaceVarSymbol(std::string sym, Operator *op) {
    varTable[sym] = {++temporaryCounter, op};
    return varTable.at(sym);
}

ACC::FunctionId &ACC::Code::getFnSymbol(std::string sym) {
    if (fnTable.find(sym) == fnTable.end())
        throw std::runtime_error("Unknown fn: " + sym);
    else
        return fnTable.at(sym);
}

ACC::FunctionId &ACC::Code::emplaceFnSymbol(std::string sym) {
    fnTable[sym] = FunctionId(++fnCounter);
    return fnTable.at(sym);
}


ACC::Dependency ACC::Code::createTemporary() {
    return {++temporaryCounter};
}

std::vector<ACC::Operator *, std::allocator<ACC::Operator *>>::iterator ACC::Code::begin() {
    return data.begin();
}

std::vector<ACC::Operator *, std::allocator<ACC::Operator *>>::iterator ACC::Code::end() {
    return data.end();
}

ACC::Operator *ACC::Code::at(size_t idx) {
    return data.at(idx);
}

std::vector<ACC::Operator *> &ACC::Code::getData() {
    return data;
}

void ACC::Code::pushOp(ACC::Operator *const &op) {
    data.push_back(op);
}

ACC::Code::Code() = default;

void ACC::Code::removeUnary(size_t idx) {
    auto op = data.at(idx);
    for (size_t i = idx; i < data.size(); i++) {
        Operator *next = data.at(i);
        if(isImmediat(next->id))
            continue;

        if (op->result == next->lhs) {
            next->lhs = op->lhs;
            next->opLhs = op->opLhs;
        }

        if (op->result == next->rhs) {
            next->rhs = op->lhs;
            next->opRhs = op->opLhs;
        }
    }

    makeOperatorDead(idx);
    data.erase(data.begin() + idx);
}

void ACC::Code::print() {
    for (const auto &op : data) {
        LOG() << op->asString() << std::endl;
    }
}

void ACC::Code::remove(size_t idx) {
    makeOperatorDead(idx);
    data.erase(data.begin() + idx);
}

ACC::Code::~Code() {
    ref--;
    if (ref > 0)
        return;
    for (auto op : data) {
        delete op;
    }
}

ACC::Code::Code(Code const &other) : ref(other.ref), data(other.data),
                                     varTable(other.varTable), temporaryCounter(other.temporaryCounter) {
    ref++;
}

void ACC::Code::deleteDead() {
    for (auto op : data) {
        if (op->isDead())
            delete op;
    }
    for (auto op : deadOperators) {
        if (op->isDead())
            delete op;
    }
    deadOperators.clear();
}

void ACC::Code::makeOperatorDead(size_t idx) {
    data.at(idx)->makeDead();
    deadOperators.push_back(data.at(idx));
}

