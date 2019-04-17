#include "CallTokenGenerator.h"

ACC::CallTokenGenerator::CallTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::CallTokenGenerator::generate(ACC::Code &code) {
    FunctionId& fn = code.getFnSymbol(node->children[0]->str);

    auto op = new Operator(OperatorId::ICALL, fn.id, 0, 0);
    op->opLhs = fn.op;

    for(size_t i = 1; i < node->children.size(); i++){
        if(node->children[i]->op == AstOperator::LITERAL)
            code.pushOp(new Operator(OperatorId::ISATTR, (temporary)std::stoi(node->children[i]->str), (temporary)i, 0));

        else {
            auto var = node->children[i]->asExpr()->generate(code);
            auto loadOp = new Operator(OperatorId::SATTR, var.temp, (temporary)i, 0);
            loadOp->opLhs = var.op;
            code.pushOp(loadOp);
        }
    }

    code.pushOp(op);

    return {};
}
