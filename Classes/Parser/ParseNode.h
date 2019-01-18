//
// Created by a_mod on 10.01.2019.
//

#ifndef SIMSYSCOMPILER_PARSENODE_H
#define SIMSYSCOMPILER_PARSENODE_H

#include <vector>
#include <Lexical/IToken.h>

namespace ACC {
    class ParseNode {
    public:
        std::vector<ParseNode*> children;
        bool isTerminal = false;
        IToken* token;
    };
}

#endif //SIMSYSCOMPILER_PARSENODE_H
