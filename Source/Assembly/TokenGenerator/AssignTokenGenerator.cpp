#include "AssignTokenGenerator.h"

ACC::Structure ACC::AssignTokenGenerator::generate(ACC::Code &code) {
    auto id = node->children[0]->data.asT<std::string>();
    auto expr = node->children[1]->asExpr()->generate(code);
    auto& fn = code.getFnSymbol();
    fn.writeLine(expr.copyToBpOffset(-fn.curBpOffset, code));

    code.freeRegister(expr.registerUsed);

    auto returnStruct = Structure(StructureType::complex);
    returnStruct.size = 8;

    returnStruct.copyToStack = [=](Code& c){
        Register reg = c.getFreeRegister();
        std::string regStr = registerToString(8, reg);
        c.freeRegister(reg);
        return "mov " + regStr + ", [rbp - " + std::to_string(fn.curBpOffset) + "]\n"
               "mov [rsp], " + regStr;

    };

    returnStruct.copyToBpOffset = [=](int32_t offset, Code& c){
        std::string sign = offset < 0 ? ("-") : ("+");
        if(offset < 0) offset *= -1;
        std::string offstr = std::to_string(offset);

        std::string reg = registerToString(8, c.getFreeRegister());
        return "mov " + reg + ", [rbp - " + std::to_string(fn.curBpOffset) + "]"
               "mov [rbp " + offstr + offstr+"], " + reg;
    };

    returnStruct.copyToRegister = [=](std::string reg, Code& c){
        return "mov " + reg + ", [ rbp - " + std::to_string(fn.curBpOffset) + "]";
    };

    returnStruct.copyAddressToStack = [=](Code& c){
        return "lea [rsp], [rbp - " + std::to_string(fn.curBpOffset) + "]\n";
    };

    returnStruct.copyAddressToRegister = [=](std::string reg, Code& c){
        return "lea "+reg+", [rbp - " + std::to_string(fn.curBpOffset) + "]\n";
    };


    returnStruct.copyAddressToBpOffset = [=](int32_t offset, Code& c){
        std::string sign = offset < 0 ? ("-") : ("+");
        if(offset < 0) offset *= -1;
        std::string offstr = std::to_string(offset);

        return "lea [rbp" + sign + offstr + "], [rbp - " + std::to_string(fn.curBpOffset) + "]";
    };

    returnStruct.copyToRegister = [=](std::string reg, Code& c){
        return "lea " + reg + ", [ rbp - " + std::to_string(fn.curBpOffset) + "]";
    };

    fn.curBpOffset += 8;
    code.emplaceVarSymbol(id, returnStruct);
    return {};
}

ACC::AssignTokenGenerator::AssignTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}