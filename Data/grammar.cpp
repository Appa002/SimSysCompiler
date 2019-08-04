//
// Created by a_mod on 18.01.2019.
//

#include <stdexcept>
#include "grammar.h"
#include <Parser/Production.h>

std::string ACC::data::symbolToString(::ACC::Symbol s) {
    switch (s) {
        case Symbol::empty:
            return "-1";
        case Symbol::VAR:
            return "var";
        case Symbol::ID:
            return "id";
        case Symbol::OPEN_BRACKET:
            return "open_bracket";
        case Symbol::CLOSED_BRACKET:
            return "closed_bracket";
        case Symbol::SYSCALL:
            return "syscall";
        case Symbol::LITERAL:
            return "data";
        case Symbol::EOS:
            return "end_of_statement";
        case Symbol::expr:
            return "expr";
        case Symbol::stmt:
            return "stmt";
        case Symbol::start:
            return "start";
        case Symbol::for_construct:
            return "for_construct";
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
            return "CMP";
        case Symbol::NOT:
            return "not";
        case Symbol::ELIF:
            return "elif";
        case Symbol::if_construct:
            return "if_construct";
        case Symbol::ELSE:
            return "else";
        case Symbol::else_construct:
            return "else_construct";
        case Symbol::elseIf_construct:
            return "elseIf_construct";
        case Symbol::WHILE:
            return "WHILE";
        case Symbol::while_construct:
            return "while_construct";
        case Symbol::ARROW:
            return "ARROW";
        case Symbol::FOR:
            return "FOR";
        case Symbol::ptr_assign:
            return "ptr_assign";
        case Symbol::SALLOC:
            return "SALLOC";
        case Symbol::SLASH:
            return "SLASH";
        case Symbol::STAR:
            return "STAR";
        case Symbol::PLUS:
            return "PLUS";
        case Symbol::MINUS:
            return "SUBTRACT";
        case Symbol::MODULO:
            return "MODULO";
        case Symbol::TEXT:
            return "TEXT";
        case Symbol::IMPORT:
            return "IMPORT";
        case Symbol::DOUBLE_QUOTE:
            return "DOUBLE_QUOTE";
        case Symbol::QUOTE:
            return "QUOTE";
        case Symbol::DOT:
            return "DOT";
        case Symbol::OPEN_CURLY:
            return "OPEN_CURLY";
        case Symbol::CLOSED_CURLY:
            return "CLOSED_CURLY";
        case Symbol::type:
            return "type";
    }
    throw std::runtime_error("Symbol not known.");
}


