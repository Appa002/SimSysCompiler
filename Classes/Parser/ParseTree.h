//
// Created by a_mod on 10.01.2019.
//

#ifndef SIMSYSCOMPILER_PARSTREE_H
#define SIMSYSCOMPILER_PARSTREE_H

#include <Lexical/LexicalAnalysis.h>
#include "ParseNode.h"
#include <iostream>


namespace ACC {
    class ParseTree {
    private:
        void killChildren(ParseNode* node);
        ParseNode * process(token_string input, Symbol prodSym);

    public:
        explicit ParseTree(const LexicalAnalysis& in);
    };
}

#endif //SIMSYSCOMPILER_PARSTREE_H
