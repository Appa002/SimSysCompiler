//
// Created by a_mod on 18.01.2019.
//

#include <stdexcept>
#include "grammar.h"
#include <Parser/Production.h>

bool ACC::isNoneterminal(Symbol sys) {
    return sys > Symbol::none_terminals_start;

}

std::vector<ACC::Production> ACC::data::getGrammar() {
    return {

            {Symbol::start,       {Symbol::assignment, Symbol::EOS}},
            {Symbol::start,       {Symbol::function, Symbol::EXTENT}},
            {Symbol::start,       {Symbol::keyword, Symbol::EOS}},
            {Symbol::start,       {Symbol::call, Symbol::EOS}},

            {Symbol::start,       {Symbol::assignment, Symbol::EOS, Symbol::start}},
            {Symbol::start,       {Symbol::function, Symbol::EXTENT, Symbol::start}},
            {Symbol::start,       {Symbol::keyword, Symbol::EOS, Symbol::start}},
            {Symbol::start,       {Symbol::call, Symbol::EOS, Symbol::start}},



            {Symbol::function,    {Symbol::FUNCTION, Symbol::DECL, Symbol::BRACKET, Symbol::paramsDecl, Symbol::BRACKET,
                                   Symbol::COLON, Symbol::INDENT, Symbol::start}},

            {Symbol::paramsDecl,  {Symbol::DECL}},
            {Symbol::paramsDecl,  {Symbol::DECL, Symbol::COMMA, Symbol::paramsDecl}},

            {Symbol::call,        {Symbol::ID, Symbol::BRACKET, Symbol::BRACKET}},
            {Symbol::call,        {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET}},


            {Symbol::paramsList,  {Symbol::expr}},
            {Symbol::paramsList,  {Symbol::expr, Symbol::COMMA, Symbol::paramsList}},


            {Symbol::assignment,  {Symbol::VAR, Symbol::DECL, Symbol::ASSIGN, Symbol::expr}},

            {Symbol::keyword,     {Symbol::PRINT, Symbol::ID}},
            {Symbol::keyword,     {Symbol::PRINT, Symbol::LITERAL}},

            {Symbol::keyword,     {Symbol::EXIT, Symbol::LITERAL}},
            {Symbol::keyword,     {Symbol::EXIT, Symbol::ID}},

            {Symbol::keyword,     {Symbol::RETURN, Symbol::LITERAL}},
            {Symbol::keyword,     {Symbol::RETURN, Symbol::ID}},

            {Symbol::expr,        {Symbol::LITERAL}}, // E ::= A-Za-z0-9
            {Symbol::expr,        {Symbol::ID}}, // E ::= A-Za-z0-9
            {Symbol::expr,        {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET}}, // (E)
            {Symbol::expr,        {Symbol::expr,    Symbol::MATH_OPERATOR, Symbol::expr}} // E-E
    };
}

std::string ACC::data::symbolToString(::ACC::Symbol s) {
    switch (s) {
        case Symbol::empty:
            return "-1";
        case Symbol::VAR:
            return "var";
        case Symbol::ID:
            return "id";
        case Symbol::BRACKET:
            return "bracket";
        case Symbol::MATH_OPERATOR:
            return "math operator";
        case Symbol::PRINT:
            return "print";
        case Symbol::LITERAL:
            return "literal";
        case Symbol::EOS:
            return "end of statement";
        case Symbol::none_terminals_start:
            return "n_t_s";
        case Symbol::expr:
            return "expr";
        case Symbol::stmt:
            return "stmt";
        case Symbol::start:
            return "start";
        case Symbol::declaration:
            return "declaration";
        case Symbol::assignment:
            return "assignment";
        case Symbol::keyword:
            return "keyword";
        case Symbol::DECL:
            return "decl";
        case Symbol::ASSIGN:
            return "assign";
        case Symbol::EXIT:
            return "exit";
        case Symbol::INDENT:
            return "indent";
        case Symbol::EXTENT:
            return "extent";
        case Symbol::FUNCTION:
            return "fn";
        case Symbol::COLON:
            return ":";
        case Symbol::COMMA:
            return ",";
        case Symbol::function:
            return "function";
        case Symbol::paramsDecl:
            return "params";
        case Symbol::paramsList:
            return "paramsList";
        case Symbol::call:
            return "call";
        case Symbol::RETURN:
            return "return";
    }
    throw std::runtime_error("Symbol not known.");
}

std::string ACC::data::productionToString(ACC::Production p) {
    std::string out = symbolToString(p.head);
    out += " ::= ";
    for (auto const &s : p.body) {
        out += "`" + symbolToString(s) + "` ";
    }
    return out;
}

