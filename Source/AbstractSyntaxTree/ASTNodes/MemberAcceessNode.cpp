#include <utility>

#include <General/builtinTypes.h>
#include <Structure/Structures/ElementaryStructure.h>
#include <Error/Errors.h>
#include "MemberAccessNode.h"

std::shared_ptr<ACC::Structure> ACC::MemberAccessNode::generate(ACC::Code &code) {

    auto var = code.getVarSymbol(obj);

    try {
        return var->operatorDot(code, member);
    } catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }
}

ACC::MemberAccessNode::MemberAccessNode(ACC::AstOperator op, std::string obj, std::string member) : obj(std::move(obj)), member(std::move(member)), ASTNode(op, {}){
}

std::string ACC::MemberAccessNode::createRepresentation() const {
    return "MemberAccess ( "+obj+"."+member+" )";
}

ACC::MemberAccessNode::MemberAccessNode( ACC::AstOperator op, std::vector<ASTNode*> children, std::string obj, std::string member)
: obj(std::move(obj)), member(std::move(member)), ASTNode(op, std::move(children)){

}
