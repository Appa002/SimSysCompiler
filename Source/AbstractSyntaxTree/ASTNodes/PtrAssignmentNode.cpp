#include <utility>
#include <Structure/Structures/Pointer/PtrStructure.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>
#include <Structure/Structures/Char/CharRValueStructure.h>
#include <Error/ASTError.h>

#include "PtrAssignmentNode.h"
#include <Types/TypeTable.h>

ACC::PtrAssignmentNode::PtrAssignmentNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                               std::move(
                                                                                                                       children)) {

}

std::shared_ptr<ACC::Structure> ACC::PtrAssignmentNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();


    auto subject = children[0]->generate(code);
    auto expr = children[1]->generate(code);

    Register reg = code.getFreeRegister();

    auto ptr = dynamic_cast<PtrStructure*>(subject.get());

    ptr->loadToRegister(reg, code);

    auto address = std::make_shared<GenericLValueStructure>(Type(ptr->type.id, TypeTable::get()->getSize(ptr->type.id)), registerToString(8, reg));

    try {
        address->operatorCopy(expr, code);
    }catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }
    subject->cleanUp(code);
    expr->cleanUp(code);
    code.freeRegister(reg);

    return nullptr;
}
