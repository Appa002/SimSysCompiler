#include <utility>
#include <Error/ASTError.h>

#include "DereferenceNode.h"

std::shared_ptr<ACC::Structure> ACC::DereferenceNode::generate(ACC::Code &code) {
    auto ptr = children[0]->generate(code);

    std::shared_ptr<Structure> out;

    try {
        out = ptr->operatorDereference(code);
    }catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }

    ptr->cleanUp(code);
    return out;
}

ACC::DereferenceNode::DereferenceNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children)
: ASTNode(op,std::move(children)) {

}
