#include "DivisionTokenGenerator.h"

ACC::DivisionTokenGenerator::DivisionTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::DivisionTokenGenerator::generate(ACC::Code &code) {
    auto lhs = node->children[0]->asExpr()->generate(code);
    auto rhs = node->children[1]->asExpr()->generate(code);
    auto& fn = code.getFnSymbol();

    if(!(code.isRegisterFree(Register::rD) && code.isRegisterFree(Register::rA) && code.isRegisterFree(Register::rC)))
        throw std::runtime_error("Division needs register rdx, rax and rcx");

    code.reserveRegister(Register::rD);
    code.reserveRegister(Register::rA);
    code.reserveRegister(Register::rC);

    fn.writeLine("mov rdx, 0");

    if(lhs.type == StructureType::elementary){
        fn.writeLine(lhs.copyToRegister("rax"));
    }

    if(rhs.type == StructureType::elementary){
        fn.writeLine(rhs.copyToRegister("rcx"));
    }

    fn.writeLine("div rcx");

    auto return_struct = Structure(StructureType::elementary);

    return_struct.copyToRegister = [=](std::string reg){
        if(reg != "rax")
            return "mov " + reg + ", rax";
        return std::string();
    };

    return_struct.copyToStack = [=](){
        return "mov qword [rsp], rax";
    };


    code.freeRegister(Register::rD);
    code.freeRegister(Register::rC);
    code.freeRegister(lhs.registerUsed);
    code.freeRegister(rhs.registerUsed);

    return_struct.registerUsed = {Register::rA};

    return return_struct;
}
