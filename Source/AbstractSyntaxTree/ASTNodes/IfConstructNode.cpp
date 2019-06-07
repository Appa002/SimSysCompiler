#include <utility>

#include "IfConstructNode.h"


ACC::Structure* ACC::IfConstructNode::generate(ACC::Code &code) {
   /* auto &fn = code.getFnSymbol();
    auto final = code.getUUID();
    std::string next;
    if(node->children.size() == 1)
        next = final;
    else
        next = code.getUUID();

    code.pushScope();
    auto expr = node->children[0]->children[0]->asExpr()->generate(code);

    Register reg;
    if(!expr.registerUsed.empty())
        reg = expr.registerUsed[0];
    else
        reg = code.getFreeRegister();

    fn.writeLine(expr.copyToRegister(registerToString(1, reg), code));
    fn.writeLine("cmp " + registerToString(1, reg) + ", 1");
    fn.writeLine("jnz ." + next);

    code.freeRegister(expr.registerUsed);
    code.freeRegister(reg);

    code.pushScope();
    node->children[0]->children[1]->asExpr()->generate(code);
    code.popScope();
    if(!node->children.empty()){
        fn.writeLine("jmp ." + final);
        for(size_t i = 1; i < node->children.size(); i++){
            if(node->children[i]->op == AstOperator::ELIF)
                handleElif(fn, code, i, next, final);
            else
                handleElse(fn, code, i, next);
        }
    }

    fn.writeLine("." + final + ":");


    code.popScope();
    return {};
    */
    return nullptr;
}

void ACC::IfConstructNode::handleElif(ACC::Fn &fn, ACC::Code &code, size_t idx, std::string &next,
                                                std::string const &final) {
    /*fn.writeLine("." + next + ":");

    if(node->children.size() - idx - 1 == 0)
        next = final;
    else
        next = code.getUUID();

    auto condition = node->children[idx]->children[0]->asExpr()->generate(code);

    Register reg;
    if(!condition.registerUsed.empty())
        reg = condition.registerUsed[0];
    else
        reg = code.getFreeRegister();

    fn.writeLine(condition.copyToRegister(registerToString(1, reg), code));
    fn.writeLine("cmp " + registerToString(1, reg) + ", 1");
    fn.writeLine("jnz ." + next);

    code.freeRegister(condition.registerUsed);
    code.freeRegister(reg);
    code.pushScope();
    node->children[idx]->children[1]->asExpr()->generate(code);
    code.popScope();
    if(node->children.size() - idx - 1 != 0)
        fn.writeLine("jmp ." + final);
        */
}

void ACC::IfConstructNode::handleElse(ACC::Fn &fn, ACC::Code &code, size_t idx, std::string &next) {
   /* code.pushScope();
    fn.writeLine("." + next + ":");
    node->children[idx]->children[0]->asExpr()->generate(code);
    code.popScope();
    */
}

ACC::IfConstructNode::IfConstructNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                           std::move(
                                                                                                                   children)) {

}
