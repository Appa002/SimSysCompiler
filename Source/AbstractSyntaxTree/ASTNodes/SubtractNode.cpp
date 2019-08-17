#include <utility>
#include <Error/ASTError.h>

#include "SubtractNode.h"



std::shared_ptr<ACC::Structure> ACC::SubtractNode::generate(ACC::Code &code){
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);
    std::shared_ptr<Structure> out;

    try {
        out = lhs->operatorSubtract(rhs, code);
    } catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }

    lhs->cleanUp(code);
    rhs->cleanUp(code);

    return out;
}

ACC::SubtractNode::SubtractNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children)
        : ASTNode(op, std::move(children)) {

}
