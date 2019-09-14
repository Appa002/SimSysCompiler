#include <utility>

#include "OrNode.h"
#include <Logger/Logger.h>
#include <Error/Errors.h>

std::shared_ptr<ACC::Structure> ACC::OrNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);

    std::shared_ptr<Structure> out;

    try {
        out = lhs->operatorOr(rhs, code);
    }catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }

    lhs->cleanUp(code);
    rhs->cleanUp(code);

    return out;
}

ACC::OrNode::OrNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
