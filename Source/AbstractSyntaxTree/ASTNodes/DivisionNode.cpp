#include <utility>
#include <Error/ASTError.h>

#include "DivisionNode.h"

std::shared_ptr<ACC::Structure> ACC::DivisionNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);
    std::shared_ptr<Structure> out;

    try {
        out = lhs->operatorDivision(rhs, code);
    } catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }

    lhs->cleanUp(code);
    rhs->cleanUp(code);

    return out;
}

ACC::DivisionNode::DivisionNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                     std::move(children)) {

}
