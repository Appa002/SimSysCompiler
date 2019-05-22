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
#include <errors.h>
#include <Lexical/Tokens/IndentToken.h>

size_t gap = 0;

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
        throw repeated_step_error_t("The parse tree has already been generated.");
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
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::start;

    size_t oldPos = pos;

    ParseNode *other;

    if (other = assignment(pos), other != nullptr) { // start -> assignment EOS
        bool b = [&]() {
            node->children.push_back(other);
            if (other = match(++pos, Symbol::EOS), other != nullptr)
                node->children.push_back(other);
            else {
                return false;
            }

            if (other = start(++pos), other != nullptr)
                node->children.push_back(other);
            else
                --pos;
            return true;
        }();

        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    if(other = ifConstruct(pos), other != nullptr){ // start -> ifConstruct [start]
        node->children.push_back(other);
        if (other = start(++pos), other != nullptr)
            node->children.push_back(other);
        else
            --pos;

        return node;
    }


    if (other = function(pos), other != nullptr) { // start -> function extent
        bool b = [&]() {
            node->children.push_back(other);
            if (other = match(++pos, Symbol::EXTENT), other != nullptr)
                node->children.push_back(other);
            else
                return false;

            if (other = start(++pos), other != nullptr)
                node->children.push_back(other);
            else
                --pos;
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    if (other = keyword(pos), other != nullptr) { // start -> keyword EOS
        bool b = [&]() {
            node->children.push_back(other);
            if (other = match(++pos, Symbol::EOS), other != nullptr)
                node->children.push_back(other);
            else
                return false;
            if (other = start(++pos), other != nullptr)
                node->children.push_back(other);
            else
                --pos;
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }

    }

    if (other = call(pos), other != nullptr) { // start -> call EOS
        bool b = [&]() {
            node->children.push_back(other);
            if (other = match(++pos, Symbol::EOS), other != nullptr)
                node->children.push_back(other);
            else
                return false;

            if (other = start(++pos), other != nullptr)
                node->children.push_back(other);
            else
                --pos;
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::assignment(size_t &pos) {
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::assignment;

    size_t oldPos = pos;


    ParseNode *other;
    if (other = match(pos, Symbol::VAR), other != nullptr) { // start -> assignment EOS
        bool b = [&]() {
            node->children.push_back(other);
            if (other = match(++pos, Symbol::DECL), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = match(++pos, Symbol::TYPE), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = match(++pos, Symbol::ASSIGN), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = expr(++pos), other == nullptr) {
                return false;
            }
            node->children.push_back(other);
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    if (other = match(++pos, Symbol::ID), other != nullptr) {
        bool b = [&]() {
            node->children.push_back(other);

            if (other = match(++pos, Symbol::ASSIGN), other == nullptr) {
                return false;
            }

            node->children.push_back(other);

            if (other = expr(++pos), other == nullptr) {
                return false;
            }
            node->children.push_back(other);
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::function(size_t &pos) {
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::function;

    size_t oldPos = pos;

    ParseNode *other;
    if (other = match(pos, Symbol::FUNCTION), other !=
                                              nullptr) { // function -> FUNCTION DECL BRACKET BRACKET TYPE COLON INDENT start
        bool b = [&]() {
            node->children.push_back(other);
            if (other = match(++pos, Symbol::DECL), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);


            if (other = paramDecl(++pos), other != nullptr) {
                node->children.push_back(other);
            } else
                pos--;

            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);


            if (other = match(++pos, Symbol::TYPE), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = match(++pos, Symbol::COLON), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = match(++pos, Symbol::INDENT), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = start(++pos), other == nullptr) {
                return false;
            }
            node->children.push_back(other);
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }
    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::keyword(size_t &pos) {
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::keyword;

    size_t oldPos = pos;
    ParseNode *other;

    if (other = match(pos, Symbol::EXIT), other != nullptr) { // keyword -> exit expr
        node->children.push_back(other);
        if (other = expr(++pos), other == nullptr) {
            killChildren(node);
            pos = oldPos;
        } else {
            node->children.push_back(other);
            return node;
        }
    }

    if (other = match(pos, Symbol::RETURN), other != nullptr) { // keyword -> return expr
        node->children.push_back(other);
        if (other = expr(++pos), other == nullptr) {
            killChildren(node);
            pos = oldPos;
        } else {
            node->children.push_back(other);
            return node;
        }
    }

    if (other = match(pos, Symbol::SYSCALL), other != nullptr) { // keyword -> syscall expr COMMA expr COMMA...
        bool b = [&]() {
            node->children.push_back(other);

            if (other = expr(++pos), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = match(++pos, Symbol::COMMA), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            for (size_t i = 0; i < 6; i++) {
                if (other = expr(++pos), other == nullptr) {
                    pos--;
                    break;
                }
                node->children.push_back(other);

                if (other = match(++pos, Symbol::COMMA), other == nullptr) {
                    pos--;
                    break;
                }
                node->children.push_back(other);
            }
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::call(size_t &pos) {
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::call;

    size_t oldPos = pos;
    ParseNode *other;

    if (other = match(pos, Symbol::ID), other != nullptr) { // call -> ID BRACKET [paramList] BRACKET
        bool b = [&]() {
            node->children.push_back(other);
            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = paramList(++pos), other != nullptr) {
                node->children.push_back(other);
            } else
                pos--;

            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::expr(size_t &pos) {
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::expr;

    size_t oldPos = pos;
    ParseNode *other;

    if (other = match(pos, Symbol::ID), other != nullptr) { // expr -> id BRACKET BRACKET
        bool b = [&]() {
            node->children.push_back(other);

            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);
            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    if (other = match(pos, Symbol::ID), other != nullptr) { // expr -> id BRACKET BRACKET expr
        bool b = [&]() {
            node->children.push_back(other);

            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);
            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = expr(++pos), other == nullptr) {
                return false;
            }
            node->children.push_back(other);
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    if (other = match(pos, Symbol::ID), other != nullptr) { // expr -> id BRACKET paramList BRACKET
        bool b = [&]() {
            node->children.push_back(other);

            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = paramDecl(++pos), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    if (other = match(pos, Symbol::ID), other != nullptr) { // expr -> id BRACKET paramList BRACKET expr
        bool b = [&]() {
            node->children.push_back(other);

            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = paramDecl(++pos), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = expr(++pos), other == nullptr) {
                return false;
            }
            node->children.push_back(other);
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }


    if (other = match(pos, Symbol::BRACKET), other != nullptr) { // expr -> BRACKET expr BRACKET expr
        bool b = [&]() {
            node->children.push_back(other);


            if (other = expr(++pos), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = match(++pos, Symbol::BRACKET), other == nullptr) {
                return false;
            }
            node->children.push_back(other);

            if (other = expr(++pos), other != nullptr) {
                node->children.push_back(other);
            } else
                pos--;
            return true;
        }();
        if (b)
            return node;
        else {
            killChildren(node);
            pos = oldPos;
        }
    }

    if (other = match(pos, Symbol::LITERAL), other != nullptr) { // expr -> LITERAL [expr]
        node->children.push_back(other);

        if (other = expr(++pos), other != nullptr) {
            node->children.push_back(other);
        } else
            --pos;
        return node;
    }


    if (other = match(pos, Symbol::ID), other != nullptr) { // expr -> ID expr
        node->children.push_back(other);

        if (other = expr(++pos), other != nullptr) {
            node->children.push_back(other);
        } else
            --pos;
        return node;
    }

    if (other = match(pos, Symbol::MATH_OPERATOR), other != nullptr) { // expr -> MATH_OPERATOR expr
        node->children.push_back(other);

        if (other = expr(++pos), other == nullptr) {
            killChildren(node);
            pos = oldPos;
        } else {
            node->children.push_back(other);
            return node;
        }
    }
    if (other = match(pos, Symbol::CMP), other != nullptr) { // expr -> CMP expr
        node->children.push_back(other);

        if (other = expr(++pos), other == nullptr) {
            killChildren(node);
            pos = oldPos;
        } else {
            node->children.push_back(other);
            return node;
        }
    }
    if (other = match(pos, Symbol::NOT), other != nullptr) { // expr -> NOT expr
        node->children.push_back(other);

        if (other = expr(++pos), other == nullptr) {
            killChildren(node);
            pos = oldPos;
        } else {
            node->children.push_back(other);
            return node;
        }
    }

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::paramDecl(size_t &pos) {
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::paramsDecl;

    size_t oldPos = pos;
    ParseNode *other;

    if (other = match(pos, Symbol::DECL), other != nullptr) {
        node->children.push_back(other);

        if (other = match(++pos, Symbol::TYPE), other == nullptr) {
            killChildren(node);
            pos = oldPos;
        } else {
            node->children.push_back(other);

            if (other = match(++pos, Symbol::COMMA), other != nullptr)
                node->children.push_back(other);
            else
                pos--;

            if (other = paramDecl(++pos), other != nullptr)
                node->children.push_back(other);
            else
                pos--;
            return node;
        }
    }

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::paramList(size_t &pos) {
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::paramsList;

    size_t oldPos = pos;
    ParseNode *other;


    if (other = expr(pos), other != nullptr) {
        node->children.push_back(other);


        if (other = match(++pos, Symbol::COMMA), other != nullptr)
            node->children.push_back(other);
        else
            pos--;

        if (other = paramList(++pos), other != nullptr)
            node->children.push_back(other);
        else
            pos--;
        return node;
    }

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::ifConstruct(size_t &pos) {
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::if_construct;

    size_t oldPos = pos;
    ParseNode *other;

    if(other = match(pos, Symbol::IF), other != nullptr){ // ifConstruct -> IF expr COLON INDENT start EXTENT [elifConstruct] [elseConstruct]
        node->children.push_back(other);
        bool b = [&](){
            if (other = expr(++pos), other == nullptr)
                return false;
            node->children.push_back(other);


            if (other = match(++pos, Symbol::COLON), other == nullptr)
                return false;
            node->children.push_back(other);

            if (other = match(++pos, Symbol::INDENT), other == nullptr)
                return false;
            node->children.push_back(other);

            if (other = start(++pos), other == nullptr)
                return false;
            node->children.push_back(other);

            if (other = match(++pos, Symbol::EXTENT), other == nullptr)
                return false;
            node->children.push_back(other);

            if(other = elifConstruct(++pos), other != nullptr)
                node->children.push_back(other);
            else
                --pos;

            if(other = elseConstruct(++pos), other != nullptr)
                node->children.push_back(other);
            else
                --pos;

            return true;
        }();
        if (b)
            return node;
        else{
            killChildren(node);
            pos = oldPos;
        }
    }

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::elifConstruct(size_t &pos) {
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::elseIf_construct;

    size_t oldPos = pos;
    ParseNode *other;

    if(other = match(pos, Symbol::ELIF), other != nullptr){ // elifConstruct -> ELIF expr COLON INDENT start EXTENT [elifConstruct]
        node->children.push_back(other);
        bool b = [&](){
            if (other = expr(++pos), other == nullptr)
                return false;
            node->children.push_back(other);

            if (other = match(++pos, Symbol::COLON), other == nullptr)
                return false;
            node->children.push_back(other);

            if (other = match(++pos, Symbol::INDENT), other == nullptr)
                return false;
            node->children.push_back(other);

            if (other = start(++pos), other == nullptr)
                return false;
            node->children.push_back(other);

            if (other = match(++pos, Symbol::EXTENT), other == nullptr)
                return false;
            node->children.push_back(other);

            if(other = elifConstruct(++pos), other != nullptr)
                node->children.push_back(other);
            else
                --pos;

            return true;
        }();
        if (b)
            return node;
        else{
            killChildren(node);
            pos = oldPos;
        }
    }

    pos = oldPos;
    delete node;
    return nullptr;
}

ACC::ParseNode *ACC::ParseTree::elseConstruct(size_t &pos) {
    ParseNode *node = new ParseNode;
    node->symbol = Symbol::else_construct;

    size_t oldPos = pos;
    ParseNode *other;

    if(other = match(pos, Symbol::ELSE), other != nullptr){ // else_construct -> ELSE INDENT start EXTENT
        node->children.push_back(other);
        bool b = [&](){
            if (other = match(++pos, Symbol::INDENT), other == nullptr)
                return false;
            node->children.push_back(other);

            if (other = start(++pos), other == nullptr)
                return false;
            node->children.push_back(other);

            if (other = match(++pos, Symbol::EXTENT), other == nullptr)
                return false;
            node->children.push_back(other);


            return true;
        }();
        if (b)
            return node;
        else{
            killChildren(node);
            pos = oldPos;
        }
    }

    pos = oldPos;
    delete node;
    return nullptr;

}


