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
    std::vector<TypeField> fields;
    size_t totalSize = 0;

    for(ASTNode* child : children){
        auto* asBody = dynamic_cast<TypeDeclBodyNode*>(child);
        fields.emplace_back(asBody->getName(), asBody->getType().id, asBody->getType().isPtr);
        totalSize += asBody->getType().size;
    }

    Type type = Type(sym, totalSize, fields);
    TypeTable::get()->addType(sym, type);

    auto& fn = code.emplaceFnSymbol("?" + type.id + ".operatorCopy");
    code.popFnFromStack();
    fn.curBpOffset = 20;
    fn.returnType = Type("num", 8);
    fn.argsType = {Type("num", 8)};

    fn.code = R"(
mov rax, 1
mov rdi, 1
mov dword [rbp - 12], 0x79706f43
mov dword [rbp - 8], 0x000a6465
lea rsi, [rbp - 12]
mov rdx, 7
syscall
mov rax, 0
leave
ret
)";

    return nullptr;
}


std::string ACC::TypeDeclNode::createRepresentation() const {
    return "Type Decl ("+sym+")";
}
