#include "SubtractTokenGenerator.h"

ACC::SubtractTokenGenerator::SubtractTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::SubtractTokenGenerator::generate(ACC::Code &code) {
    Dependency out = code.createTemporary();
    Dependency lhs = node->children[0]->asExpr()->generate(code);
    Dependency rhs = node->children[1]->asExpr()->generate(code);

    auto op = new Operator(OperatorId::SUBTRACT, lhs.temp, rhs.temp, out.temp);

    out.op = op;
    op->opLhs = lhs.op;
    op->opRhs = rhs.op;
    code.pushOp(op);
    return out;
}
