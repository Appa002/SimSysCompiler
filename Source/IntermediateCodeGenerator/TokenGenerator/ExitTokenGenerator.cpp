#include "ExitTokenGenerator.h"

ACC::ExitTokenGenerator::ExitTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Dependency ACC::ExitTokenGenerator::generate(ACC::Code &code) {
    auto exitCode = (temporary)std::stoi(node->children[0]->str);
    auto op = new Operator(OperatorId::EXIT, exitCode, 0, 0);
    code.pushOp(op);
    return {};
}
