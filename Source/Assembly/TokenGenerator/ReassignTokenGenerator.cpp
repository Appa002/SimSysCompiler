#include "ReassignTokenGenerator.h"


ACC::Structure ACC::ReassignTokenGenerator::generate(ACC::Code &code) {
    auto id = node->children[0]->data.asT<std::string>();
    auto expr = node->children[1]->asExpr()->generate(code);
    auto var = code.getVarSymbol(id);

    var.copyToRegister = expr.copyToRegister;
    var.copyToBpOffset = expr.copyToBpOffset;
    var.copyToStack = expr.copyToStack;

    code.emplaceVarSymbol(id, expr);

    return {};
}

ACC::ReassignTokenGenerator::ReassignTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}