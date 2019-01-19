//
// Created by a_mod on 10.01.2019.
//

#ifndef SIMSYSCOMPILER_PARSENODE_H
#define SIMSYSCOMPILER_PARSENODE_H

#include <vector>
#include <grammar.h>
#include <iostream>
#include <Lexical/IToken.h>

namespace ACC {
    struct ParseNode{
        ParseNode();
        explicit ParseNode(Symbol s);
        ParseNode(Symbol s, IToken* t);
        ~ParseNode();

        void print(unsigned indent = 0) const;
        Symbol value;
        IToken* token = nullptr;
        std::vector<ParseNode*> children;
    };
}

#endif //SIMSYSCOMPILER_PARSENODE_H
