#include "PlusTokenGenerator.h"

ACC::PlusTokenGenerator::PlusTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::temporary ACC::PlusTokenGenerator::generate(ACC::Code &code) {
    temporary out = code.createTemporary();
    temporary lhs = node->children[0]->asExpr()->generate(code);
    temporary rhs = node->children[1]->asExpr()->generate(code);

    code.emplaceOperator(Operator(OperatorId::PLUS, lhs, rhs, out));
    return out;
}
