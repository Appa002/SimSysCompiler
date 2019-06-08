#include <utility>
#include <Structure/Structures/Number/NumLValueStructure.h>

#include "AssignNode.h"
#include <memory>
#include <Structure/Structures/GenericLValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>


std::shared_ptr<ACC::Structure> ACC::AssignNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();

    auto id  =  children[0]->data.asT<std::string>();
    auto type = children[1]->data.asT<Type>();
    auto expr = children[2]->generate(code);

    fn.curBpOffset += expr->type.getSize();

    std::shared_ptr<Structure> address;

    if(type == BuiltIns::numType)
        address = std::make_shared<NumLValueStructure>("rbp - " + std::to_string(fn.curBpOffset));
    else if (type == BuiltIns::ptrType)
        address = std::make_shared<PtrLValueStructure>("rbp - " + std::to_string(fn.curBpOffset), type);

    expr->operatorCopy(address, code);
    expr->cleanUp(code);

    code.emplaceVarSymbol(id, address);
    return nullptr;
}

ACC::AssignNode::AssignNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
