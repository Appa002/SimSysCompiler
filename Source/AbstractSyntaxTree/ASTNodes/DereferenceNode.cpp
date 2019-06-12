#include <utility>

#include "DereferenceNode.h"

std::shared_ptr<ACC::Structure> ACC::DereferenceNode::generate(ACC::Code &code) {
    auto ptr = children[0]->generate(code);
    auto out = ptr->operatorDereference(code);
    ptr->cleanUp(code);
    return out;
}

ACC::DereferenceNode::DereferenceNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children)
: ASTNode(op,std::move(children)) {

}
