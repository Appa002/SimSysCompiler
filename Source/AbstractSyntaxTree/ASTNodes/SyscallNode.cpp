#include <utility>

#include <utility>

#include "SyscallNode.h"


std::string loadReg(ACC::Code &code, ACC::Register reg, ACC::Structure structure) {
    /*using namespace ACC;

    code.reserveRegister(reg);

    std::string out = structure.copyToRegister( registerToString(8, reg), code);

    code.freeRegister(structure.registerUsed);

    return out;*/
}

std::shared_ptr<ACC::Structure> ACC::SyscallNode::generate(ACC::Code &code) {
  /*  auto &fn = code.getFnSymbol();

    if (node->children.size() >= 1)
        fn.writeLine(loadReg(code, Register::rA, node->children[0]->asExpr()->generate(code)));
    if (node->children.size() >= 2)
        fn.writeLine(loadReg(code, Register::rDI, node->children[1]->asExpr()->generate(code)));
    if (node->children.size() >= 3)
        fn.writeLine(loadReg(code, Register::rSI, node->children[2]->asExpr()->generate(code)));
    if (node->children.size() >= 4)
        fn.writeLine(loadReg(code, Register::rD, node->children[3]->asExpr()->generate(code)));
    if (node->children.size() >= 5)
        fn.writeLine(loadReg(code, Register::r10, node->children[4]->asExpr()->generate(code)));
    if (node->children.size() >= 6)
        fn.writeLine(loadReg(code, Register::r8, node->children[5]->asExpr()->generate(code)));
    if (node->children.size() >= 7)
        fn.writeLine(loadReg(code, Register::r9, node->children[6]->asExpr()->generate(code)));

    if (node->children.size() >= 1)
        code.freeRegister(Register::rA);
    if (node->children.size() >= 2)
        code.freeRegister(Register::rDI);
    if (node->children.size() >= 3)
        code.freeRegister(Register::rSI);
    if (node->children.size() >= 4)
        code.freeRegister(Register::rD);
    if (node->children.size() >= 5)
        code.freeRegister(Register::r10);
    if (node->children.size() >= 6)
        code.freeRegister(Register::r8);
    if (node->children.size() >= 7)
        code.freeRegister(Register::r9);

    fn.writeLine("syscall");

    return {};
    */

    return nullptr;
}

ACC::SyscallNode::SyscallNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(
        op, std::move(children)) {

}
