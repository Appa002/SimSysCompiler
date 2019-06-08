#include <utility>

#include "AddNode.h"
#include <Logger/Logger.h>

std::shared_ptr<ACC::Structure> ACC::AddNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);

    auto out = lhs->operatorAdd(rhs, code);

    lhs->cleanUp(code);
    rhs->cleanUp(code);

    return out;
}

ACC::AddNode::AddNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
