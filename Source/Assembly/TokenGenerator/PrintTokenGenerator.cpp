#include "PrintTokenGenerator.h"

ACC::PrintTokenGenerator::PrintTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::PrintTokenGenerator::generate(ACC::Code &code) {
    ASTNode* lhs = node->children[0];
    auto& fn = code.getFnSymbol();

    if(lhs->op == AstOperator::LITERAL){
        if(lhs->dataKind != ASTNodeDataType::STRING)
            throw std::runtime_error("Keyword `print` needs to be called with an expression evaluating to a string or with "
                                     "a literal, that is a string.");

        auto string = lhs->data.asT<std::string>();

        offset_t offset = -(fn.curBpOffset + (uint32_t)string.size());
        std::string movCode = Movs::imm2bp(lhs->data, offset);

        fn.curBpOffset += string.size() + 1;

        fn.writeLine(movCode);

        fn.writeLine("lea rsi, [rbp " + std::to_string(offset) + "]");

        fn.writeLine("mov rdx, " + std::to_string(string.size()));
        fn.writeLine("mov rax, 1");
        fn.writeLine("mov rdi, 1");
        fn.writeLine("syscall");
    }else{
        auto lhsStruct = lhs->asExpr()->generate(code);
        fn.writeLine(lhsStruct.copyToStack());
        code.freeRegister(lhsStruct.registerUsed);

        fn.writeLine("mov rsi, rsp");

        fn.writeLine("mov rdx, " + std::to_string(node->children[1]->data.createNumber()));
        fn.writeLine("mov rax, 1");
        fn.writeLine("mov rdi, 1");
        fn.writeLine("syscall");
    }
    return {};
}
