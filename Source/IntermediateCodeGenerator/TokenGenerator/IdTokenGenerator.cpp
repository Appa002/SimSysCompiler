#include "IdTokenGenerator.h"

ACC::IdTokenGenerator::IdTokenGenerator(ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::IdTokenGenerator::generate(ACC::Code &code) {
    Dependency out = code.createTemporary();
    Dependency& var = code.getVarSymbol(node->str);

    auto op = new Operator(OperatorId::COPY, var.temp, 0, out.temp);
    op->opLhs = var.op;
    code.pushOp(op);
    out.op = op;
    return out;
}
