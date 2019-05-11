#include "LiteralTokenGenerator.h"
#include <builtinTypes.h>

ACC::LiteralTokenGenerator::LiteralTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::LiteralTokenGenerator::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    size_t address = fn.curBpOffset;

    /* Return structure setup... */
    auto returnStruct = Structure();
    returnStruct.typeId = node->type;

    std::string literalEncoded; // We need to encode the literal as a string while taking types into account;
    //e.g. 100 as char and num would yield "d" and "100" respectively.

    if(node->type == BuiltIns::ptrCharType){
        returnStruct.type = StructureType::complex;
        returnStruct.size = node->data.size();
    }
    else if(node->type == BuiltIns::numType){
        literalEncoded = std::to_string(node->data.createNumber());
        returnStruct.type = StructureType::elementary;
        returnStruct.size = BuiltIns::numType.getSize();
    }


    if(returnStruct.type == StructureType::complex){
        /* If the litearl is complex other code will assume the data has been stored somewhere and can be accessed*/
        fn.writeLine(Movs::imm2bp(node->data, -(offset_t)fn.curBpOffset));
        fn.curBpOffset += node->data.size();
    }

    GeneralDataStore store = node->data; // Copy for lambdas.

    returnStruct.copyToRegister = [=](std::string reg, Code& c){
        return "mov " + reg + ", " + literalEncoded;
    };

    returnStruct.copyToStack = [=](Code& c){
        return Movs::imm2st(store);
    };

    returnStruct.copyToBpOffset = [=](int32_t offset, Code& c){
        return Movs::imm2bp(store, offset);
    };

    returnStruct.copyAddressToRegister = [=](std::string reg, Code& c){
        return "lea " + reg + ", [rbp - " + std::to_string(address) + "]";
    };

    returnStruct.copyAddressToStack = [=](Code& c){
        Register reg = c.getFreeRegister();
        std::string regStr = registerToString(8, reg);
        std::string out = "lea " + regStr + ", [rbp - " +  std::to_string(address) + "]\n";
        out += "mov [rsp], " + regStr;
        return out;
        c.freeRegister(reg);
    };

    returnStruct.copyAddressToBpOffset = [=](int32_t offset, Code& c){
        Register reg = c.getFreeRegister();
        std::string regStr = registerToString(8, reg);
        std::string out = "lea " + regStr + ", [rbp - " +  std::to_string(address) + "]\n";
        std::string sign = offset < 0 ? ("-") : ("+");
        offset = offset < 0 ? (offset * -1) : (offset);
        out += "mov [rbp "+sign + std::to_string(offset) +"], " + regStr;
        return out;
        c.freeRegister(reg);
    };


    return returnStruct;
}
