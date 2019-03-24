#include "PrintTokenGenerator.h"

ACC::PrintTokenGenerator::PrintTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::PrintTokenGenerator::generate(ACC::Code &code) {

    if(node->children[0]->op == AstOperator::ID){
        Dependency& var = code.getVarSymbol(node->children[0]->str);
        auto op = new Operator(OperatorId::PRINT, var.temp, 0, 0);
        op->opLhs = var.op;
        var.op->opResult = op;
        code.pushOp(op);
    }else{ // its a print with a literal e.g.: "print 10;"
        auto op = new Operator(OperatorId::IPRINT, (temporary)std::stoi(node->children[0]->str), 0, 0);
        code.pushOp(op);
    }
    return {};
}
