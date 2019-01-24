//
// Created by a_mod on 23.01.2019.
//

#include "AbstractSyntaxTree.h"
#include <AbstractSyntaxTree/process.h>

ACC::AbstractSyntaxTree::AbstractSyntaxTree(ACC::ParseTree parseTree) {
    root = process(parseTree.getRoot());
}
