#include <utility>

#include <utility>

#include "IdNode.h"

std::shared_ptr<ACC::Structure> ACC::IdNode::generate(ACC::Code &code) {
     return code.getVarSymbol(sym);
}

ACC::IdNode::IdNode(ACC::AstOperator op, std::string str) : ASTNode(op, {}), sym(std::move(str)) {

}

std::string ACC::IdNode::createRepresentation() const {
    return "Id ( " + sym + ")";
}
