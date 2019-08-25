//
// Created by a_mod on 20.08.2019.
//

#include "TypeDeclBodyNode.h"
#include <Types/TypeTable.h>

#include <utility>
#include <Error/Errors.h>

ACC::TypeDeclBodyNode::TypeDeclBodyNode(ACC::AstOperator op, std::vector<ASTNode*> children, std::string sym)
: ASTNode(op, std::move(children)), sym(std::move(sym)){

}

std::shared_ptr<ACC::Structure> ACC::TypeDeclBodyNode::generate(ACC::Code &code) {
    throw std::runtime_error("Can't generate type def node.");
}

std::string ACC::TypeDeclBodyNode::createRepresentation() const {
    return "TypeDeclBody ("+sym+")";
}
