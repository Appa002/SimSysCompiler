//
// Created by a_mod on 10.01.2019.
//

#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Tokens/BracketToken.h>
#include <iostream>
#include "ParseTree.h"
#include "Production.h"
#include <Logger/Logger.h>
#include <errors.h>

size_t gap = 0;

ACC::ParseTree::ParseTree(const ACC::LexicalAnalysis &in) {
    generate(in);
}

ACC::ParseTree::ParseTree(const ACC::ParseTree &other) : refCount(other.refCount), root(other.root),
                                                         generated(other.generated){
    refCount++;
}

ACC::ParseNode *ACC::ParseTree::process(token_string input, Symbol prodHead) {
    auto iItr = input.begin();
    auto node = new ParseNode(prodHead);
    gap += 4;

    for (auto production : data::getGrammar()) {
        if (production.head != prodHead)
            continue;
        LOG() <<  Log::Colour::Blue << std::string(gap, ' ') << "Selected: " << data::symbolToString(production.head) << std::endl;
        auto old = iItr;
        for (auto pItr = production.body.begin();; ++pItr) {
            if (pItr == production.body.end()) {
                if (iItr == input.end()){
                    gap -= 4;
                    return node;
                }
                LOG() << std::string(gap, ' ') <<"-----" << std::endl;
                LOG() << std::string(gap, ' ') <<"Symbol: " << (*iItr)->getIdentifier() << std::endl;
                LOG() << std::string(gap, ' ') <<"Input: " << input.createStdString() << std::endl;
                LOG() << std::string(gap, ' ') <<"Production: " << data::productionToString(production) << std::endl;
                LOG() << Log::Colour::Magenta << std::string(gap, ' ') <<"  --- FAILED -- (reached end of production without reaching end of input)" << std::endl;
                iItr = old;
                killChildren(node);
                break;
            }
            auto expected = *pItr;

            if (!isNoneterminal(expected)) {
                if(iItr == input.end()){
                    LOG() << std::string(gap, ' ') << "Reached end of input whilst matching" << std::endl;
                    killChildren(node);
                    iItr = old;
                }
                if (expected == (*iItr)->id) {
                    node->children.push_back(new ParseNode((*iItr)->id, *iItr));
                    LOG() << std::string(gap, ' ') << "Matched terminal: " << (*iItr)->getIdentifier() << std::endl;
                    iItr++;
                } else {
                    killChildren(node);
                    iItr = old;
                    LOG() << std::string(gap, ' ') << "-----" << std::endl;
                    LOG() << std::string(gap, ' ') << "Terminal: " << (*iItr)->getIdentifier() << std::endl;
                    LOG() << std::string(gap, ' ') << "Input: " << input.createStdString() << std::endl;
                    LOG() << std::string(gap, ' ') << "Production: " << data::productionToString(production) << std::endl;
                    LOG() << Log::Colour::Magenta << std::string(gap, ' ') << "  --- FAILED -- (noneterminal wasn't the same in the production and the input)" << std::endl;
                    break;
                }
            } else {
                auto terminal = *pItr;
                LOG() << std::string(gap, ' ') << "Noneterminal in production: " << data::symbolToString(terminal) << std::endl;
                ++pItr;


                if (iItr == input.end() && pItr != production.body.end()) {
                    iItr = old;
                    LOG() << std::string(gap, ' ') << "-----" << std::endl;
                    LOG() << std::string(gap, ' ') << "Production: " << data::productionToString(production) << std::endl;
                    LOG() << Log::Colour::Magenta << std::string(gap, ' ') << "  --- FAILED -- (reached end of input while not reaching the end of production.)" << std::endl;
                    break;
                }


                token_string subStr = createString(iItr, pItr, input, production.body);

                LOG() << std::string(gap, ' ') << "Production: " << data::productionToString(production) << std::endl;
                LOG() << std::string(gap, ' ') << "Substring: " << subStr.createStdString() << std::endl;

                ParseNode *newNode = process(subStr, terminal);
                if (newNode) {
                    node->children.push_back(newNode);
                    pItr--;
                } else {
                    killChildren(node);
                    iItr = old;
                    LOG() << Log::Colour::Magenta << std::string(gap, ' ') << "  --- FAILED -- (couldn't satisfy terminal; see above)" << std::endl;
                    break;
                }
            }
        }
    }
    LOG() << Log::Colour::Magenta << std::string(gap, ' ') << "  :-: Couldn't satisfy overall expression: " << input.createStdString() << std::endl;
    delete node;
    gap -= 4;
    return nullptr;
}

void ACC::ParseTree::killChildren(ACC::ParseNode *node) {
    for (auto const &child : node->children)
        delete child;
    node->children.clear();
}

ACC::token_string
ACC::ParseTree::createString(token_string::iterator &inputItr, productionBody_t::iterator &productionItr,
                             token_string const &input, productionBody_t const &production) {
    int depth = 0;
    token_string subStr;
    while (inputItr != input.end()) {
        if ((*inputItr)->id == Symbol::BRACKET &&
                dynamic_cast<BracketToken *>(*inputItr)->kind == BracketKind::OPEN){
            depth++;
        }

        if (productionItr != production.end() && (*inputItr)->id == *productionItr && depth == 0)
            break;

        if ((*inputItr)->id == Symbol::BRACKET &&
                dynamic_cast<BracketToken *>(*inputItr)->kind == BracketKind::CLOSED){
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
    LOG.createHeading("Generating Parse Tree...");
    root = process(const_cast<LexicalAnalysis &>(in).data(), Symbol::start);
}

ACC::ParseTree::~ParseTree() {
    refCount--;
    if(refCount > 0)
        return;

    delete root;
    root = nullptr;
}
