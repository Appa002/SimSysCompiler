//
// Created by a_mod on 10.01.2019.
//

#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Tokens/BracketToken.h>
#include <iostream>
#include "ParseTree.h"

ACC::ParseTree::ParseTree(const ACC::LexicalAnalysis &in) {
    auto root = process(const_cast<LexicalAnalysis &>(in).data(), Symbol::expr);
    root->print();
    delete root;
}

ACC::ParseNode *ACC::ParseTree::process(token_string input, Symbol prodSym) {
    auto iItr = input.begin();
    auto node = new ParseNode(prodSym);

    for (auto const &production : data::getGrammar()) {
        if (production.first != prodSym)
            continue;
        auto old = iItr;
        for (auto pItr = production.second.begin();; ++pItr) {
            if (pItr == production.second.end()) {
                if (iItr == input.end())
                    return node;
                iItr = old;
                killChildren(node);
                break;
            }
            auto expected = *pItr;

            if (!isNoneterminal(expected)) {
                if (expected == (*iItr)->id) {
                    node->children.push_back(new ParseNode(expected));
                    iItr++;
                } else {
                    killChildren(node);
                    iItr = old;
                    break;
                }
            } else {
                ++pItr;
                int depth = 0;
                token_string subStr;
                while (iItr != input.end()) {
                    /*  if(pItr == production.second.end()){
                          subStr.push_back(*iItr);
                          break;
                      }*/
                    if ((*iItr)->id == *pItr && depth == 0)
                        break;
                    if ((*iItr)->id == Symbol::BRACKET &&
                        static_cast<BracketToken *>(*iItr)->kind == BracketKind::OPEN)
                        depth++;
                    if ((*iItr)->id == Symbol::BRACKET &&
                        static_cast<BracketToken *>(*iItr)->kind == BracketKind::CLOSED)
                        depth--;
                    subStr.push_back(*iItr);
                    iItr++;
                }

                if (iItr == input.end() && pItr != production.second.end()) {
                    iItr = old;
                    break;
                }
                ParseNode *newNode = process(subStr, production.first);
                if (newNode) {
                    node->children.push_back(newNode);
                    pItr--;
                } else {
                    killChildren(node);
                    iItr = old;
                    break;
                }
            }
        }
    }
    delete node;
    return nullptr;
}

/*
std::vector<ACC::ParseTree::assigment> ACC::ParseTree::interpretGrammar(std::string in) {
    std::vector<std::string> exprs;
    std::string cur;
    for(auto itr = in.begin(); itr != in.end(); itr++){
        auto c = *itr;
        if(c == ';'){
            exprs.push_back(cur);
            cur = "";
            continue;
        }else if (c == '\n' || c=='\r' || (itr+1 != in.end() && c == ' ' && *(itr + 1) == ' '))
            continue;
        cur += c;
    }
    for (auto& expr : exprs){
        if(expr[0] == ' '){
            expr.erase(0, 1);
        }
    }

    std::vector<assigment> out;
    for(auto const& expr : exprs){
        std::string lhs, rhs;
        split(expr, lhs, rhs);
        out.push_back(assigment({lhs, rhs}));
    }

    return out;
}

void ACC::ParseTree::split(const std::string &input, std::string &lhs, std::string &rhs) {
    bool seen = false;
    for(auto itr = input.begin(); itr != input.end(); itr++){
        if(seen)
            rhs += *itr;
        else
            lhs += *itr;
        if(*(itr+2) == '>'){
            seen = true;
            itr+=3;
        }
    }
}*/

void ACC::ParseTree::killChildren(ACC::ParseNode *node) {
    for (auto const &child : node->children)
        delete child;
    node->children.clear();
}
