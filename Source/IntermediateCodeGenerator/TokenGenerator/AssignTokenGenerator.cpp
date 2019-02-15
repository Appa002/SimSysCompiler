#include "AssignTokenGenerator.h"

ACC::Dependency ACC::AssignTokenGenerator::generate(ACC::Code &code) {
    Dependency rhs = node->children[1]->asExpr()->generate(code);
    Dependency& lhs = code.emplaceSymbol(node->children[0]->str, nullptr);

    // lhs = rhs

    auto op = new Operator(OperatorId::COPY, rhs.temp, 0, lhs.temp);
    // copy lhs rhs 0
    //      r   lhs rhs

    op->opLhs = rhs.op;
    lhs.op = op;
    rhs.op->opResult = op;

    code.pushOp(op);
    return {op->result, op};
}

ACC::AssignTokenGenerator::AssignTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}
