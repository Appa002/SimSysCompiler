#include <utility>

#include "AddNode.h"
#include <Logger/Logger.h>
#include <Error/ASTError.h>

std::shared_ptr<ACC::Structure> ACC::AddNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);
    std::shared_ptr<Structure> out;


    try {
        out = lhs->operatorAdd(rhs, code);
    }catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }

    lhs->cleanUp(code);
    rhs->cleanUp(code);

    return out;
}

ACC::AddNode::AddNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
