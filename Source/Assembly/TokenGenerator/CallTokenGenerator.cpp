#include "CallTokenGenerator.h"

ACC::CallTokenGenerator::CallTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::CallTokenGenerator::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    for(size_t i = 1; i < node->children.size(); i++){
        auto value = node->children[i]->asExpr()->generate(code);
        fn.writeLine("sub rsp, 8");
        fn.writeLine(value.copyToStack(code));
    }

    fn.writeLine("call " + node->children[0]->data.asT<std::string>());
    code.reserveRegister(Register::rA);

    auto out = Structure(StructureType::elementary);
    out.copyToRegister = [](std::string reg, Code& c){
        if(reg != "rax")
            return "mov " + reg + " , rax";
        return std::string();
    };

    out.copyToStack = [](Code& c){
        return "mov qword [rsp], rax";
    };

    out.copyToBpOffset = [=](int32_t offset, Code& c){
        std::string sign = offset < 0 ? ("-") : ("+");
        if(offset < 0) offset *= -1;
        std::string offstr = std::to_string(offset);

        return "mov qword [rbp " + sign + offstr + "], rax";
    };


    out.size = 8;

    return out;
}
