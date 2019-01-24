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
    private:
        void _print(std::string indent = "", bool isLast = false) const;

    public:
        ParseNode();
        explicit ParseNode(Symbol s);
        ParseNode(Symbol s, IToken* t);
        ~ParseNode();
        void print() const;

        Symbol symbol;
        IToken* token = nullptr;
        std::vector<ParseNode*> children;
    };
}

#endif //SIMSYSCOMPILER_PARSENODE_H
