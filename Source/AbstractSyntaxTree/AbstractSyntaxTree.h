//
// Created by a_mod on 23.01.2019.
//

#ifndef SIMSYSCOMPILER_ABSTRACTSYNTAXTREE_H
#define SIMSYSCOMPILER_ABSTRACTSYNTAXTREE_H


#include <grammar.h>
#include <Parser/ParseTree.h>
#include "ASTNode.h"

namespace ACC {
    class AbstractSyntaxTree {
    public:
        ASTNode* root;
        explicit AbstractSyntaxTree(ParseTree parseTree);
    };
}

#endif //SIMSYSCOMPILER_ABSTRACTSYNTAXTREE_H
