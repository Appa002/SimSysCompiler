//
// Created by a_mod on 20.08.2019.
//

#include "TypeDeclNode.h"
#include "TypeDeclBodyNode.h"
#include <Assembly/Code.h>
#include <Types/TypeTable.h>

#include <utility>
#include <Types/TypeTable.h>
#include <Error/Errors.h>

ACC::TypeDeclNode::TypeDeclNode(ACC::AstOperator op, std::string sym) : ASTNode(op, {}), sym(std::move(sym)){

}

std::shared_ptr<ACC::Structure> ACC::TypeDeclNode::generate(ACC::Code &code) {
    std::unordered_map<std::string, TypeField> fields;
    std::unordered_map<std::string, size_t> fieldMap;
    size_t totalSize = 0;

    for(ASTNode* child : children){
        auto* asBody = dynamic_cast<TypeDeclBodyNode*>(child);
        fields[asBody->getName()]  = TypeField(asBody->getName(), asBody->getType().id, asBody->getType().isPtr);
        fieldMap[asBody->getName()] = totalSize;
        totalSize += asBody->getType().size;
    }

    Type type = Type(sym, totalSize, fields);
    type.fieldSizes = fieldMap;
    TypeTable::get()->addType(sym, type);

    auto& fn = code.emplaceFnSymbol("?" + type.id + ".operatorCopy");
    code.popFnFromStack();
    fn.curBpOffset = 16;
    fn.returnType = Type("num", 8);
    fn.argsType = {Type::createPtr("char"),Type::createPtr("char")};

    fn.code = R"(
mov r15, [rbp + 16]
mov [rbp - 8], r15
mov r15, [rbp + 24]
mov [rbp - 16], r15
mov r15, [rbp - 16]
mov r15b, [r15]
mov r14, [rbp - 8]
mov [ r14 ], r15b
mov r15, [rbp - 8]
mov r14, 1
add r15, r14
mov r14, [rbp - 16]
mov r13, 1
add r14, r13
mov r13, r14
mov r13b, [r13]
mov r14, r15
mov [ r14 ], r13b
mov rax, 0
leave
ret
)";

    return nullptr;
}


std::string ACC::TypeDeclNode::createRepresentation() const {
    return "Type Decl ("+sym+")";
}
