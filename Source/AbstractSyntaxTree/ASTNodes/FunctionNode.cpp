#include <utility>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/GenericLValueStructure.h>

#include "FunctionNode.h"



std::shared_ptr<ACC::Structure> ACC::FunctionNode::generate(ACC::Code &code) {
    auto& fn = code.emplaceFnSymbol(children[0]->data.asT<std::string>());
    fn.returnType = children[1]->data.asT<TypeId>();

    size_t offset = 16;

    code.pushScope();

    for(size_t i = 2; i < children.size() - 1; i++){

        auto container = children[i];
        auto type = container->children[1]->data.asT<TypeId>();
        auto size = type.getSize();
        auto sym = container->children[0]->data.asT<std::string>();
        auto loc = fn.curBpOffset + size;
        auto locStr = std::to_string(loc);

        auto structure = std::make_shared<GenericLValueStructure>(type, "rbp - " + locStr);

        fn.writeLine(copyIntoStackFrame(offset, loc, size, code));

        code.emplaceVarSymbol(sym, structure);
        offset += size;
        fn.curBpOffset += size;
    }

    children.at(children.size() - 1)->generate(code);
    code.popFnFromStack();
    code.popScope();
    return nullptr;
}

std::string
ACC::FunctionNode::copyIntoStackFrame(size_t offset, size_t loc, size_t size, ACC::Code &code) {
    Register reg = code.getFreeRegister();
    std::string regStr = registerToString(size, reg);
    std::string offstr = std::to_string(offset);

    std::string locStr = std::to_string(loc);

    std::string out = "mov " + regStr + ", [rbp + " + offstr +"]\n";
    out += "mov [rbp - " + locStr + "], " + regStr;

    code.freeRegister(reg);
    return out;
}

ACC::FunctionNode::FunctionNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                     std::move(children)) {

}
