#include <utility>

#include "MultiplicationNode.h"

std::shared_ptr<ACC::Structure> ACC::MultiplicationNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);

    auto out = lhs->operatorMultiplication(rhs, code);

    lhs->cleanUp(code);
    rhs->cleanUp(code);

    return out;
}

ACC::MultiplicationNode::MultiplicationNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                                 std::move(
                                                                                                                         children)) {

}
