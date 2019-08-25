//
// Created by a_mod on 20.08.2019.
//

#include "TypeDeclNode.h"
#include <Types/TypeTable.h>

#include <utility>
#include <Error/Errors.h>

ACC::TypeDeclNode::TypeDeclNode(ACC::AstOperator op, std::string sym) : ASTNode(op, {}), sym(std::move(sym)){

}

std::shared_ptr<ACC::Structure> ACC::TypeDeclNode::generate(ACC::Code &code) {
    throw std::runtime_error("Can't generate type def node.");
}

std::string ACC::TypeDeclNode::createRepresentation() const {
    return "Type Decl ("+sym+")";
}
