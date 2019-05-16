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
            {Symbol::start,       {Symbol::ifStmt, Symbol::EXTENT}},
            {Symbol::start,       {Symbol::keyword, Symbol::EOS}},
            {Symbol::start,       {Symbol::call, Symbol::EOS}},

            {Symbol::start,       {Symbol::assignment, Symbol::EOS, Symbol::start}},
            {Symbol::start,       {Symbol::function, Symbol::EXTENT, Symbol::start}},
            {Symbol::start,       {Symbol::ifStmt, Symbol::EXTENT, Symbol::start}},
            {Symbol::start,       {Symbol::keyword, Symbol::EOS, Symbol::start}},
            {Symbol::start,       {Symbol::call, Symbol::EOS, Symbol::start}},



            {Symbol::function,    {Symbol::FUNCTION, Symbol::DECL, Symbol::BRACKET, Symbol::BRACKET, Symbol::TYPE,
                                          Symbol::COLON, Symbol::INDENT, Symbol::start}},

            {Symbol::function,    {Symbol::FUNCTION, Symbol::DECL, Symbol::BRACKET, Symbol::paramsDecl, Symbol::BRACKET,
                                        Symbol::TYPE, Symbol::COLON, Symbol::INDENT, Symbol::start}},


            {Symbol::paramsDecl,  {Symbol::DECL, Symbol::TYPE}},
            {Symbol::paramsDecl,  {Symbol::DECL, Symbol::TYPE, Symbol::COMMA, Symbol::paramsDecl}},


            {Symbol::call,        {Symbol::ID,    Symbol::BRACKET, Symbol::BRACKET}},
            {Symbol::call,        {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET}},

            {Symbol::paramsList,  {Symbol::expr}},
            {Symbol::paramsList,  {Symbol::expr, Symbol::COMMA, Symbol::paramsList}},


            {Symbol::assignment,  {Symbol::VAR, Symbol::DECL, Symbol::TYPE, Symbol::ASSIGN, Symbol::expr}},
            {Symbol::assignment,  {Symbol::ID, Symbol::ASSIGN, Symbol::expr}},

            {Symbol::keyword,     {Symbol::SYSCALL, Symbol::expr}},
            {Symbol::keyword,     {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr}},
            {Symbol::keyword,     {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}},
            {Symbol::keyword,     {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}},
            {Symbol::keyword,     {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}},
            {Symbol::keyword,     {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}},
            {Symbol::keyword,     {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}},

            {Symbol::keyword,     {Symbol::EXIT, Symbol::expr}},
            {Symbol::keyword,     {Symbol::RETURN, Symbol::expr}},
            {Symbol::keyword,     {Symbol::SYSCALL, Symbol::expr}},

            {Symbol::ifStmt,      {Symbol::IF, Symbol::BRACKET, Symbol::expr, Symbol::BRACKET, Symbol::COLON, Symbol::INDENT, Symbol::start}},


            {Symbol::expr,        {Symbol::ID,    Symbol::BRACKET, Symbol::BRACKET}},
            {Symbol::expr,        {Symbol::ID,    Symbol::BRACKET, Symbol::BRACKET, Symbol::expr}},

            {Symbol::expr,        {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET}},
            {Symbol::expr,        {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET, Symbol::expr}},

            {Symbol::expr,        {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET}},
            {Symbol::expr,        {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET, Symbol::expr}},

            {Symbol::expr,        {Symbol::LITERAL}},
            {Symbol::expr,        {Symbol::LITERAL, Symbol::expr}},

            {Symbol::expr,        {Symbol::ID}},
            {Symbol::expr,        {Symbol::ID, Symbol::expr}},

            {Symbol::expr,        {Symbol::MATH_OPERATOR, Symbol::expr}},
            {Symbol::expr,        {Symbol::CMP, Symbol::expr}}
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
        case Symbol::SYSCALL:
            return "syscall";
        case Symbol::LITERAL:
            return "data";
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
        case Symbol::TYPE:
            return "type";
        case Symbol::IF:
            return "IF";
        case Symbol::ifStmt:
            return "ifStmt";
        case Symbol::CMP:
            return "EQUAL";
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

