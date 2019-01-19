//
// Created by a_mod on 10.01.2019.
//

#ifndef SIMSYSCOMPILER_PARSENODE_H
#define SIMSYSCOMPILER_PARSENODE_H

#include <vector>
#include <grammar.h>
#include <iostream>

namespace ACC {
    struct ParseNode{
        ParseNode();
        explicit ParseNode(Symbol s);
        ~ParseNode();

        void print(unsigned indent = 0) const;
        Symbol value;
        std::vector<ParseNode*> children;
    };
}

#endif //SIMSYSCOMPILER_PARSENODE_H
