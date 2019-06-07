#include <utility>
#include <Structure/Structures/NumLValueStructure.h>
#include <Structure/Structures/NumRValueStructure.h>
#include <builtinTypes.h>

#include "CallNode.h"

std::shared_ptr<ACC::Structure> ACC::CallNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    size_t totalRspSubtracted = 0;

    for(size_t i = children.size() - 1; i >= 1; i--){
        auto value = children[i]->generate(code);
        fn.writeLine("sub rsp, " + std::to_string(value->type.getSize()));
        totalRspSubtracted += value->type.getSize();

        if(value->type == BuiltIns::numType)
            value->operatorCopy(std::make_shared<NumLValueStructure>("rsp"), code);
    }

    auto name = children[0]->data.asT<std::string>();
    fn.writeLine("call " + name);
    fn.writeLine("add rsp, " + std::to_string(totalRspSubtracted));
    return std::make_shared<NumRValueStructure>(Register::rA);


  /*  auto& fn = code.getFnSymbol();
    size_t totalRspSubtracted = 0;
    for(size_t i = node->children.size() - 1; i >= 1; i--){
        auto value = node->children[i]->asExpr()->generate(code);
        fn.writeLine("sub rsp, " + std::to_string(value.typeId.getSize()));
        totalRspSubtracted += value.typeId.getSize();
        fn.writeLine(value.copyToStack(code));
    }

    auto name = node->children[0]->data.asT<std::string>();
    fn.writeLine("call " + name);
    fn.writeLine("add rsp, " + std::to_string(totalRspSubtracted));

    auto out = Structure(StructureType::elementary);
    out.typeId = code.getFnSymbol(name).returnType;

    out.copyToRegister = [](std::string reg, Code& c){
        if(reg != "rax")
            return "mov " + reg + " , rax";
        return std::string();
    };

    out.copyToStack = [](Code& c){
        return "mov qword [rsp], rax";
    };

    out.copyToBpOffset = [=](int32_t offset, Code& c){
        std::string sign = offset < 0 ? ("-") : ("+");
        if(offset < 0) offset *= -1;
        std::string offstr = std::to_string(offset);

        return "mov qword [rbp " + sign + offstr + "], rax";
    };

    return out;
    */
}

ACC::CallNode::CallNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
