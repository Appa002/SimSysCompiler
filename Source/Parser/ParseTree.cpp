//
// Created by a_mod on 10.01.2019.
//

#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Tokens/BracketToken.h>
#include <iostream>
#include "ParseTree.h"
#include <errors.h>

ACC::ParseTree::ParseTree(const ACC::LexicalAnalysis &in) {
    generate(in);
}

ACC::ParseTree::ParseTree(const ACC::ParseTree &other) : refCount(other.refCount), root(other.root),
                                                         generated(other.generated){
    refCount++;
}

ACC::ParseNode *ACC::ParseTree::process(token_string input, Symbol prodSym) {
    auto iItr = input.begin();
    auto node = new ParseNode(prodSym);

    for (auto production : data::getGrammar()) {
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
                    node->children.push_back(new ParseNode((*iItr)->id, *iItr));
                    iItr++;
                } else {
                    killChildren(node);
                    iItr = old;
                    break;
                }
            } else {
                ++pItr;
                token_string subStr = createString(iItr, pItr, input);
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

void ACC::ParseTree::killChildren(ACC::ParseNode *node) {
    for (auto const &child : node->children)
        delete child;
    node->children.clear();
}

ACC::token_string
ACC::ParseTree::createString(token_string::iterator& inputItr, production::iterator& productionItr, token_string const& input){
    int depth = 0;
    token_string subStr;
    while (inputItr != input.end()) {
        if ((*inputItr)->id == Symbol::BRACKET &&
            static_cast<BracketToken *>(*inputItr)->kind == BracketKind::OPEN){
            depth++;
        }

        if ((*inputItr)->id == *productionItr && depth == 0)
            break;

        if ((*inputItr)->id == Symbol::BRACKET &&
            static_cast<BracketToken *>(*inputItr)->kind == BracketKind::CLOSED){
            depth--;
        }
        subStr.push_back(*inputItr);
        inputItr++;
    }
    return subStr;
}

const ACC::ParseNode *ACC::ParseTree::getRoot() {
    return root;
}

void ACC::ParseTree::generate(const ACC::LexicalAnalysis &in) {
    if(generated)
        throw repeated_step_error_t("The parse tree has already been generated.");
    generated = true;
    root = process(const_cast<LexicalAnalysis &>(in).data(), Symbol::expr);
}

ACC::ParseTree::~ParseTree() {
    refCount--;
    if(refCount > 0)
        return;

    delete root;
    root = nullptr;
}
