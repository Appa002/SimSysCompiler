//
// Created by a_mod on 18.01.2019.
//

#include "ParseNode.h"

ACC::ParseNode::ParseNode() : value(Symbol::expr) {

}

ACC::ParseNode::ParseNode(ACC::Symbol s) : value(s) {

}

ACC::ParseNode::~ParseNode(){
    for(const auto& child : children)
        delete child;
}

void ACC::ParseNode::print(unsigned int indent){
    std::cout << std::string(indent, ' ') << (int)value << std::endl;
    for(auto const& child : children)
        child->print(indent+2);
}



