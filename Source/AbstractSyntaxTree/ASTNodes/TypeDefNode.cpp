//
// Created by a_mod on 20.08.2019.
//

#include "TypeDefNode.h"
#include <Types/TypeTable.h>

#include <utility>
#include <Error/Errors.h>

ACC::TypeDefNode::TypeDefNode(ACC::AstOperator op, ACC::Type t) : ASTNode(op, {}), type(std::move(t)){

}

std::shared_ptr<ACC::Structure> ACC::TypeDefNode::generate(ACC::Code &code) {
    throw std::runtime_error("Can't generate type def node.");
}

ACC::TypeDefNode::TypeDefNode(ACC::AstOperator op, ACC::UnverifiedType t) : ASTNode(op, {}), unverifiedType(std::move(t)) {

}

ACC::Type ACC::TypeDefNode::getType() {
    if(type != Type("", 0))
        return type;

    if(!TypeTable::get()->isType(unverifiedType.id))
        throw errors::UnknownType(this, unverifiedType.id);

    if(unverifiedType.isPtr){
        type = Type::createPtr(unverifiedType.id);
        return type;
    }

    type = Type(unverifiedType.id, TypeTable::get()->getSize(unverifiedType.id));
    return type;

}

std::string ACC::TypeDefNode::createRepresentation() const {
    return "Type: " + unverifiedType.id + (unverifiedType.isPtr ? ("*"):(""));
}
