#include <utility>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/GenericLValueStructure.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Structure/Structures/Bool/BoolLValueStructure.h>
#include <Structure/Structures/User/UserStructure.h>
#include <Structure/Structures/User/UserLValueStructure.h>
#include <Error/Errors.h>

#include "FunctionNode.h"
#include "TypeNode.h"
#include "IdNode.h"


std::shared_ptr<ACC::Structure> ACC::FunctionNode::generate(ACC::Code &code) {
    auto name = dynamic_cast<IdNode*>(children[0])->sym;

    checkIfReserved(name);

    auto& fn = code.emplaceFnSymbol(name);
    fn.returnType = dynamic_cast<TypeNode*>(children[1])->getType();
    fn.argsType = getArgumentTypes();

    size_t offset = 16;

    code.pushScope();

    for(size_t i = 2; i < children.size() - 1; i++){
        std::shared_ptr<Structure> structure;
        auto container = children[i];
        auto type = dynamic_cast<TypeNode*>(container->children[1])->getType();
        auto size = type.size;
        auto sym = dynamic_cast<IdNode*>(container->children[0])->sym;
        auto loc = fn.curBpOffset + size;
        auto locStr = std::to_string(loc);

        checkIfReserved(sym);

        if(type.isPtr)
            structure = std::make_shared<PtrLValueStructure>("rbp - " + locStr, type);

        else if (type == Type("num", 8))
            structure = std::make_shared<NumLValueStructure>("rbp - " + locStr);

        else if (type == Type("char", 1))
            structure = std::make_shared<CharLValueStructure>("rbp - " + locStr);

        else if (type == Type("bool", 1))
            structure = std::make_shared<BoolLValueStructure>("rbp - " + locStr);

        else
            structure = std::make_shared<UserLValueStructure>("rbp - " + locStr, type);

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
        auto type = dynamic_cast<TypeNode*>(children[i]->children[1])->getType();
        argumentsType.push_back(type);
    }

    return argumentsType;
}

void ACC::FunctionNode::checkIfReserved(std::string const &name) {
    if (name == "fn")
        throw errors::ReservedNameError(this, name);

    else if (name == "else")
        throw errors::ReservedNameError(this, name);

    else if (name == "elif")
        throw errors::ReservedNameError(this, name);

    else if (name == "exit")
        throw errors::ReservedNameError(this, name);

    else if (name == "for")
        throw errors::ReservedNameError(this, name);

    else if (name == "if")
        throw errors::ReservedNameError(this, name);

    else if (name == "import")
        throw errors::ReservedNameError(this, name);

    else if (name == "return")
        throw errors::ReservedNameError(this, name);

    else if (name == "salloc")
        throw errors::ReservedNameError(this, name);

    else if (name == "syscall")
        throw errors::ReservedNameError(this, name);

    else if (name == "var")
        throw errors::ReservedNameError(this, name);

    else if (name == "while")
        throw errors::ReservedNameError(this, name);

    else if (name == "type")
        throw errors::ReservedNameError(this, name);

    else if (name == "trait")
        throw errors::ReservedNameError(this, name);

    else if (name == "this")
        throw errors::ReservedNameError(this, name);
}
