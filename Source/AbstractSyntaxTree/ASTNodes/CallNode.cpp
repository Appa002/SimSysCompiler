#include <utility>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <Structure/Structures/Number/NumRValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/GenericLValueStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Structure/Structures/Char/CharRValueStructure.h>

#include "CallNode.h"

std::shared_ptr<ACC::Structure> ACC::CallNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    size_t totalRspSubtracted = 0;

    for(size_t i = children.size() - 1; i >= 1; i--){
        auto value = children[i]->generate(code);
        fn.writeLine("sub rsp, " + std::to_string(value->type.getSize()));
        totalRspSubtracted += value->type.getSize();

        value->operatorCopy(std::make_shared<GenericLValueStructure>(value->type, "rsp"), code);
        value->cleanUp(code);
    }

    auto name = children[0]->data.asT<std::string>();
    fn.writeLine("call " + name);
    fn.writeLine("add rsp, " + std::to_string(totalRspSubtracted));

    Type returnType = code.getFnSymbol(name).returnType;

    if(returnType == Type(BuiltIns::numType))
        return std::make_shared<NumRValueStructure>(Register::rA);

    else if (returnType == Type(BuiltIns::ptrType))
        return std::make_shared<PtrRValueStructure>(Register::rA, Type(type.getPointingTo()));

    else if (returnType == Type(BuiltIns::charType))
        return std::make_shared<CharRValueStructure>(Register::rA);

    return nullptr;
}

ACC::CallNode::CallNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
