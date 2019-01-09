//
// Created by a_mod on 06.01.2019.
//

#include <iostream>
#include "OperandHandler.h"

ACC::OperandHandler::OperandHandler(DepthParsedInput input) {
    referenceCount++;
    std::vector<Token> expr;
    for(const auto& token : input){
        if(token.id == TokenId::TOKEN_EOE){
            data.push_back(new Operand(expr));
            expr.clear();
            continue;
        }
        if(token.id != TokenId::TOKEN_NEWLINE)
            expr.push_back(token);
    }
}

ACC::Operand* &ACC::OperandHandler::at(unsigned idx) {
    return data.at(idx);
}

void ACC::OperandHandler::prettyPrint() {
    std::stringstream ss;
    void *t = this;
    ss << "---- Pretty Print of ExpressionizedInput at " << std::hex << t << " ----" << std::endl;
    unsigned long startMsgLen = ss.str().length();
    std::cout << ss.str();

    for (auto &expr : data) {
        std::cout << "Tree Output for: " << expr->simplePrint() << std::endl;
        std::vector<std::string> ss_vec;
        expr->prettyPrint(&ss_vec);

        for (const auto &line : ss_vec) {
            std::cout << "(" << line << std::endl;
        }

        std::cout << std::endl << std::endl;
    }

    std::cout << "List of found expressions: " << std::endl;
    for (auto &expr : data) {
        std::cout << "Expression: " << expr->simplePrint() << std::endl;
    }
    while (startMsgLen != 1) {
        std::cout << "-";
        startMsgLen--;
    }
    std::cout << std::endl << std::endl;

}

std::vector<ACC::Operand *, std::allocator<ACC::Operand *>>::iterator ACC::OperandHandler::begin() {
    return data.begin();
}

std::vector<ACC::Operand *, std::allocator<ACC::Operand *>>::iterator ACC::OperandHandler::end() {
    return data.end();
}

ACC::OperandHandler::~OperandHandler() {
    referenceCount--;
    if(referenceCount != 0)
        return;

    for(const auto& op : data){
        delete op;
    }
}

ACC::OperandHandler::OperandHandler(const ACC::OperandHandler &other)
: data(other.data), referenceCount(other.referenceCount){
    referenceCount++;
}
