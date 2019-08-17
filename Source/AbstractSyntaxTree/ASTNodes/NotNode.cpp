#include <utility>
#include <Error/ASTError.h>

#include "NotNode.h"

std::shared_ptr<ACC::Structure> ACC::NotNode::generate(ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto expr = children[0]->generate(code);

    std::shared_ptr<Structure> out;

    try {
        out = expr->operatorNot(code);
    }catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }
    expr->cleanUp(code);

    return out;
}

ACC::NotNode::NotNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
