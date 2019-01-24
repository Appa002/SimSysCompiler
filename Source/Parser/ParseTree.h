//
// Created by a_mod on 10.01.2019.
//

#pragma once

#include <Lexical/LexicalAnalysis.h>
#include "ParseNode.h"
#include <iostream>


namespace ACC {
    class ParseTree {
    private:
        void killChildren(ParseNode* node);
        token_string createString(token_string::iterator& inputItr, production::iterator& productionItr,
                token_string const& input);

        ParseNode * process(token_string input, Symbol prodSym);

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
