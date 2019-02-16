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

void ACC::Code::removeUnary(size_t idx) {
    auto op = data.at(idx);
    for(size_t i = idx; i < data.size(); i++){
        Operator* next = data.at(i);

        if(op->result == next->lhs || op->result == next->rhs){
            if(op->result == next->lhs){
                next->lhs = op->lhs;
                next->opLhs = op->opLhs;
            }

            if(op->result == next->rhs){
                next->rhs = op->lhs;
                next->opRhs = op->opLhs;
            }

            if(op->opLhs)
                op->opLhs->opResult = next;
        }
    }


    data.erase(data.begin() + idx);
}

void ACC::Code::print() {
    for(const auto& op : data){
        LOG() << op->asString() << std::endl;
    }
}

void ACC::Code::remove(size_t idx) {
    data.erase(data.begin() + idx);
}

