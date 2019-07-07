//
// Created by a_mod on 23.01.2019.
//

#ifndef SIMSYSCOMPILER_ABSTRACTSYNTAXTREE_H
#define SIMSYSCOMPILER_ABSTRACTSYNTAXTREE_H


#include <grammar.h>
#include <Parser/ParseTree.h>
#include "ASTNode.h"

namespace ACC {

    /*! This class contains the AbstractSyntaxTree as generated by the language.
     * The class keeps a pointer to the root `ASTNode`, which is allocated on the heap.
     * The class also does memory managment by keeping track of the amount of times it is
     * referenced.
     * */
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
