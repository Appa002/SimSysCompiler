#include <utility>

#include <utility>

#include <utility>

#include <utility>
#include "ASTNode.h"
#include <AbstractSyntaxTree/process.h>
#include <Assembly/Stmt.h>
#include <Assembly/Expr.h>
#include <Logger/Logger.h>

#include <Assembly/TokenGenerator/AddTokenGenerator.h>
#include <Assembly/TokenGenerator/SubtractTokenGenerator.h>
#include <Assembly/TokenGenerator/LiteralTokenGenerator.h>
#include <Assembly/TokenGenerator/SeqTokenGenerator.h>
#include <Assembly/TokenGenerator/AssignTokenGenerator.h>
#include <Assembly/TokenGenerator/IdTokenGenerator.h>
#include <Assembly/TokenGenerator/SyscallTokenGenerator.h>
#include <Assembly/TokenGenerator/ExitTokenGenerator.h>
#include <Assembly/TokenGenerator/DivisionTokenGenerator.h>
#include <Assembly/TokenGenerator/MultiplicationTokenGenerator.h>
#include <Assembly/TokenGenerator/FunctionTokenGenerator.h>
#include <Assembly/TokenGenerator/ReturnTokenGenerator.h>
#include <Assembly/TokenGenerator/ReassignTokenGenerator.h>
#include <Assembly/TokenGenerator/CallTokenGenerator.h>
#include <Lexical/Tokens/LiteralToken.h>
#include <GeneralDataStore.h>
#include <builtinTypes.h>

ACC::ASTNode::ASTNode(AstOperator op, std::vector<ACC::ASTNode*> children) {
    this->op = op;
    this->children = std::move(children);
    this->type = BuiltIns::__none;
}



ACC::ASTNode::ASTNode(AstOperator op, ACC::GeneralDataStore literal, TypeId type) {
    this->op = op;
    this->data = std::move(literal);
    this->type = type;
}


ACC::ASTNode::ASTNode(AstOperator op, std::string str) {
    if(op == AstOperator::LITERAL)
        throw std::runtime_error("Initialise literals with a general store");
    this->op = op;
    this->type = BuiltIns::__none;
    this->data.storeT(std::move(str));
}

ACC::ASTNode::ASTNode(AstOperator op, ACC::GeneralDataStore store) {
    this->op = op;
    this->type = BuiltIns::__none;
    this->data = std::move(store);
}

ACC::ASTNode::ASTNode(AstOperator op) {
    if(op != AstOperator::__NONE)
        throw std::runtime_error("Single argument constructor for `ASTNode` can only be used for `AstOperator::__NONE`");
    this->op = op;
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
        case AstOperator::LITERAL:{
            if(type == BuiltIns::numType || type == BuiltIns::charType)
                return "Lit: " + std::to_string(data.createNumber());
            else if(type == BuiltIns::ptrCharType)
                return std::string("Lit: ") + "\"" + data.asT<std::string>() +"\"";
            else{
                std::string data = "[ ";
                for(size_t i = 0; i < this->data.size(); i++){
                    data += " `" + toHex(data.at(i)) + "`";
                    if(i + 1 < data.size())
                        data += ",";
                }
                data += " ]";

                return "Lit (Complex) " + data;
            }
        }
        case AstOperator::SEQ:
            return "SEQ";
        case AstOperator::ASSIGN:
            return "assign";
        case AstOperator::ID:
            return std::string("ID: ") + data.asT<std::string>(0);
        case AstOperator::SYSCALL:
            return "syscall";
        case AstOperator::EXIT:
            return "exit";
        case AstOperator::MULTIPLICATION:
            return "*";
        case AstOperator::DIVISION:
            return "/";
        case AstOperator::FUNCTION:
            return "function";
        case AstOperator::CALL:
            return "call";
        case AstOperator::RETURN:
            return "return";
        case AstOperator::__NONE:
            return "__none";
        case AstOperator::TYPE_DEF:
            return "type def; id: " + std::to_string(data.asT<TypeId>().getId()) +
            " size: " +  std::to_string(data.asT<TypeId>().getSize());
        case AstOperator::__CONTAINER:
            return "__container";
        case AstOperator::REASSIGN:
            return "reassign";
    }
    throw std::runtime_error("Unknown Symbol!");
}



std::unique_ptr<ACC::Expr> ACC::ASTNode::asExpr() {
    switch (op){
        case AstOperator::PLUS:
            return std::unique_ptr<Expr>(new AddTokenGenerator(this));
        case AstOperator::MINUS:
            return std::unique_ptr<Expr>(new SubtractTokenGenerator(this));
        case AstOperator::LITERAL:
            return std::unique_ptr<Expr>(new LiteralTokenGenerator(this));
        case AstOperator::SEQ:
            return std::unique_ptr<Expr>(new SeqTokenGenerator(this));
        case AstOperator::ASSIGN:
            return std::unique_ptr<Expr>(new AssignTokenGenerator(this));
        case AstOperator::ID:
            return std::unique_ptr<Expr>(new IdTokenGenerator(this));
        case AstOperator::SYSCALL:
            return std::unique_ptr<Expr>(new SyscallTokenGenerator(this));
        case AstOperator::EXIT:
            return std::unique_ptr<Expr>(new ExitTokenGenerator(this));
        case AstOperator::MULTIPLICATION:
            return std::unique_ptr<Expr>(new MultiplicationTokenGenerator(this));
        case AstOperator::DIVISION:
            return std::unique_ptr<Expr>(new DivisionTokenGenerator(this));
        case AstOperator::FUNCTION:
            return std::unique_ptr<Expr>(new FunctionTokenGenerator(this));
        case AstOperator::CALL:
            return std::unique_ptr<Expr>(new CallTokenGenerator(this));
        case AstOperator::RETURN:
            return std::unique_ptr<Expr>(new ReturnTokenGenerator(this));
        case AstOperator::REASSIGN:
            return std::unique_ptr<Expr>(new ReassignTokenGenerator(this));
        case AstOperator::__NONE:
            throw std::runtime_error("Operator `__none` can't be interpreted as an expression.");
        case AstOperator::TYPE_DEF:
            throw std::runtime_error("Operator `type_def` can't be interpreted as an expression.");
        case AstOperator::__CONTAINER:
            throw std::runtime_error("Operator `__container` can't be interpreted as an expression.");
    }
    return std::unique_ptr<Expr>(nullptr);
}

ACC::ASTNode::~ASTNode() {
    for(const auto& child : children){
        delete child;
    }
}

