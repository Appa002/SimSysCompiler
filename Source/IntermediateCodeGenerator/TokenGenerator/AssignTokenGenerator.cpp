#include "AssignTokenGenerator.h"

ACC::Dependency ACC::AssignTokenGenerator::generate(ACC::Code &code) {
    Dependency rhs = node->children[1]->asExpr()->generate(code);
    Dependency& lhs = code.emplaceSymbol(node->children[0]->str, nullptr);

    auto op = new Operator(OperatorId::COPY, rhs.temp, 0, lhs.temp);
    op->opLhs = rhs.op;
    lhs.op = op;

    code.pushOp(op);
    return {};
}

ACC::AssignTokenGenerator::AssignTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}
