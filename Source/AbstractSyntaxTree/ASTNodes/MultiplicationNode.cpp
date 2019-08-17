#include <utility>
#include <Error/ASTError.h>

#include "MultiplicationNode.h"

std::shared_ptr<ACC::Structure> ACC::MultiplicationNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);
    std::shared_ptr<Structure> out;


    try {
        out = lhs->operatorMultiplication(rhs, code);
    } catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }
    lhs->cleanUp(code);
    rhs->cleanUp(code);
    return out;

}

ACC::MultiplicationNode::MultiplicationNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children)
: ASTNode(op,std::move(children)) {

}
