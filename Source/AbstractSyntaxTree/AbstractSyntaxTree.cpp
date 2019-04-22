//
// Created by a_mod on 23.01.2019.
//

#include "AbstractSyntaxTree.h"
#include <AbstractSyntaxTree/process.h>
#include <sstream>
#include <Logger/Logger.h>

ACC::AbstractSyntaxTree::AbstractSyntaxTree(ACC::ParseTree parseTree) {
    root = process(parseTree.getRoot(), nullptr);
    refCount++;
}

void ACC::AbstractSyntaxTree::print() {
    std::stringstream ss;
    ss << "Generated Abstract Syntax Tree: (Node at:" << std::hex << this <<" used as root)";
    Log::Logger::get()->createHeading(ss.str());
    root->_print("", false);
}

ACC::ASTNode *ACC::AbstractSyntaxTree::getRoot() const{
    return root;
}

ACC::AbstractSyntaxTree::~AbstractSyntaxTree() {
    refCount--;
    if(refCount != 0)
        return;

    delete root;
}

ACC::AbstractSyntaxTree::AbstractSyntaxTree(const ACC::AbstractSyntaxTree &other) : root(other.root), refCount(other.refCount){
    refCount++;
}
