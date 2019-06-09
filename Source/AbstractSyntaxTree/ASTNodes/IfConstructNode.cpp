#include <utility>
#include <Structure/Structures/Bool/BoolRValueStructure.h>

#include "IfConstructNode.h"
#include <Structure/Structures/Bool/BoolStructure.h>


std::shared_ptr<ACC::Structure> ACC::IfConstructNode::generate(ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto final = code.getUUID();
    std::string next;
    if (children.size() == 1)
        next = final;
    else
        next = code.getUUID();

    code.pushScope();
    auto expr = children[0]->children[0]->generate(code);
    auto* exprAsBool = dynamic_cast<BoolStructure*>(expr.get());

    Register reg = code.getFreeRegister();
    exprAsBool->loadToRegister(reg, code);
    fn.writeLine("cmp " + registerToString(1, reg) + ", 1");
    fn.writeLine("jnz ." + next);

    expr->cleanUp(code);
    code.freeRegister(reg);

    code.pushScope();
    auto body = children[0]->children[1]->generate(code);
    code.popScope();
    if(body)
        body->cleanUp(code);

    fn.writeLine("jmp ." + final);
    for (size_t i = 1; i < children.size(); i++) {
        if (children[i]->op == AstOperator::ELIF)
            handleElif(fn, code, i, next, final);
        else
            handleElse(fn, code, i, next);
    }

    fn.writeLine("." + final + ":");
    code.popScope();
    return nullptr;
}

void ACC::IfConstructNode::handleElif(ACC::Fn &fn, ACC::Code &code, size_t idx, std::string &next,
                                      std::string const &final) {
    fn.writeLine("." + next + ":");

    if(children.size() - idx - 1 == 0)
        next = final;
    else
        next = code.getUUID();

    auto condition = children[idx]->children[0]->generate(code);
    auto* conditionAsBool = dynamic_cast<BoolStructure*>(condition.get());

    Register reg = code.getFreeRegister();
    conditionAsBool->loadToRegister(reg, code);
    fn.writeLine("cmp " + registerToString(1, reg) + ", 1");
    fn.writeLine("jnz ." + next);
    condition->cleanUp(code);
    code.freeRegister(reg);

    code.pushScope();
    auto body = children[idx]->children[1]->generate(code);
    code.popScope();
    if(body)
        body->cleanUp(code);

    if(children.size() - idx - 1 != 0)
        fn.writeLine("jmp ." + final);
}

void ACC::IfConstructNode::handleElse(ACC::Fn &fn, ACC::Code &code, size_t idx, std::string &next) {
     code.pushScope();
     fn.writeLine("." + next + ":");
     auto body = children[idx]->children[0]->generate(code);
     code.popScope();
     if(body)
        body->cleanUp(code);
}

ACC::IfConstructNode::IfConstructNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                           std::move(
                                                                                                                   children)) {

}
