#include "PrintTokenGenerator.h"

ACC::PrintTokenGenerator::PrintTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::temporary ACC::PrintTokenGenerator::generate(ACC::Code &code) {
    temporary var = code.getSymbol(node->children[0]->str);
    code.emplaceOperator(Operator(OperatorId::PRINT, var, 0, 0));
    return 0;
}
