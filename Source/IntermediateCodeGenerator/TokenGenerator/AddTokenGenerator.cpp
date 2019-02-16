#include "AddTokenGenerator.h"

ACC::AddTokenGenerator::AddTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::AddTokenGenerator::generate(ACC::Code &code) {
    Dependency out = code.createTemporary();
    Dependency lhs = node->children[0]->asExpr()->generate(code);
    Dependency rhs = node->children[1]->asExpr()->generate(code);

    auto op = new Operator(OperatorId::ADD, lhs.temp, rhs.temp, out.temp);

    lhs.op->opResult = op;
    rhs.op->opResult = op;

    out.op = op;
    op->opLhs = lhs.op;
    op->opRhs = rhs.op;
    code.pushOp(op);
    return out;
}
