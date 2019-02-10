#include "AssignTokenGenerator.h"

ACC::temporary ACC::AssignTokenGenerator::generate(ACC::Code &code) {
    temporary rhs = node->children[1]->asExpr()->generate(code);
    temporary lhs = code.emplaceSymbol(node->children[0]->str);
    code.emplaceOperator(Operator(OperatorId::COPY, rhs, 0, lhs));
    return 0;
}

ACC::AssignTokenGenerator::AssignTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}
