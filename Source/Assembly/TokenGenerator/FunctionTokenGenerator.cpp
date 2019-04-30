#include "FunctionTokenGenerator.h"

ACC::FunctionTokenGenerator::FunctionTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::FunctionTokenGenerator::generate(ACC::Code &code) {
    auto& fn = code.emplaceFnSymbol(node->children[0]->data.asT<std::string>());

    for(size_t i = 1; i < node->children.size() - 1; i++){

        auto structure = Structure(StructureType::elementary);
        structure.size = 8;

        std::string offset = std::to_string(16 + 8 * (i- 1));

        structure.copyAddressToRegister = [=](std::string reg){
            return "lea " + reg + ", [rbp + "+offset+"]";
        };
        structure.copyAddressToStack = [=](){
            return "sub rsp, 8\n"
                   "lea [rsp], [rbp + "+offset+"]";
        };
        structure.copyToRegister = [=](std::string reg){
            return "mov " + reg + "[rbp + "+offset+"]";
        };
        structure.copyToStack = [=](){
            return "mov rax, [rbp + "+offset+"]\n"
                   "mov [rsp], rax";
        };

        code.emplaceVarSymbol(node->children[i]->data.asT<std::string>(), structure);
        fn.curBpOffset += 8;
    }

    node->children.at(node->children.size() - 1)->asExpr()->generate(code);

    return {};
}
