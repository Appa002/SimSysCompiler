#include <utility>
#include <Structure/Structures/Pointer/PtrStructure.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>
#include <Structure/Structures/Char/CharRValueStructure.h>

#include "PtrAssignmentNode.h"

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

    auto address = std::make_shared<GenericLValueStructure>(Type(ptr->type.getPointingTo()), registerToString(8, reg));

    expr->operatorCopy(address, code);

    return nullptr;
}
