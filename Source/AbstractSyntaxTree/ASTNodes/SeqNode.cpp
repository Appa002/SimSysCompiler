#include <utility>

#include "SeqNode.h"

std::shared_ptr<ACC::Structure> ACC::SeqNode::generate(ACC::Code &code) {
    if(children.size() == 2)
        children[1]->generate(code);
    children[0]->generate(code);
    return nullptr;
}

ACC::SeqNode::SeqNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,std::move(children)) {

}

