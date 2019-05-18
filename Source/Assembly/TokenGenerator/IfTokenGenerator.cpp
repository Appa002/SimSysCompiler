#include "IfTokenGenerator.h"

ACC::IfTokenGenerator::IfTokenGenerator(ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::IfTokenGenerator::generate(ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto uuid = code.getUUID();

    code.pushScope();
    auto expr = node->children[0]->asExpr()->generate(code);

    Register reg;
    if(!expr.registerUsed.empty())
        reg = expr.registerUsed[0];
    else
        reg = code.getFreeRegister();

    fn.writeLine(expr.copyToRegister(registerToString(1, reg), code));
    fn.writeLine("cmp " + registerToString(1, reg) + ", 1");
    fn.writeLine("jnz ." + uuid);

    code.freeRegister(expr.registerUsed);
    code.freeRegister(reg);

    auto block = node->children[1]->asExpr()->generate(code);
    fn.writeLine("." + uuid + ":");


    code.popScope();
    return {};
}
