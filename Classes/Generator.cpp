//
// Created by a_mod on 06.01.2019.
//

#include <iostream>
#include "Generator.h"

ACC::Generator::Generator(ACC::OperandHandler input) : input(input){
    for(const auto& expr : this->input){
        delegate(expr);
    }
}

void ACC::Generator::handleVariable(ACC::Operand *operand) {
    Variable var;
    Operand* declaration = operand->lhs;
    Operand* value = operand->rhs;
    var.idf = declaration->at(1).content;
    if(isVariableDefined(var.idf))
        throw std::runtime_error("Redefinition of var: \"" + var.idf + "\"");

    var.code = eval(value);

    variables.push_back(var);
}

void ACC::Generator::delegate(ACC::Operand *operand) {
    if(operand->at(0).id == TokenId::TOKEN_VAR)
        handleVariable(operand);
    else
        handleKeyWord(operand);
}

bool ACC::Generator::isVariableDefined(std::string idf) {
    bool out = false;
    for(const auto& it : variables){
        if(it.idf == idf){
            out = true;
            break;
        }
    }
    return out;
}

std::string ACC::Generator::eval(ACC::Operand *op, std::string code) {
    std::string topOperator;
    auto tokens = op->data;
    if(tokens.size() == 1 && !tokens.at(0).subToken.empty())
        tokens = tokens.at(0).subToken;

    for(const auto& token : tokens){
        if(token.id == TokenId::TOKEN_ASSIGN || token.id == TokenId::TOKEN_PLUS || token.id == TokenId::TOKEN_MINUS){
            topOperator = token.content;
            break;
        }
    }

    if(topOperator.empty()) // no operator => either number or variable
        return "(" + evalLiteral(tokens.at(0).content) + ")";

    return "( (" + eval(op->lhs) + ")" + topOperator + "(" + eval(op->rhs) + ") )";
}

bool ACC::Generator::isNumber(std::string idf) {
    bool out = true;
    try {
        std::stoi(idf);
    }catch (...){
        out = false;
    }
    return out;
}

std::string ACC::Generator::getVariable(std::string idf) {
    for(const auto& var : variables){
        if(var.idf == idf)
            return var.code;
    }
    return "";
}

std::string ACC::Generator::evalLiteral(std::string idf) {
        if(isNumber(idf))
            return "(" + idf + ")";
        else if(isVariableDefined(idf))
            return "(" + getVariable(idf) + ")";
        else
            throw std::runtime_error("Fucked up idf: " + idf);
}

void ACC::Generator::handleKeyWord(ACC::Operand *operand) {
    if(operand->at(0).id == TokenId::TOKEN_PRINT){
        Command command;
        command.idf = "print";
        command.code = evalLiteral(operand->at(1).content);
        commands.push_back(command);
        result.emplace_back("print(" + command.code + ")");
    }
}