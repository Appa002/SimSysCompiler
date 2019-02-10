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
    private:
        ASTNode* root;
        int refCount = 0;
    public:
        explicit AbstractSyntaxTree(ParseTree parseTree);
        AbstractSyntaxTree(const AbstractSyntaxTree& other);
        ~AbstractSyntaxTree();
        void print();
        ASTNode* getRoot() const;
    };
}

#endif //SIMSYSCOMPILER_ABSTRACTSYNTAXTREE_H
