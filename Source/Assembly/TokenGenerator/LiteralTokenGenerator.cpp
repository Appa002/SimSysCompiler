#include "LiteralTokenGenerator.h"
#include <builtinTypes.h>

ACC::LiteralTokenGenerator::LiteralTokenGenerator(ACC::ASTNode *node) : Expr(node) {

}

void ACC::LiteralTokenGenerator::handleStringLiteral(ACC::Structure &structure, ACC::Code &code, ACC::Fn &fn) {
    structure.type = StructureType ::elementary;
    structure.size = node->data.size();


    fn.curBpOffset += node->data.size();
    fn.writeLine(Movs::imm2bp(node->data, -(offset_t)fn.curBpOffset));
    size_t address = fn.curBpOffset;


    structure.copyToStack = [=](Code& c){
        Register reg = c.getFreeRegister();
        std::string out = "lea " + registerToString(8, reg) + ", [rbp - " + std::to_string(address) + "]";
        out += "\nmov [rsp], " + registerToString(8, reg);
        c.freeRegister(reg);
        return out;
    };

    structure.copyToBpOffset = [=](int32_t offset, Code& c){
        Register reg = c.getFreeRegister();
        std::string sign = offset < 0 ? ("-") : ("+");
        offset = offset < 0 ? (offset * -1) : (offset);
        std::string out = "lea " + registerToString(8, reg) + ", [rbp - " + std::to_string(address) + "]";
        out += "\nmov [rbp " + sign + std::to_string(offset) + "], " + registerToString(8, reg);
        c.freeRegister(reg);
        return out;
    };

    structure.copyToRegister = [=](std::string reg, Code& c){
        return "lea " + reg + ", [rbp - " + std::to_string(address) + "]";
    };

}

ACC::Structure ACC::LiteralTokenGenerator::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();

    auto returnStruct = Structure();
    returnStruct.typeId = node->type;

    if(node->type == BuiltIns::ptrCharType){
        handleStringLiteral(returnStruct, code, fn);
    }
    else if(node->type == BuiltIns::numType){
        handleNumberLiteral(returnStruct, code, fn);
    }

    return returnStruct;
}

void ACC::LiteralTokenGenerator::handleNumberLiteral(ACC::Structure &structure, ACC::Code &code, ACC::Fn &fn) {
    std::string literalEncoded = std::to_string(node->data.createNumber());
    structure.type = StructureType::elementary;
    structure.size = BuiltIns::numType.getSize();
    GeneralDataStore store = node->data; // Copy for lambdas.

    structure.copyToRegister = [=](std::string reg, Code& c){
        return "mov " + reg + ", " + literalEncoded;
    };

    structure.copyToStack = [=](Code& c){
        return Movs::imm2st(store);
    };

    structure.copyToBpOffset = [=](int32_t offset, Code& c){
        return Movs::imm2bp(store, offset);
    };
}
