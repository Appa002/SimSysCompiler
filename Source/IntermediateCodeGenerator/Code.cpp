//
// Created by a_mod on 10.02.2019.
//

#include <Logger/Logger.h>
#include "Code.h"

ACC::Dependency& ACC::Code::getSymbol(std::string sym) {
    if(symTable.find(sym) == symTable.end())
        return symTable.at("none");
    else
        return symTable.at(sym);
}

ACC::Dependency& ACC::Code::emplaceSymbol(std::string sym, Operator* op) {
    symTable[sym] = {++temporaryCounter, op};
    return symTable.at(sym);
}


ACC::Dependency ACC::Code::createTemporary() {
    return {++temporaryCounter};
}

std::vector<ACC::Operator*, std::allocator<ACC::Operator*>>::iterator ACC::Code::begin() {
    return data.begin();
}

std::vector<ACC::Operator*, std::allocator<ACC::Operator*>>::iterator ACC::Code::end() {
    return data.end();
}

ACC::Operator* ACC::Code::at(size_t idx) {
    return data.at(idx);
}

std::vector<ACC::Operator*>& ACC::Code::getData() {
    return data;
}

void ACC::Code::pushOp(ACC::Operator *const &op) {
    data.push_back(op);
}

ACC::Code::Code() {
    symTable["none"] = {};
}

void ACC::Code::removeOp(size_t idx) {
    auto op = data.at(idx);
    Operator* prev = nullptr;

    for(auto const & i : data){
        if(i->opLhs == op || i->opRhs == op){
            prev = i;
            break;
        }
    }
    if(prev != nullptr){
        prev->opLhs = op->opLhs;
        prev->opRhs = op->opRhs;

        prev->lhs = op->lhs;
        prev->rhs = op->rhs;
    }

    data.erase(data.begin() + idx);
}

