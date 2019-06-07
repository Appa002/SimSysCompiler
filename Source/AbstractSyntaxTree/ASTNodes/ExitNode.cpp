#include <utility>

#include <builtinTypes.h>
#include <Structure/Structures/ElementaryStructure.h>
#include "ExitNode.h"

std::shared_ptr<ACC::Structure> ACC::ExitNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto* expr = (ElementaryStructure*)children[0]->generate(code);



    expr->loadToRegister(Register::rDI, code);
    fn.writeLine("mov rax, 60");
    fn.writeLine("syscall");

    return {};
}

ACC::ExitNode::ExitNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
