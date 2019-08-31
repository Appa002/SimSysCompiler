#include <utility>
#include <Structure/Structures/ElementaryStructure.h>
#include <Structure/Structures/Pointer/PtrStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Error/ASTError.h>

#include "SallocNode.h"
#include "IdNode.h"

ACC::SallocNode::SallocNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}

std::shared_ptr<ACC::Structure> ACC::SallocNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto size = children[0]->generate(code);
    auto sizeAsElementary = dynamic_cast<ElementaryStructure*>(size.get());
    Register reg = code.getFreeRegister();
    sizeAsElementary->loadToRegister(reg, code);
    fn.writeLine("sub rsp, " + registerToString(size->type.size, reg));
    fn.writeLine("lea " + registerToString(8, reg) + ", [rsp]");


    auto id = dynamic_cast<IdNode*>(children[1])->sym;
    auto var = code.getVarSymbol(id);
    auto ptr = std::make_shared<PtrRValueStructure>(reg, Type(var->type));

    try {
        var->operatorCopy(ptr, code);
    } catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }
    size->cleanUp(code);
    code.freeRegister(reg);
    ptr->cleanUp(code);

    return nullptr;
}
