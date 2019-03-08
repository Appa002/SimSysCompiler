//
// Created by a_mod on 27.01.2019.
//

#include "SymbolTable.h"

ACC::SymbolTable::SymbolTable() : std::unordered_map<std::string, Symbol>() {
    this->emplace("var", Symbol::VAR);
    this->emplace("(", Symbol::BRACKET);
    this->emplace(")", Symbol::BRACKET);
    this->emplace("+", Symbol::MATH_OPERATOR);
    this->emplace("-", Symbol::MATH_OPERATOR);
    this->emplace("print", Symbol::PRINT);
    this->emplace(";", Symbol::EOS);
    this->emplace("=", Symbol::ASSIGN);
    this->emplace("exit", Symbol::EXIT);
}