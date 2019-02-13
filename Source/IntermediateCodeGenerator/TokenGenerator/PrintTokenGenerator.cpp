#include "PrintTokenGenerator.h"

ACC::PrintTokenGenerator::PrintTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::PrintTokenGenerator::generate(ACC::Code &code) {
    Dependency var = code.getSymbol(node->children[0]->str);
    auto op = new Operator(OperatorId::PRINT, var.temp, 0, 0);
    op->opLhs = var.op;
    code.pushOp(op);
    return {};
}
