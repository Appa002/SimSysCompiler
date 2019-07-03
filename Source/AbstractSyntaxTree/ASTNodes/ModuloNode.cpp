#include <utility>

#include <Logger/Logger.h>
#include "ModuloNode.h"

std::shared_ptr<ACC::Structure> ACC::ModuloNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);

    auto out = lhs->operatorModulo(rhs, code);

    lhs->cleanUp(code);
    rhs->cleanUp(code);

    return out;
}

ACC::ModuloNode::ModuloNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
