#include <utility>

//
// Created by a_mod on 10.01.2019.
//

#include <exception>
#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Tokens/BracketToken.h>
#include <iostream>
#include "ParseTree.h"
#include "Production.h"
#include <Logger/Logger.h>
#include <Lexical/Tokens/IndentToken.h>
#include <Logger/LogableProduction.h>

#define START_PRODUCTION() \
    logable.echoProduction(); \
    { \
    bool b = [&]() {

#define END_PRODUCTION() \
    return true; \
    }(); \
    if (b){ \
         pos--;\
        return node; \
    }\
    else { \
        killChildren(node); \
        pos = oldPos;\
    }\
    }

#define NONE_TERMINAL(name) \
    if (other = name(pos), other == nullptr) { \
        logable.red(); \
        return false; \
    } \
    pos++; \
    node->children.push_back(other); \
    logable.green();

#define TERMINAL(name) \
    if (other = match(pos, Symbol::name), other == nullptr) { \
        logable.red(); \
        return false; \
    } \
    pos++; \
    node->children.push_back(other); \
    logable.green();

#define OPTIONAL_NONE_TERMINAL(name) \
    if (other = name(pos), other != nullptr){\
        node->children.push_back(other);\
        logable.green(); \
        pos++;\
    } \
    else {\
        logable.blue();\
    }\

#define OPTIONAL_TERMINAL(name) \
    if (other = match(pos, Symbol::name), other != nullptr){\
        node->children.push_back(other);\
        logable.green(); \
        pos++;\
    } \
    else {\
        logable.blue();\
    }\


ACC::ParseTree::ParseTree(const ACC::LexicalAnalysis &in) {
    generate(in);
}

ACC::ParseTree::ParseTree(const ACC::ParseTree &other) : refCount(other.refCount), root(other.root),
                                                         generated(other.generated) {
    refCount++;
}

void ACC::ParseTree::killChildren(ACC::ParseNode *node) {
    for (auto const &child : node->children)
        delete child;
    node->children.clear();
}

const ACC::ParseNode *ACC::ParseTree::getRoot() {
    return root;
}

void ACC::ParseTree::generate(ACC::LexicalAnalysis in) {
    if (generated)
        throw std::runtime_error("The parse tree has already been generated.");
    generated = true;
    LOG.createHeading("Generating Parse Tree...");
    //  root = process(const_cast<LexicalAnalysis &>(in).data(), Symbol::start);
    document = in.data();
    size_t pos = 0;
    root = start(pos);
}

ACC::ParseTree::~ParseTree() {
    refCount--;
    if (refCount > 0)
        return;

    delete root;
    root = nullptr;
}

