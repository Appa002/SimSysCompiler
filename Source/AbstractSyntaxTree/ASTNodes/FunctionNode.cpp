#include <utility>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/GenericLValueStructure.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Structure/Structures/Bool/BoolLValueStructure.h>

#include "FunctionNode.h"
#include "TypeDefNode.h"
#include "IdNode.h"


std::shared_ptr<ACC::Structure> ACC::FunctionNode::generate(ACC::Code &code) {
    auto name = dynamic_cast<IdNode*>(children[0])->sym;

    auto& fn = code.emplaceFnSymbol(name);
    fn.returnType = dynamic_cast<TypeDefNode*>(children[1])->getType();
    fn.argsType = getArgumentTypes();

    size_t offset = 16;

    code.pushScope();

    for(size_t i = 2; i < children.size() - 1; i++){
        std::shared_ptr<Structure> structure;
        auto container = children[i];
        auto type = dynamic_cast<TypeDefNode*>(container->children[1])->getType();
        auto size = type.size;
        auto sym = dynamic_cast<IdNode*>(container->children[0])->sym;
        auto loc = fn.curBpOffset + size;
        auto locStr = std::to_string(loc);

        if(type.isPtr)
            structure = std::make_shared<PtrLValueStructure>("rbp - " + locStr, type);

        else if (type == Type("num", 8))
            structure = std::make_shared<NumLValueStructure>("rbp - " + locStr);

        else if (type == Type("char", 1))
            structure = std::make_shared<CharLValueStructure>("rbp - " + locStr);

        else if (type == Type("bool", 1))
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
        auto type = dynamic_cast<TypeDefNode*>(children[i]->children[1])->getType();
        argumentsType.push_back(type);
    }

    return argumentsType;
}
