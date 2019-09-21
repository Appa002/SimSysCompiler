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
        case Symbol::__debug_escape_sequence:
            return "__debug_escape_sequence";
        case Symbol::type_decl:
            return "type_decl";
        case Symbol::type_decl_body:
            return "type_decl_body";
        case Symbol::TRAIT:
            return "TRAIT";
        case Symbol::trait:
            return "trait";
        case Symbol::initializer_list:
            return  "initializer_list";
        case Symbol::AND:
            return "AND";
        case Symbol::OR:
            return "OR";
        case Symbol::TRUE:
            return "TRUE";
        case Symbol::FALSE:
            return "FALSE";
    }
    throw std::runtime_error("Symbol not known.");
}

std::string ACC::data::symbolToStringForErrReporting(ACC::Symbol s) {
    switch (s) {
        case Symbol::empty:
            return "-1";
        case Symbol::VAR:
            return "var";
        case Symbol::ID:
            return "id";
        case Symbol::OPEN_BRACKET:
            return "(";
        case Symbol::CLOSED_BRACKET:
            return ")";
        case Symbol::SYSCALL:
            return "syscall";
        case Symbol::LITERAL:
            return "data";
        case Symbol::EOS:
            return ";";
        case Symbol::expr:
            return "an expr";
        case Symbol::stmt:
            return "an stmt";
        case Symbol::start:
            return "a block";
        case Symbol::for_construct:
            return "parts of for loop";
        case Symbol::assignment:
            return "=";
        case Symbol::keyword:
            return "keyword";
        case Symbol::DECL:
            return "decl";
        case Symbol::ASSIGN:
            return "=";
        case Symbol::EXIT:
            return "exit";
        case Symbol::INDENT:
            return "a block start";
        case Symbol::EXTENT:
            return "a block end";
        case Symbol::FUNCTION:
            return "fn";
        case Symbol::COLON:
            return ":";
        case Symbol::COMMA:
            return ",";
        case Symbol::function:
            return "a function";
        case Symbol::paramsDecl:
            return "a declaration list";
        case Symbol::paramsList:
            return "a parameter list";
        case Symbol::call:
            return "a function call";
        case Symbol::RETURN:
            return "return";
        case Symbol::TYPE:
            return "type";
        case Symbol::IF:
            return "if";
        case Symbol::ifStmt:
            return "parts of if";
        case Symbol::CMP:
            return "a comparison expression";
        case Symbol::NOT:
            return "!";
        case Symbol::ELIF:
            return "elif";
        case Symbol::if_construct:
            return "parts of if";
        case Symbol::ELSE:
            return "else";
        case Symbol::else_construct:
            return "parts of else";
        case Symbol::elseIf_construct:
            return "parts of elif";
        case Symbol::WHILE:
            return "while";
        case Symbol::while_construct:
            return "parts of while loop";
        case Symbol::ARROW:
            return "->";
        case Symbol::FOR:
            return "for";
        case Symbol::ptr_assign:
            return "an assignment to pointer";
        case Symbol::SALLOC:
            return "salloc";
        case Symbol::SLASH:
            return "/";
        case Symbol::STAR:
            return "*";
        case Symbol::PLUS:
            return "+";
        case Symbol::MINUS:
            return "-";
        case Symbol::MODULO:
            return "%";
        case Symbol::TEXT:
            return "a identifier or string";
        case Symbol::IMPORT:
            return "import";
        case Symbol::DOUBLE_QUOTE:
            return "\"";
        case Symbol::QUOTE:
            return "'";
        case Symbol::DOT:
            return ".";
        case Symbol::OPEN_CURLY:
            return "{";
        case Symbol::CLOSED_CURLY:
            return "}";
        case Symbol::type:
            return "a type definition";
        case Symbol::__debug_escape_sequence:
            return "a escape sequence";
        case Symbol::type_decl:
            return "type_decl";
        case Symbol::type_decl_body:
            return "type_decl_body";
        case Symbol::TRAIT:
            return "trait";
        case Symbol::trait:
            return "a member function definition";
        case Symbol::initializer_list:
            return "an expression list";
        case Symbol::AND:
            return "&&";
        case Symbol::OR:
            return "||";
        case Symbol::TRUE:
            return "true";
        case Symbol::FALSE:
            return "false";
    }
    throw std::runtime_error("Symbol not known.");
}