ACC::ParseNode *ACC::ParseTree::match(size_t &pos, ACC::Symbol what) {
    if (pos >= document.size())
        return nullptr;

    if (document[pos]->id == what)
        return new ParseNode(document[pos]->id, document[pos]);
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::start(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [start]...\n";
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::start;

    size_t oldPos = pos;

    ParseNode *other;

    logable.loadProduction(Symbol::start, {Symbol::assignment, Symbol::EOS, Symbol::start});
    START_PRODUCTION()

        NONE_TERMINAL(assignment)
        TERMINAL(EOS)
        OPTIONAL_NONE_TERMINAL(start);

    END_PRODUCTION()


    logable.loadProduction(Symbol::start, {Symbol::if_construct, Symbol::start});
    START_PRODUCTION()
            NONE_TERMINAL(ifConstruct)
            OPTIONAL_NONE_TERMINAL(start);

    END_PRODUCTION()

    logable.loadProduction(Symbol::start, {Symbol::function, Symbol::EXTENT, Symbol::start});
    START_PRODUCTION()

            NONE_TERMINAL(function)
            TERMINAL(EXTENT)
            OPTIONAL_NONE_TERMINAL(start);

    END_PRODUCTION()

    logable.loadProduction(Symbol::start, {Symbol::keyword, Symbol::EOS, Symbol::start});
    START_PRODUCTION()

            NONE_TERMINAL(keyword)
            TERMINAL(EOS)
            OPTIONAL_NONE_TERMINAL(start);

    END_PRODUCTION()

    logable.loadProduction(Symbol::start, {Symbol::call, Symbol::EOS, Symbol::start});
    START_PRODUCTION()

            NONE_TERMINAL(call)
            TERMINAL(EOS)
            OPTIONAL_NONE_TERMINAL(start);

    END_PRODUCTION()

    logable.loadProduction(Symbol::start, {Symbol::while_construct, Symbol::start});
    START_PRODUCTION()

            NONE_TERMINAL(whileConstruct)
            OPTIONAL_NONE_TERMINAL(start);

    END_PRODUCTION()

    logable.loadProduction(Symbol::start, {Symbol::for_construct, Symbol::start});
    START_PRODUCTION()

            NONE_TERMINAL(forConstruct)
            OPTIONAL_NONE_TERMINAL(start);

    END_PRODUCTION()

    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::assignment(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [assignment]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::assignment;
    ParseNode *other;

    size_t oldPos = pos;

    logable.loadProduction(Symbol::assignment, {Symbol::VAR, Symbol::DECL, Symbol::TYPE, Symbol::ASSIGN, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(VAR)
            TERMINAL(DECL)
            TERMINAL(TYPE)
            TERMINAL(ASSIGN)
            NONE_TERMINAL(expr)
    END_PRODUCTION()

    logable.loadProduction(Symbol::assignment, {Symbol::ID, Symbol::ASSIGN, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(ID)
            TERMINAL(ASSIGN)
            NONE_TERMINAL(expr)
    END_PRODUCTION()


    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::function(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [function]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::function;

    size_t oldPos = pos;

    ParseNode *other;

    logable.loadProduction(Symbol::function, {Symbol::FUNCTION, Symbol::DECL, Symbol::BRACKET, Symbol::paramsDecl,
                                              Symbol::BRACKET, Symbol::TYPE, Symbol::COLON, Symbol::INDENT, Symbol::start});
    START_PRODUCTION()
            TERMINAL(FUNCTION)
            TERMINAL(DECL)
            TERMINAL(BRACKET)
            OPTIONAL_NONE_TERMINAL(paramDecl)
            TERMINAL(BRACKET)
            TERMINAL(TYPE)
            TERMINAL(COLON)
            TERMINAL(INDENT)
            NONE_TERMINAL(start)
    END_PRODUCTION()

    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::keyword(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [keyword]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::keyword;

    size_t oldPos = pos;
    ParseNode *other;

    logable.loadProduction(Symbol::keyword, {Symbol::EXIT, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(EXIT)
            NONE_TERMINAL(expr)
    END_PRODUCTION()


    logable.loadProduction(Symbol::keyword, {Symbol::RETURN, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(RETURN)
            NONE_TERMINAL(expr)
    END_PRODUCTION()

    logable.loadProduction(Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA});
    START_PRODUCTION()
            std::vector<Symbol> vec = {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA};
            TERMINAL(SYSCALL)
            NONE_TERMINAL(expr)
            OPTIONAL_TERMINAL(COMMA)

            for(size_t i = 0; i < 6; i++){
                vec.push_back(Symbol::expr);
                vec.push_back(Symbol::COMMA);
                logable.changeProduction(Symbol::keyword, vec);
                OPTIONAL_NONE_TERMINAL(expr)
                OPTIONAL_TERMINAL(COMMA)
            }

    END_PRODUCTION()

    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::call(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [call]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::call;

    size_t oldPos = pos;
    ParseNode *other;

    logable.loadProduction(Symbol::call, {Symbol::ID, Symbol::BRACKET, Symbol::paramsList,Symbol::BRACKET});
    START_PRODUCTION()
            TERMINAL(ID)
            TERMINAL(BRACKET)
            OPTIONAL_NONE_TERMINAL(paramList)
            TERMINAL(BRACKET)
    END_PRODUCTION()

    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::expr(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [expr]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::expr;

    size_t oldPos = pos;
    ParseNode *other;

    logable.loadProduction(Symbol::expr, {Symbol::ID, Symbol::BRACKET, Symbol::BRACKET, Symbol::expr});
    START_PRODUCTION()
        TERMINAL(ID)
        TERMINAL(BRACKET)
        TERMINAL(BRACKET)
        OPTIONAL_NONE_TERMINAL(expr)
    END_PRODUCTION()

    logable.loadProduction(Symbol::expr, {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(ID)
            TERMINAL(BRACKET)
            NONE_TERMINAL(paramList)
            TERMINAL(BRACKET)
            OPTIONAL_NONE_TERMINAL(expr)
    END_PRODUCTION()

    logable.loadProduction(Symbol::expr, {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(BRACKET)
            NONE_TERMINAL(expr)
            TERMINAL(BRACKET)
            OPTIONAL_NONE_TERMINAL(expr)
    END_PRODUCTION()

    logable.loadProduction(Symbol::expr, {Symbol::LITERAL, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(LITERAL)
            OPTIONAL_NONE_TERMINAL(expr)
    END_PRODUCTION()


    logable.loadProduction(Symbol::expr, {Symbol::ID, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(ID)
            OPTIONAL_NONE_TERMINAL(expr)
    END_PRODUCTION()


    logable.loadProduction(Symbol::expr, {Symbol::MATH_OPERATOR, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(MATH_OPERATOR)
            NONE_TERMINAL(expr)
    END_PRODUCTION()

    logable.loadProduction(Symbol::expr, {Symbol::CMP, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(CMP)
            NONE_TERMINAL(expr)
    END_PRODUCTION()

    logable.loadProduction(Symbol::expr, {Symbol::NOT, Symbol::expr});
    START_PRODUCTION()
            TERMINAL(NOT)
            NONE_TERMINAL(expr)
    END_PRODUCTION()


    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::paramDecl(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [paramsDecl]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::paramsDecl;

    size_t oldPos = pos;
    ParseNode *other;

    logable.loadProduction(Symbol::paramsDecl, {Symbol::DECL, Symbol::TYPE, Symbol::COMMA, Symbol::paramsDecl});
    START_PRODUCTION()
            TERMINAL(DECL)
            TERMINAL(TYPE)
            OPTIONAL_TERMINAL(COMMA)
            OPTIONAL_NONE_TERMINAL(paramDecl)
    END_PRODUCTION()


    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::paramList(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [paramsList]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::paramsList;

    size_t oldPos = pos;
    ParseNode *other;

    logable.loadProduction(Symbol::paramsList, {Symbol::expr, Symbol::COMMA, Symbol::paramsList});
    START_PRODUCTION()
            NONE_TERMINAL(expr)
            OPTIONAL_TERMINAL(COMMA)
            OPTIONAL_NONE_TERMINAL(paramList)
    END_PRODUCTION()


    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::ifConstruct(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [if_construct]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::if_construct;

    size_t oldPos = pos;
    ParseNode *other;

    logable.loadProduction(Symbol::if_construct, {Symbol::IF, Symbol::expr, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT,
                                                  Symbol::elseIf_construct, Symbol::else_construct});
    START_PRODUCTION()
            TERMINAL(IF)
            NONE_TERMINAL(expr)
            TERMINAL(COLON)
            TERMINAL(INDENT)
            NONE_TERMINAL(start)
            TERMINAL(EXTENT)
            OPTIONAL_NONE_TERMINAL(elifConstruct)
            OPTIONAL_NONE_TERMINAL(elseConstruct)
    END_PRODUCTION()

    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::elifConstruct(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [elif_construct]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::elseIf_construct;

    size_t oldPos = pos;
    ParseNode *other;

    logable.loadProduction(Symbol::elseIf_construct, {Symbol::ELIF, Symbol::expr, Symbol::COLON,Symbol::INDENT,Symbol::start,
                                                      Symbol::EXTENT,Symbol::elseIf_construct});
    START_PRODUCTION()
            TERMINAL(ELIF)
            NONE_TERMINAL(expr)
            TERMINAL(COLON)
            TERMINAL(INDENT)
            NONE_TERMINAL(start)
            TERMINAL(EXTENT)
            OPTIONAL_NONE_TERMINAL(elifConstruct)
    END_PRODUCTION()


    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::elseConstruct(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [else_construct]...\n";
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::else_construct;

    size_t oldPos = pos;
    ParseNode *other;

    logable.loadProduction(Symbol::else_construct, {Symbol::ELSE, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT});
    START_PRODUCTION()
            TERMINAL(ELSE)
            TERMINAL(COLON)
            TERMINAL(INDENT)
            NONE_TERMINAL(start)
            TERMINAL(EXTENT)
    END_PRODUCTION()

    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;

}

ACC::ParseNode *ACC::ParseTree::whileConstruct(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [while_construct]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::while_construct;

    size_t oldPos = pos;
    ParseNode *other;

    logable.loadProduction(Symbol::while_construct, {Symbol::WHILE, Symbol::expr, Symbol::COLON, Symbol::INDENT,
                                                     Symbol::start, Symbol::EXTENT});
    START_PRODUCTION()
            TERMINAL(WHILE)
            NONE_TERMINAL(expr)
            TERMINAL(COLON)
            TERMINAL(INDENT)
            NONE_TERMINAL(start)
            TERMINAL(EXTENT)
    END_PRODUCTION()

    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::forConstruct(size_t &pos) {
    ACC::LogableProduction logable;
    LOG() << "\n";
    LOG() << Log::Colour::Magenta << "Entering [for_construct]...\n";

    ParseNode *node = new ParseNode;
    node->symbol = Symbol::for_construct;

    size_t oldPos = pos;
    ParseNode *other;

    logable.loadProduction(Symbol::for_construct, {Symbol::FOR, Symbol::ID, Symbol::GOES_TO, Symbol::expr, Symbol::COLON,
                                                   Symbol::INDENT, Symbol::start, Symbol::EXTENT});
    START_PRODUCTION()
            TERMINAL(FOR)
            TERMINAL(ID)
            TERMINAL(GOES_TO)
            NONE_TERMINAL(expr)
            TERMINAL(COLON)
            TERMINAL(INDENT)
            NONE_TERMINAL(start)
            TERMINAL(EXTENT)
    END_PRODUCTION()

    LOG() << Log::Colour::Magenta << "..done\n";

    pos = oldPos;
    delete node;
    return nullptr;
}


