#include <utility>

#include <utility>
#include <Structure/Structures/ElementaryStructure.h>

#include "SyscallNode.h"


void loadReg(ACC::Code &code, ACC::Register reg, const std::shared_ptr<ACC::Structure> &structure) {
    using namespace ACC;

    auto* structureAsElementary = dynamic_cast<ElementaryStructure*>(structure.get());
    code.reserveRegister(reg);

    structureAsElementary->loadToRegister(reg, code);
    structure->cleanUp(code);
}

std::shared_ptr<ACC::Structure> ACC::SyscallNode::generate(ACC::Code &code) {
    auto &fn = code.getFnSymbol();

    if (children.size() >= 1)
        loadReg(code, Register::rA, children[0]->generate(code));
    if (children.size() >= 2)
        loadReg(code, Register::rDI, children[1]->generate(code));
    if (children.size() >= 3)
        loadReg(code, Register::rSI, children[2]->generate(code));
    if (children.size() >= 4)
        loadReg(code, Register::rD, children[3]->generate(code));
    if (children.size() >= 5)
        loadReg(code, Register::r10, children[4]->generate(code));
    if (children.size() >= 6)
        loadReg(code, Register::r8, children[5]->generate(code));
    if (children.size() >= 7)
        loadReg(code, Register::r9, children[6]->generate(code));

    if (children.size() >= 1)
        code.freeRegister(Register::rA);
    if (children.size() >= 2)
        code.freeRegister(Register::rDI);
    if (children.size() >= 3)
        code.freeRegister(Register::rSI);
    if (children.size() >= 4)
        code.freeRegister(Register::rD);
    if (children.size() >= 5)
        code.freeRegister(Register::r10);
    if (children.size() >= 6)
        code.freeRegister(Register::r8);
    if (children.size() >= 7)
        code.freeRegister(Register::r9);

    fn.writeLine("syscall");
    
    return nullptr;
}

ACC::SyscallNode::SyscallNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(
        op, std::move(children)) {

}
