#include "LiteralTokenGenerator.h"

ACC::LiteralTokenGenerator::LiteralTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::temporary ACC::LiteralTokenGenerator::generate(ACC::Code &code) {
    temporary out = code.createTemporary();
    code.emplaceOperator(Operator(OperatorId::ICOPY, static_cast<address>(std::stoi(node->str)), 0, out));
    return out;
}
