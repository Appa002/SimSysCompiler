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
    Operator* next = nullptr;

    for(auto const & i : data){
        if(i->opLhs == op || i->opRhs == op){
            next = i;
            break;
        }
    }
    if(next != nullptr){
        next->opLhs = op->opLhs;
        next->opRhs = op->opRhs;

        if(op->result == next->lhs)
            next->lhs = op->lhs;
        if(op->result == next->rhs)
            next->rhs = op->lhs;
      //  next->result = op->result;
    }

    data.erase(data.begin() + idx);
}

void ACC::Code::print() {
    for(const auto& op : data){
        LOG() << operator2String(*op) << std::endl;
    }
}


std::string ACC::Code::operator2String(ACC::Operator op) {
    switch (op.id) {
        case OperatorId::PLUS:
            return std::string("add, ") + printAsTemporary(op.result) + ", " + printAsTemporary(op.lhs) + ", " +
                   printAsTemporary(op.rhs);
        case OperatorId::MINUS:
            return std::string("subtract, ") + printAsTemporary(op.result) + ", " + printAsTemporary(op.lhs) + ", " +
                   printAsTemporary(op.rhs);

        case OperatorId::COPY:
            return std::string("copy, ") + printAsTemporary(op.result) + ", " + printAsTemporary(op.lhs);

        case OperatorId::PRINT:
            return std::string("print, ") + printAsTemporary(op.lhs);

        case OperatorId::ICOPY:
            return std::string("icopy, ") + printAsTemporary(op.result) + ", " + std::to_string(op.lhs);
    }
    return "";
}

std::string ACC::Code::printAsTemporary(ACC::temporary temp){
    return "t" + std::to_string(temp);
}

