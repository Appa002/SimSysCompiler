#include "SubtractTokenGenerator.h"

ACC::SubtractTokenGenerator::SubtractTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::SubtractTokenGenerator::generate(ACC::Code &code){
    auto lhs = node->children[0]->asExpr()->generate(code);
    auto rhs = node->children[1]->asExpr()->generate(code);
    auto& fn = code.getFnSymbol();

    //TODO: Type Conversions.

    auto lhsRegister = code.getFreeRegister();
    auto rhsRegister = code.getFreeRegister();

    if(lhs.type == StructureType::elementary){
        fn.writeLine(lhs.copyToRegister(registerToString(8, lhsRegister), code));
    }

    if(rhs.type == StructureType::elementary){
        fn.writeLine(rhs.copyToRegister(registerToString(8, rhsRegister), code));
    }

    fn.writeLine("sub "+ registerToString(8, lhsRegister) +", "+ registerToString(8, rhsRegister));

    auto return_struct = Structure(StructureType::elementary);
    return_struct.typeId = lhs.typeId;

    return_struct.copyToRegister = [=](std::string reg, Code& c){
        if(reg != "rax")
            return "mov " + reg + ", " + registerToString(8, lhsRegister);
        return std::string();
    };

    return_struct.copyToStack = [=](Code& c){
        return "mov qword [rsp], " + registerToString(8, lhsRegister);
    };

    return_struct.copyToBpOffset = [=](int32_t offset, Code& c){
        std::string sign = offset < 0 ? ("-") : ("+");
        if(offset < 0) offset *= -1;
        std::string offstr = std::to_string(offset);

        return "mov qword [rbp " + sign + offstr + "], " + registerToString(8, lhsRegister);
    };

    code.freeRegister(rhsRegister);
    code.freeRegister(lhs.registerUsed);
    code.freeRegister(rhs.registerUsed);
    return_struct.registerUsed = {lhsRegister};

    return return_struct;
}
