#include "ExitTokenGenerator.h"

ACC::ExitTokenGenerator::ExitTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::ExitTokenGenerator::generate(ACC::Code &code) {
    if(node->children[0]->op == AstOperator::LITERAL){
        if(node->children[0]->dataKind != ASTNodeDataType::NUMBER)
            throw std::runtime_error("Keyword `exit` needs to be called with an expression evaluating to a nummer or with"
                                     "a literal, that is a number.");

        auto& fn = code.getFnSymbol();
        fn.writeLine("mov rax, 60");
        fn.writeLine("mov rdi, " + std::to_string(node->children[0]->data.createNumber()));
        fn.writeLine("syscall");
    }
    //TODO: Program case where rhs isn't a literal e.g. exit 5 + 5;
    return {};
}
