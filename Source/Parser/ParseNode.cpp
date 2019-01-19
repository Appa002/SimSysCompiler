//
// Created by a_mod on 18.01.2019.
//

#include "ParseNode.h"

namespace ANSI_CODES{
    const std::string NONE_TERMINAL = "\033[34;1m";
    const std::string TERMINAL = "\033[35;1m";
    const std::string CLEAR = "\033[0m";
};

ACC::ParseNode::ParseNode() : value(Symbol::expr) {

}

ACC::ParseNode::ParseNode(ACC::Symbol s, ACC::IToken *t) : token(t), value(s) {

}

ACC::ParseNode::ParseNode(ACC::Symbol s) : value(s) {

}

ACC::ParseNode::~ParseNode() {
    for (const auto &child : children)
        delete child;
}

void ACC::ParseNode::print(std::string indent, bool isLast) const {
    std::string representation = token == nullptr ? (data::symbolToString(value)) : (token->getIdentifier());
    std::string colour = token == nullptr ? (ANSI_CODES::TERMINAL) : (ANSI_CODES::NONE_TERMINAL);

    std::cout << indent;
    if(isLast){
        std::cout << "\\-";
        indent += "     ";
    }else{
        std::cout << "|-";
        indent += "|    ";
    }
    std::cout << colour << "[" << representation << "]" <<  ANSI_CODES::CLEAR << std::endl;

    for (int i = 0; i < children.size(); i++) {
        children[i]->print(indent, i == children.size() - 1);
    }
}



