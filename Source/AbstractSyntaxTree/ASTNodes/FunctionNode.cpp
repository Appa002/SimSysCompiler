#include <utility>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/GenericLValueStructure.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Structure/Structures/Bool/BoolLValueStructure.h>

#include "FunctionNode.h"




std::shared_ptr<ACC::Structure> ACC::FunctionNode::generate(ACC::Code &code) {
    auto argumentTypes = getArgumentTypes();
    auto name = children[0]->data.asT<std::string>();
    name = code.mangleName(name, argumentTypes);


    auto& fn = code.emplaceFnSymbol(name);
    fn.returnType = children[1]->data.asT<Type>();

    size_t offset = 16;

    code.pushScope();

    for(size_t i = 2; i < children.size() - 1; i++){
        std::shared_ptr<Structure> structure;
        auto container = children[i];
        auto type = container->children[1]->data.asT<Type>();
        auto size = type.getSize();
        auto sym = container->children[0]->data.asT<std::string>();
        auto loc = fn.curBpOffset + size;
        auto locStr = std::to_string(loc);

        if(type == Type(BuiltIns::ptrType))
            structure = std::make_shared<PtrLValueStructure>("rbp - " + locStr, Type(type.getPointingTo()));
        else if (type == Type(BuiltIns::numType))
            structure = std::make_shared<NumLValueStructure>("rbp - " + locStr);
        else if (type == Type(BuiltIns::charType))
            structure = std::make_shared<CharLValueStructure>("rbp - " + locStr);
        else if (type == Type(BuiltIns::boolType))
            structure = std::make_shared<BoolLValueStructure>("rbp - " + locStr);

        fn.writeLine(copyIntoStackFrame(offset, loc, size, code));
        structure->cleanUp(code);
        code.emplaceVarSymbol(sym, structure);
        offset += size;
        fn.curBpOffset += size;
    }

    auto body = children.at(children.size() - 1)->generate(code);
    if(body)
        body->cleanUp(code);

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

std::vector<ACC::Type> ACC::FunctionNode::getArgumentTypes() {
    std::vector<Type> argumentsType;

    for(size_t i = 2; i < children.size() - 1; i++) {
        auto type = children[i]->children[1]->data.asT<Type>();
        argumentsType.push_back(type);
    }

    return argumentsType;
}
