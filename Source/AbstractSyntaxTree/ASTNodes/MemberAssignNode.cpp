#include <utility>

#include <General/builtinTypes.h>
#include <Structure/Structures/ElementaryStructure.h>
#include <Error/Errors.h>
#include "MemberAccessNode.h"
#include "MemberAssignNode.h"

std::shared_ptr<ACC::Structure> ACC::MemberAssignNode::generate(ACC::Code &code) {
    std::shared_ptr<ACC::Structure> var;
    try {
        var = code.getVarSymbol(obj);
    }catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }

    try {
        return var->operatorDot(code, member);
    } catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }
}

std::string ACC::MemberAssignNode::createRepresentation() const {
    return "MemberAssign ( "+obj+"."+member+" )";
}

ACC::MemberAssignNode::MemberAssignNode( ACC::AstOperator op, std::vector<ASTNode*> children, std::string obj, std::string member)
: obj(std::move(obj)), member(std::move(member)), ASTNode(op, std::move(children)){

}
