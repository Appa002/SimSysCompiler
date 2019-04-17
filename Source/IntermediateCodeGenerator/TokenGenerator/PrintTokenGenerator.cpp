#include "PrintTokenGenerator.h"

ACC::PrintTokenGenerator::PrintTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::PrintTokenGenerator::generate(ACC::Code &code) {

    if(node->children[0]->op == AstOperator::LITERAL){ // its a print with a literal e.g.: "print 10;"
        auto op = new Operator(OperatorId::IPRINT, (temporary)std::stoi(node->children[0]->str), 0, 0);
        code.pushOp(op);
    }
    else{
        Dependency var = node->children[0]->asExpr()->generate(code);
        auto op = new Operator(OperatorId::PRINT, var.temp, 0, 0);
        op->opLhs = var.op;
        code.pushOp(op);
    }
    return {};
}
