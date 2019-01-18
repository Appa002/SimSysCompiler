//
// Created by a_mod on 10.01.2019.
//

#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Tokens/BracketToken.h>
#include <iostream>
#include "ParseTree.h"

ACC::ParseTree::ParseTree(const ACC::LexicalAnalysis &in) {
  //  process(const_cast<LexicalAnalysis&>(in));
}

ACC::TestNode * ACC::ParseTree::process(std::string input, char prodSym) {
    std::vector<assigment> grammar = interpretGrammar(grammarDef);
    auto iItr = input.begin();
    auto node = new TestNode(prodSym);

    for(auto const& production : grammar){
        if(production.first[0] != prodSym)
            continue;
        auto old = iItr;
        for(auto pItr = production.second.begin();; ++pItr){
            if(pItr == production.second.end()){
                if(iItr == input.end())
                    return node;
                iItr = old;
                break;
            }
            auto expected = *pItr;

            if(expected != '`'){
                if(expected == *iItr){
                    node->children.push_back(new TestNode(expected));
                    iItr++;
                }
                else{
                    killChildren(node);
                    iItr = old;
                    break;
                }
            }else{
                std::string sym;
                pItr++;
                while(*pItr != '`'){
                    sym += *pItr;
                    ++pItr;
                }

                ++pItr;
                int depth = 0;
                std::string subStr;
                while(iItr != input.end()){
                    if(*iItr == *pItr && depth == 0)
                        break;
                    if(*iItr == '(')
                        depth++;
                    else if (*iItr == ')')
                        depth--;
                    subStr += *iItr;
                    iItr++;
                }
                std::cout << subStr << std::endl;
                if(iItr == input.end() && *iItr != *pItr) {
                    iItr = old;
                    break;
                }
                TestNode* newNode = process(subStr, production.first[0]);
                if(newNode){
                    node->children.push_back(newNode);
                    pItr--;
                }
                else{
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

void ACC::ParseTree::interactive() {
    std::vector<assigment> grammar = interpretGrammar(grammarDef);
    auto root = process("(n-(n))", 'E');
    delete root;
}
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
}

void ACC::ParseTree::killChildren(ACC::TestNode *node) {
    for(auto const& child : node->children)
        delete child;
    node->children.clear();
}
