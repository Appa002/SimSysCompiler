#include <utility>

#include <utility>
#include <Error/ASTError.h>

#include "IdNode.h"

std::shared_ptr<ACC::Structure> ACC::IdNode::generate(ACC::Code &code) {
    try {
        return code.getVarSymbol(sym);
    }catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }
}

ACC::IdNode::IdNode(ACC::AstOperator op, std::string str) : ASTNode(op, {}), sym(std::move(str)) {

}

std::string ACC::IdNode::createRepresentation() const {
    return "Id ( " + sym + ")";
}
