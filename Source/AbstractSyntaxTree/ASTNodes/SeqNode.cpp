#include <utility>

#include "SeqNode.h"

std::shared_ptr<ACC::Structure> ACC::SeqNode::generate(ACC::Code &code) {
    /*if(node->children.size() == 2)
        node->children[1]->asExpr()->generate(code);
    node->children[0]->asExpr()->generate(code);
    return {};*/
    return nullptr;
}

ACC::SeqNode::SeqNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                               std::move(
                                                                                                                       children)) {

}

