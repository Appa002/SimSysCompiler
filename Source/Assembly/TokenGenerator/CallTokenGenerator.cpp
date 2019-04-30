#include "CallTokenGenerator.h"

ACC::CallTokenGenerator::CallTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::CallTokenGenerator::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    for(size_t i = 1; i < node->children.size(); i++){
        auto value = node->children[i]->asExpr()->generate(code);
        fn.writeLine("sub rsp, 8");
        fn.writeLine(value.copyToStack());
    }

    fn.writeLine("call " + node->children[0]->data.asT<std::string>());

    auto out = Structure(StructureType::elementary);
    out.copyToRegister = [](std::string reg){
        if(reg != "rax")
            return "mov " + reg + " , rax";
        return std::string();
    };

    out.copyToStack = [](){
        return "mov qword [rsp], rax";
    };


    out.size = 8;

    return out;
}
