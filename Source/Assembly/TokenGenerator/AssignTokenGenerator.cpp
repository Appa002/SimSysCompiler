#include "AssignTokenGenerator.h"

ACC::Structure ACC::AssignTokenGenerator::generate(ACC::Code &code) {
    auto id = node->children[0]->data.asT<std::string>();
    auto expr = node->children[1]->asExpr()->generate(code);

    code.emplaceVarSymbol(id, expr);
    return {};
}

ACC::AssignTokenGenerator::AssignTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}
