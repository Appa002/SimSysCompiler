//
// Created by a_mod on 23.01.2019.
//

#include "AbstractSyntaxTree.h"
#include <AbstractSyntaxTree/process.h>
#include <sstream>
#include <Logger/Logger.h>

ACC::AbstractSyntaxTree::AbstractSyntaxTree(ACC::ParseTree parseTree) {
    root = process(parseTree.getRoot());
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
