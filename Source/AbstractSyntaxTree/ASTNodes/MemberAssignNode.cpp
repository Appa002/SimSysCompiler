#include <utility>

#include <General/builtinTypes.h>
#include <Structure/Structures/ElementaryStructure.h>
#include <Error/Errors.h>
#include "MemberAccessNode.h"
#include "MemberAssignNode.h"

std::shared_ptr<ACC::Structure> ACC::MemberAssignNode::generate(ACC::Code &code) {

    auto var = code.getVarSymbol(obj);

    try {
        return var->operatorDot(code, member);
    } catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }
}

std::string ACC::MemberAssignNode::createRepresentation() const {
    return "MemberAssing ( "+obj+"."+member+" )";
}

ACC::MemberAssignNode::MemberAssignNode( ACC::AstOperator op, std::vector<ASTNode*> children, std::string obj, std::string member)
: obj(std::move(obj)), member(std::move(member)), ASTNode(op, std::move(children)){

}
