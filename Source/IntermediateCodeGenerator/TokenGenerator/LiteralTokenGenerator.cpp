#include "LiteralTokenGenerator.h"

ACC::LiteralTokenGenerator::LiteralTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::LiteralTokenGenerator::generate(ACC::Code &code) {
    Dependency out = code.createTemporary();
    auto op = new Operator(OperatorId::ICOPY, static_cast<address>(std::stoi(node->str)), 0, out.temp);
    out.op = op;
    code.pushOp(op);
    return out;
}
