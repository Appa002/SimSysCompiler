#include <utility>
#include "ASTNode.h"
#include <AbstractSyntaxTree/process.h>
#include <Logger/Logger.h>

ACC::ASTNode::ASTNode(AstOperator op, std::vector<ACC::ASTNode*> children) {
    this->op = op;
    this->children = std::move(children);
}

ACC::ASTNode::ASTNode(AstOperator op, std::string str) {
    this->op = op;
    this->str = std::move(str);
}

void ACC::ASTNode::_print(std::string indent, bool isLast) const {
    std::string representation = astOperator2String(op);
    auto colour = op == AstOperator::LITERAL ? (Log::Colour::Magenta) : (Log::Colour::Blue);

    LOG() << indent;
    if(isLast){
        LOG() << "\\-";
        indent += "     ";
    }else{
        LOG() << "|-";
        indent += "|    ";
    }
    LOG() << colour << "[" << representation << "]" << std::endl;

    for (int i = 0; i < children.size(); i++) {
        children[i]->_print(indent, i == children.size() - 1);
    }
}

std::string ACC::ASTNode::astOperator2String(AstOperator op) const{
    switch (op){
        case AstOperator::PLUS:
            return "+";
        case AstOperator::MINUS:
            return "-";
        case AstOperator::LITERAL:
            return str;
        case AstOperator::SEQ:
            return "SEQ";
        case AstOperator::ASSIGN:
            return "assign";
        case AstOperator::ID:
            return str;
        case AstOperator::PRINT:
            return "print";
    }
    return "";
}

void ACC::ASTNode::print() {
    std::stringstream ss;
    ss << "Generated Abstract Syntax Tree: (Node at:" << std::hex << this <<" used as root)";
    Log::Logger::get()->createHeading(ss.str());
    _print("", false);
}
