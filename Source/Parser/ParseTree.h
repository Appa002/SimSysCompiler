//
// Created by a_mod on 10.01.2019.
//

#pragma once

#include <Lexical/LexicalAnalysis.h>
#include "ParseNode.h"
#include "Production.h"


namespace ACC {
    class ParseTree {
    private:
        void killChildren(ParseNode* node);
        ACC::token_string createString(token_string::iterator &inputItr, productionBody_t::iterator &productionItr,
                                               token_string const &input, productionBody_t const &production);

        ParseNode * process(token_string input, Symbol prodHead);

        ParseNode * root = nullptr;
        int refCount = 1;
        bool generated = false;
    public:
        ParseTree() = default;
        explicit ParseTree(const LexicalAnalysis& in);
        ParseTree(ParseTree const & other);
        ~ParseTree();

        ParseNode const* getRoot();
        void generate(const LexicalAnalysis& in);
    };
}
