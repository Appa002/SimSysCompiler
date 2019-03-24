#include "ExitTokenGenerator.h"

ACC::ExitTokenGenerator::ExitTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::ExitTokenGenerator::generate(ACC::Code &code) {
    if(node->children[0]->op == AstOperator::LITERAL){
        auto exitCode = (temporary)std::stoi(node->children[0]->str);
        auto op = new Operator(OperatorId::IEXIT, exitCode, 0, 0);
        code.pushOp(op);

    } else{ // its a exit with an variable e.g.: " var a = 10; exit a; "
        Dependency& var = code.getVarSymbol(node->children[0]->str);
        auto op = new Operator(OperatorId::EXIT, var.temp, 0, 0);
        op->opLhs = var.op;
        var.op->opResult = op;
        code.pushOp(op);
    }
    return {};
}
