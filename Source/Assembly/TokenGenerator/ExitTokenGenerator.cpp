#include "ExitTokenGenerator.h"

ACC::ExitTokenGenerator::ExitTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::ExitTokenGenerator::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto expr = node->children[0]->asExpr()->generate(code);

    fn.writeLine(expr.copyToRegister("rdi", code));
    fn.writeLine("mov rax, 60");
    fn.writeLine("syscall");

    return {};
}
