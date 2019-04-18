#include "ReturnTokenGenerator.h"

ACC::ReturnTokenGenerator::ReturnTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::ReturnTokenGenerator::generate(ACC::Code &code) {
    if(node->children[0]->op == AstOperator::LITERAL){
        auto op = new Operator(OperatorId::IRETURN, (temporary)std::stoi(node->children[0]->str), 0, 0);
        code.pushOp(op);
        return {};

    }else {
        Dependency var = node->children[0]->asExpr()->generate(code);

        auto op = new Operator(OperatorId::RETURN, var.temp, 0, 0);
        op->opLhs = var.op;
        code.pushOp(op);
        return {};
    }

    throw std::runtime_error("Broken Return");
}
