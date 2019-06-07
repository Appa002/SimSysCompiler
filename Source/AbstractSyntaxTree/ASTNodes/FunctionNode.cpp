#include <utility>

#include "FunctionNode.h"



std::shared_ptr<ACC::Structure> ACC::FunctionNode::generate(ACC::Code &code) {
 /*   auto& fn = code.emplaceFnSymbol(node->children[0]->data.asT<std::string>());
    fn.returnType = node->children[1]->data.asT<TypeId>();

    size_t offset = 16;

    code.pushScope();

    for(size_t i = 2; i < node->children.size() - 1; i++){
        auto structure = Structure(StructureType::elementary);
        auto container = node->children[i];
        auto type = container->children[1]->data.asT<TypeId>();
        auto size = type.getSize();
        auto sym = container->children[0]->data.asT<std::string>();
        auto loc = fn.curBpOffset + size;
        auto locStr = std::to_string(loc);

        structure.typeId = type;

        fn.writeLine(copyIntoStackFrame(offset, loc, size, code));

        structure.copyToRegister = [=](std::string reg, Code& c){
            return "mov " + reg + ", [rbp - " + locStr + "]";
        };
        structure.copyToStack = [=](Code& c){
            Register reg = c.getFreeRegister();
            std::string out = "mov "+registerToString(size, reg)+", " + ("[rbp - " + locStr + "]");
            out += "\nmov [rsp], " + registerToString(size, reg);
            c.freeRegister(reg);
            return out;
        };

        structure.copyToBpOffset = [=](int32_t off, Code& c){
            Register reg = c.getFreeRegister();
            std::string regStr = registerToString(size, reg);
            std::string out = Movs::bp2bp(loc, off, regStr, size);
            c.freeRegister(reg);
            return out;
        };

        structure.copyAddrToRegister = [=](std::string reg, Code& c){
            return "lea " + reg + ", [rbp - " + locStr + "]";
        };

        code.emplaceVarSymbol(sym, structure);
        offset += size;
        fn.curBpOffset += size;
    }

    node->children.at(node->children.size() - 1)->asExpr()->generate(code);
    code.popFnFromStack();
    code.popScope();
    return {};
    */
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