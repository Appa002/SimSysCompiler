#include <utility>
#include <Error/ASTError.h>

#include "ReassignNode.h"
#include "IdNode.h"


std::shared_ptr<ACC::Structure> ACC::ReassignNode::generate(ACC::Code &code) {
    auto id = dynamic_cast<IdNode*>( children[0])->sym;
    auto expr = children[1]->generate(code);
    auto var = code.getVarSymbol(id);

    try {
        var->operatorCopy(expr, code);
    } catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }
    expr->cleanUp(code);

    return nullptr;
}

ACC::ReassignNode::ReassignNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children)
        : ASTNode(op, std::move(children)) {

}
