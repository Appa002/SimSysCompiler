#include <utility>

#include "NotNode.h"

std::shared_ptr<ACC::Structure> ACC::NotNode::generate(ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto expr = children[0]->generate(code);
    auto out = expr->operatorNot(code);

    expr->cleanUp(code);

    return out;
}

ACC::NotNode::NotNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
