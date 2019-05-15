#include "AssignTokenGenerator.h"



ACC::Structure ACC::AssignTokenGenerator::generate(ACC::Code &code) {
    auto id = node->children[0]->data.asT<std::string>();
    auto type = node->children[1]->data.asT<TypeId>();
    auto expr = node->children[2]->asExpr()->generate(code);

    //TODO: Type Conversions.
    expr.typeId = type;

    if(!expr.isStored){
        auto& fn = code.getFnSymbol();
        fn.curBpOffset += expr.typeId.getSize();
        fn.writeLine(expr.copyToBpOffset(-fn.curBpOffset, code));
        expr.copyToBpOffset = [=](int32_t offset, Code& c){
            Register reg = c.getFreeRegister();
            std::string sign = offset < 0 ? ("-") : ("+");
            offset = offset < 0 ? (offset * -1) : (offset);
            std::string out = "mov " + registerToString(expr.typeId.getSize(), reg) + ", [rbp - " + std::to_string(fn.curBpOffset) + "]";
            out += "\nmov [rbp " + sign + std::to_string(offset) + "], " + registerToString(expr.typeId.getSize(), reg);
            c.freeRegister(reg);
            return out;
        };

        expr.copyToStack = [=](Code& c){
            Register reg = c.getFreeRegister();
            std::string out = "mov " + registerToString(expr.typeId.getSize(), reg) + ", [rbp - " + std::to_string(fn.curBpOffset) + "]";
            out += "\nmov [rsp], " + registerToString(expr.typeId.getSize(), reg);
            c.freeRegister(reg);
            return out;
        };
    }

    code.emplaceVarSymbol(id, expr);

    return {};
}

ACC::AssignTokenGenerator::AssignTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}