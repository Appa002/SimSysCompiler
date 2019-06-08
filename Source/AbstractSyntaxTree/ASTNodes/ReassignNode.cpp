#include <utility>

#include "ReassignNode.h"


std::shared_ptr<ACC::Structure> ACC::ReassignNode::generate(ACC::Code &code) {
    auto id = children[0]->data.asT<std::string>();
    auto expr = children[1]->generate(code);
    auto var = code.getVarSymbol(id);

    auto out = expr->operatorCopy(var, code);

    expr->cleanUp(code);

    return nullptr;
}

ACC::ReassignNode::ReassignNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children)
        : ASTNode(op, std::move(children)) {

}
