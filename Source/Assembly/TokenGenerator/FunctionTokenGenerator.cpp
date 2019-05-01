#include "FunctionTokenGenerator.h"

ACC::FunctionTokenGenerator::FunctionTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::FunctionTokenGenerator::generate(ACC::Code &code) {
    auto& fn = code.emplaceFnSymbol(node->children[0]->data.asT<std::string>());

    for(size_t i = 1; i < node->children.size() - 1; i++){

        auto structure = Structure(StructureType::elementary);
        structure.size = 8;

        std::string offset = std::to_string(16 + 8 * (i- 1));

        structure.copyAddressToRegister = [=](std::string reg, Code& c){
            return "lea " + reg + ", [rbp + "+offset+"]";
        };
        structure.copyAddressToStack = [=](Code& c){
            return "sub rsp, 8\n"
                   "lea [rsp], [rbp + "+offset+"]";
        };
        structure.copyToRegister = [=](std::string reg, Code& c){
            return "mov " + reg + "[rbp + "+offset+"]";
        };
        structure.copyToStack = [=](Code& c){
            return "mov rax, [rbp + "+offset+"]\n"
                   "mov [rsp], rax";
        };

        structure.copyToBpOffset = [=](int32_t off, Code& c){
            Register reg = c.getFreeRegister();
            std::string regStr = registerToString(8, reg);
            c.freeRegister(reg);

            std::string sign = off < 0 ? ("-") : ("+");
            if(off < 0) off *= -1;
            std::string offstr = std::to_string(off);

            return "mov " + regStr + "[rbp + " + offset +"]\n"
                   "mov qword [rbp " + sign + offstr + "], " + regStr;
        };

        code.emplaceVarSymbol(node->children[i]->data.asT<std::string>(), structure);
        fn.curBpOffset += 8;
    }

    node->children.at(node->children.size() - 1)->asExpr()->generate(code);

    return {};
}
