#include "IfTokenGenerator.h"

ACC::IfTokenGenerator::IfTokenGenerator(ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::IfTokenGenerator::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();

    auto expr = node->children[0]->asExpr()->generate(code);

    auto reg = code.getFreeRegister();

    fn.writeLine(expr.copyToRegister(registerToString(expr.typeId.getSize(), reg), code));
    fn.writeLine("cmp " + registerToString(expr.typeId.getSize(), reg) + ", 0"); //TODO: Remove

    auto uuid = code.getUUID();

    fn.writeLine("jnz ." + uuid);
    auto block = node->children[1]->asExpr()->generate(code);
    fn.writeLine("."+uuid+":");

    return {};
    /*
     * cmp expr, 0 ; true if expr is true
     * jnz .sym
     * block
     * .sym
     * rest
     *
     * */
}
