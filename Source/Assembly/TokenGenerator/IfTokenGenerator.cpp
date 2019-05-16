#include "IfTokenGenerator.h"

ACC::IfTokenGenerator::IfTokenGenerator(ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::IfTokenGenerator::generate(ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto expr = node->children[0]->asExpr()->generate(code);
    auto uuid = code.getUUID();

    switch (expr.flag) {
        case StructureFlags::EQ:
            fn.writeLine("jnz ." + uuid);
            break;

        case StructureFlags::LT:
            fn.writeLine("jge ." + uuid);
            break;

        case StructureFlags::GT:
            fn.writeLine("jle ." + uuid);
            break;

        case StructureFlags::NEQ:
            fn.writeLine("je ." + uuid);
            break;

        case StructureFlags::LET:
            fn.writeLine("jg ." + uuid);
            break;

        case StructureFlags::GET:
            fn.writeLine("jl ." + uuid);
            break;
    }

    auto block = node->children[1]->asExpr()->generate(code);
    fn.writeLine("." + uuid + ":");

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
