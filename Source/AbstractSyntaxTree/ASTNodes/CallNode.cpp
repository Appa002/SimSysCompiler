#include <utility>
#include <Structure/Structures/NumLValueStructure.h>
#include <Structure/Structures/NumRValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/ElementaryLValueStructure.h>

#include "CallNode.h"

std::shared_ptr<ACC::Structure> ACC::CallNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    size_t totalRspSubtracted = 0;

    for(size_t i = children.size() - 1; i >= 1; i--){
        auto value = children[i]->generate(code);
        fn.writeLine("sub rsp, " + std::to_string(value->type.getSize()));
        totalRspSubtracted += value->type.getSize();

        value->operatorCopy(std::make_shared<ElementaryLValueStructure>(value->type, "rsp"), code);
    }

    auto name = children[0]->data.asT<std::string>();
    fn.writeLine("call " + name);
    fn.writeLine("add rsp, " + std::to_string(totalRspSubtracted));
    return std::make_shared<NumRValueStructure>(Register::rA); // TODO: Return type
}

ACC::CallNode::CallNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
