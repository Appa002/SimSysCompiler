#include <utility>
#include <Structure/Structures/ElementaryStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Structure/Structures/User/UserLValueStructure.h>

#include "ReturnNode.h"

std::shared_ptr<ACC::Structure> ACC::ReturnNode::generate(ACC::Code &code) {
    auto returnValue = children[0]->generate(code);
    auto &fn = code.getFnSymbol();

    auto* asElem = dynamic_cast<ElementaryStructure*>(returnValue.get());
    if(asElem) {
        asElem->loadToRegister(Register::rA, code);
        fn.writeLine("mov rsp, rbp");
        fn.writeLine("pop rbp");
        fn.writeLine("ret");
    } else{
        code.reserveRegister(Register::rDI);

        fn.writeLine("mov rdi, [rbp - 8]");

        std::make_shared<UserLValueStructure>("rdi", returnValue->type)->operatorCopy(returnValue, code);

        fn.writeLine("mov rsp, rbp");
        fn.writeLine("pop rbp");
        fn.writeLine("ret");

        code.freeRegister(Register::rDI);

    }
    returnValue->cleanUp(code);

    return nullptr;
}

ACC::ReturnNode::ReturnNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                 std::move(children)) {

}
