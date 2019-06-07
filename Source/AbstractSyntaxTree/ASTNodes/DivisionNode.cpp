#include <utility>

#include "DivisionNode.h"

std::shared_ptr<ACC::Structure> ACC::DivisionNode::generate(ACC::Code &code) {
    /*auto lhs = node->children[0]->asExpr()->generate(code);
    auto rhs = node->children[1]->asExpr()->generate(code);
    auto& fn = code.getFnSymbol();

    //TODO: Type Conversions.

    if(!(code.isRegisterFree(Register::rD) && code.isRegisterFree(Register::rA) && code.isRegisterFree(Register::rC)))
        throw std::runtime_error("Division needs register rdx, rax and rcx");

    code.reserveRegister(Register::rD);
    code.reserveRegister(Register::rA);
    code.reserveRegister(Register::rC);

    fn.writeLine("mov rdx, 0");

    if(lhs.type == StructureType::elementary){
        fn.writeLine(lhs.copyToRegister("rax", code));
    }

    if(rhs.type == StructureType::elementary){
        fn.writeLine(rhs.copyToRegister("rcx", code));
    }

    fn.writeLine("div rcx");

    auto return_struct = Structure(StructureType::elementary);
    return_struct.typeId = lhs.typeId;

    return_struct.copyToRegister = [=](std::string reg, Code& c){
        if(reg != "rax")
            return "mov " + reg + ", rax";
        return std::string();
    };

    return_struct.copyToStack = [=](Code& c){
        return "mov qword [rsp], rax";
    };

    return_struct.copyToBpOffset = [=](int32_t offset, Code& c){
        std::string sign = offset < 0 ? ("-") : ("+");
        if(offset < 0) offset *= -1;
        std::string offstr = std::to_string(offset);

        return "mov qword [rbp " + sign + offstr + "], rax";
    };


    code.freeRegister(Register::rD);
    code.freeRegister(Register::rC);
    code.freeRegister(lhs.registerUsed);
    code.freeRegister(rhs.registerUsed);

    return_struct.registerUsed = {Register::rA};

    return return_struct;
*/
    return nullptr;
}

ACC::DivisionNode::DivisionNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                     std::move(children)) {

}
