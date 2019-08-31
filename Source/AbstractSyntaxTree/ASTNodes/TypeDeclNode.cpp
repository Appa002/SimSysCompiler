//
// Created by a_mod on 20.08.2019.
//

#include "TypeDeclNode.h"
#include "TypeDeclBodyNode.h"
#include <Types/TypeTable.h>

#include <utility>
#include <Types/TypeTable.h>
#include <Error/Errors.h>

ACC::TypeDeclNode::TypeDeclNode(ACC::AstOperator op, std::string sym) : ASTNode(op, {}), sym(std::move(sym)){

}

std::shared_ptr<ACC::Structure> ACC::TypeDeclNode::generate(ACC::Code &code) {
    std::vector<TypeField> fields;
    size_t totalSize = 0;

    for(ASTNode* child : children){
        auto* asBody = dynamic_cast<TypeDeclBodyNode*>(child);
        fields.emplace_back(asBody->getName(), asBody->getType().id, asBody->getType().isPtr);
        totalSize += asBody->getType().size;
    }

    Type type = Type(sym, totalSize, fields);
    TypeTable::get()->addType(sym, type);

    return nullptr;
}


std::string ACC::TypeDeclNode::createRepresentation() const {
    return "Type Decl ("+sym+")";
}
