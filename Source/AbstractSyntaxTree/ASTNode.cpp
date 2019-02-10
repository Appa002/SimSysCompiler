#include <utility>
#include "ASTNode.h"
#include <AbstractSyntaxTree/process.h>
#include <IntermediateCodeGenerator/Stmt.h>
#include <IntermediateCodeGenerator/Expr.h>
#include <Logger/Logger.h>

#include <IntermediateCodeGenerator/TokenGenerator/PlusTokenGenerator.h>
#include <IntermediateCodeGenerator/TokenGenerator/MinusTokenGenerator.h>
#include <IntermediateCodeGenerator/TokenGenerator/LiteralTokenGenerator.h>
#include <IntermediateCodeGenerator/TokenGenerator/SeqTokenGenerator.h>
#include <IntermediateCodeGenerator/TokenGenerator/AssignTokenGenerator.h>
#include <IntermediateCodeGenerator/TokenGenerator/IdTokenGenerator.h>
#include <IntermediateCodeGenerator/TokenGenerator/PrintTokenGenerator.h>

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



std::unique_ptr<ACC::Expr> ACC::ASTNode::asExpr() {
    switch (op){
        case AstOperator::PLUS:
            return std::unique_ptr<Expr>(new PlusTokenGenerator(this));
        case AstOperator::MINUS:
            return std::unique_ptr<Expr>(new MinusTokenGenerator(this));
        case AstOperator::LITERAL:
            return std::unique_ptr<Expr>(new LiteralTokenGenerator(this));
        case AstOperator::SEQ:
            return std::unique_ptr<Expr>(new SeqTokenGenerator(this));
        case AstOperator::ASSIGN:
            return std::unique_ptr<Expr>(new AssignTokenGenerator(this));
        case AstOperator::ID:
            return std::unique_ptr<Expr>(new IdTokenGenerator(this));
        case AstOperator::PRINT:
            return std::unique_ptr<Expr>(new PrintTokenGenerator(this));
    }
}