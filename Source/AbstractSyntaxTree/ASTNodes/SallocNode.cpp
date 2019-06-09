#include <utility>
#include <Structure/Structures/ElementaryStructure.h>
#include <Structure/Structures/Pointer/PtrStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>

#include "SallocNode.h"

ACC::SallocNode::SallocNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}

std::shared_ptr<ACC::Structure> ACC::SallocNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto size = children[0]->generate(code);
    auto sizeAsElementary = dynamic_cast<ElementaryStructure*>(size.get());
    Register reg = code.getFreeRegister();
    sizeAsElementary->loadToRegister(reg, code);
    fn.writeLine("sub rsp, " + registerToString(size->type.getSize(), reg));
    fn.writeLine("lea " + registerToString(8, reg) + ", [rsp]");

    auto var = code.getVarSymbol(children[1]->data.asT<std::string>());
    auto ptr = std::make_shared<PtrRValueStructure>(reg, Type(var->type.getPointingTo()));

    ptr->operatorCopy(var, code);

    size->cleanUp(code);
    code.freeRegister(reg);
    ptr->cleanUp(code);

    return nullptr;
}
