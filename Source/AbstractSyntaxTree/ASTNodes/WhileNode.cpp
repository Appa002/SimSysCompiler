#include <utility>

#include "WhileNode.h"
#include <builtinTypes.h>

std::shared_ptr<ACC::Structure> ACC::WhileNode::generate(ACC::Code &code) {
 /*   auto& fn = code.getFnSymbol();

    auto top = code.getUUID();
    auto rest = code.getUUID();

    fn.writeLine("."+top+":");
    auto condition = node->children[0]->asExpr()->generate(code);

    Register reg;
    if(!condition.registerUsed.empty())
        reg = condition.registerUsed[0];
    else
        reg = code.getFreeRegister();

    fn.writeLine(condition.copyToRegister(registerToString(1, reg), code));
    fn.writeLine("cmp " + registerToString(1, reg) + ", 1");
    fn.writeLine("jnz ." + rest);

    code.freeRegister(reg);
    code.freeRegister(condition.registerUsed);

    code.pushScope();
    auto body = node->children[1]->asExpr()->generate(code);
    code.popScope();

    fn.writeLine("jmp ." + top);

    fn.writeLine("."+rest+":");
    code.freeRegister(body.registerUsed);

    return {};*/
    return nullptr;
}

ACC::WhileNode::WhileNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children)
: ASTNode(op,std::move(children)) {

}
