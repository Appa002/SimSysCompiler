//
// Created by a_mod on 18.01.2019.
//

#include "ParseNode.h"
#include <Logger/Logger.h>
#include <iomanip>

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

void ACC::ParseNode::_print(std::string indent, bool isLast) const {
    std::string representation = token == nullptr ? (data::symbolToString(value)) : (token->getIdentifier());
    auto colour = token == nullptr ? (Log::Colour::Magenta) : (Log::Colour::Blue);

    LOG() << indent;
    if(isLast){
        LOG() << "\\-";
        indent += "     ";
    }else{
        LOG() << "|-";
        indent += "|    ";
    }
   // std::cout
    LOG() << colour << "[" << representation << "]" << std::endl;

    for (int i = 0; i < children.size(); i++) {
        children[i]->_print(indent, i == children.size() - 1);
    }
}

void ACC::ParseNode::print() const {
    std::stringstream ss;
    ss << "Parse Tree Generated. (Node at:" << std::hex << this <<" used as root)";
    Log::Logger::get()->createHeading(ss.str());
    _print("", false);
}



