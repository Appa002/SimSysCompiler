#include "IdTokenGenerator.h"

ACC::IdTokenGenerator::IdTokenGenerator(ASTNode *node) : Expr(node) {

}

ACC::temporary ACC::IdTokenGenerator::generate(ACC::Code &code) {
    temporary out = code.createTemporary();
    code.emplaceOperator(Operator(OperatorId::COPY, code.getSymbol(node->str), 0, out));
    return out;
}
