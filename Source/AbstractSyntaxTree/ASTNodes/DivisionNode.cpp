#include <utility>

#include "DivisionNode.h"

std::shared_ptr<ACC::Structure> ACC::DivisionNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);

    auto out = lhs->operatorDivision(rhs, code);

    lhs->cleanUp(code);
    rhs->cleanUp(code);

    return out;
}

ACC::DivisionNode::DivisionNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                     std::move(children)) {

}
