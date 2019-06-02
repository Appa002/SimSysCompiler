#include "ReassignTokenGenerator.h"


ACC::Structure ACC::ReassignTokenGenerator::generate(ACC::Code &code) {
    auto id = node->children[0]->data.asT<std::string>();
    auto expr = node->children[1]->asExpr()->generate(code);
    auto& var = code.getVarSymbol(id);
    auto& fn = code.getFnSymbol();

    Register lhs = code.getFreeRegister();
    Register rhs = code.getFreeRegister();

    fn.writeLine(var.copyAddrToRegister(registerToString(8, lhs), code));
    fn.writeLine(expr.copyToRegister(registerToString(var.typeId.getSize(), rhs), code));

    fn.writeLine("mov [" + registerToString(var.typeId.getSize(), lhs) + "], " + registerToString(var.typeId.getSize(), rhs));

    code.freeRegister({lhs, rhs});

    //TODO: Type conversion.
    return {};
}

ACC::ReassignTokenGenerator::ReassignTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}