#include "LiteralTokenGenerator.h"

ACC::LiteralTokenGenerator::LiteralTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::LiteralTokenGenerator::generate(ACC::Code &code) {
    auto return_struct = Structure(StructureType::elementary);

    std::string literalAsString;
    if(node->dataKind == ASTNodeDataType::STRING){
        literalAsString = node->data.asT<std::string>();
        return_struct.size = literalAsString.size();
    }
    else if(node->dataKind == ASTNodeDataType::NUMBER){
        literalAsString = std::to_string(node->data.createNumber());
        if (node->data.createNumber() < 0x10000) {
            if (node->data.createNumber() < 0x100) // 8 bit
                return_struct.size = 1;
            else // 16 bit
                return_struct.size = 2;
        } else {
            if (node->data.createNumber() < 0x100000000L) // 32 bit
                return_struct.size = 4;
            else // 64 bit
                return_struct.size = 8;
        }
    }

    return_struct.copyToRegister = [=](std::string reg){
        return "mov " + reg + ", " + literalAsString;
    };

    GeneralDataStore store = node->data;
    return_struct.copyToStack = [=](){
        return Movs::imm2st(store);
    };

    return return_struct;
}
