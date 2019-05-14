#include "AssignTokenGenerator.h"



ACC::Structure ACC::AssignTokenGenerator::generate(ACC::Code &code) {
    auto id = node->children[0]->data.asT<std::string>();
    auto type = node->children[1]->data.asT<TypeId>();
    auto expr = node->children[2]->asExpr()->generate(code);

    //TODO: Type Conversions.
    expr.typeId = type;

    code.emplaceVarSymbol(id, expr);

    return {};
}

ACC::AssignTokenGenerator::AssignTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}