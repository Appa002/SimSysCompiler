#include "FunctionTokenGenerator.h"

ACC::FunctionTokenGenerator::FunctionTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::FunctionTokenGenerator::generate(ACC::Code &code) {
    FunctionId& fn = code.emplaceFnSymbol(node->children[0]->str);
    auto fnOp = new Operator(OperatorId::FUNCTION, fn.id, 0, 0);
    fn.op = fnOp;
    code.pushOp(fnOp);

    for(size_t i = 1; i < node->children.size() - 1; i++){
        auto& var = code.emplaceVarSymbol(node->children[i]->str, nullptr);
        var.op = fnOp;
        auto op = new Operator(OperatorId::LATTR, (temporary)i, 0, var.temp);

        op->opLhs =fnOp;

        code.pushOp(op);
    }

    node->children[node->children.size() - 1]->asExpr()->generate(code);

    return {};
}
