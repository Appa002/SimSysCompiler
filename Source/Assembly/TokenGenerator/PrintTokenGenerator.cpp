#include "PrintTokenGenerator.h"

ACC::PrintTokenGenerator::PrintTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::PrintTokenGenerator::generate(ACC::Code &code) {
    ASTNode *lhs = node->children[0];
    auto &fn = code.getFnSymbol();
    auto lhsStruct = lhs->asExpr()->generate(code);

    if(lhsStruct.type == StructureType::elementary){
        fn.writeLine(lhsStruct.copyToStack(code));
        fn.writeLine("mov rsi, rsp");

    }else if(lhsStruct.type == StructureType::complex){
        fn.writeLine(lhsStruct.copyAddressToRegister("rsi", code));
    }

    fn.writeLine("mov rdx, " + std::to_string(node->children[1]->data.createNumber()));
    fn.writeLine("mov rax, 1");
    fn.writeLine("mov rdi, 1");
    fn.writeLine("syscall");

    code.freeRegister(lhsStruct.registerUsed);

    return {};
}
