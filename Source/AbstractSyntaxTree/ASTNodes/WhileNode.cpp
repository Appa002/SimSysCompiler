#include <utility>

#include "WhileNode.h"
#include <General/builtinTypes.h>
#include <Structure/Structures/Bool/BoolRValueStructure.h>

std::shared_ptr<ACC::Structure> ACC::WhileNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();

    auto top = code.getUUID();
    auto rest = code.getUUID();

    fn.writeLine("."+top+":");
    auto condition = children[0]->generate(code);
    auto conditionAsBool = dynamic_cast<BoolRValueStructure*>(condition.get());

    Register reg = code.getFreeRegister();
    conditionAsBool->loadToRegister(reg, code);

    fn.writeLine("cmp " + registerToString(1, reg) + ", 1");
    fn.writeLine("jne ." + rest);

    code.freeRegister(reg);

    code.pushScope();
    auto body = children[1]->generate(code);
    code.popScope();

    fn.writeLine("jmp ." + top);

    fn.writeLine("."+rest+":");

    return nullptr;
}

ACC::WhileNode::WhileNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children)
: ASTNode(op,std::move(children)) {

}
