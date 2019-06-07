#include "LiteralTokenGenerator.h"
#include <builtinTypes.h>


void ACC::LiteralTokenGenerator::handleStringLiteral(ACC::Structure &structure, ACC::Code &code, ACC::Fn &fn) {
   /* structure.type = StructureType ::elementary;

    size_t count = 0;
    for(size_t i = 0; i < node->data.size(); i++){
        if(count == 4)
            count = 0;
        count++;
    }
    if(count == 3)
        node->data.push(0x00);


    fn.curBpOffset += node->data.size();
    fn.writeLine(Movs::imm2bp(node->data, -(offset_t)fn.curBpOffset));
    size_t address = fn.curBpOffset;

    structure.isStored = false;

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
*/
}

ACC::Structure* ACC::LiteralTokenGenerator::generate(ACC::Code &code) {
    /*auto& fn = code.getFnSymbol();

    auto returnStruct = Structure();
    returnStruct.typeId = node->type;

    if(node->type == BuiltIns::ptrCharType){
        handleStringLiteral(returnStruct, code, fn);
    }
    else if(node->type == BuiltIns::numType){
        handleNumberLiteral(returnStruct, code, fn);
    }

    return returnStruct;*/
    return nullptr;
}

void ACC::LiteralTokenGenerator::handleNumberLiteral(ACC::Structure &structure, ACC::Code &code, ACC::Fn &fn) {
  /*  std::string literalEncoded = std::to_string(node->data.createNumber());
    structure.type = StructureType::elementary;
    structure.isStored = false;

    size_t count = 0;
    for(size_t i = 0; i < node->data.size(); i++){
        if(count == 4)
            count = 0;
        count++;
    }
    if(count == 3)
        node->data.push(0x00);



    GeneralDataStore store = node->data; // Copy for lambdas.
    if(store.size() >= 3){
        size_t alignmentChange = 4 - store.size() % 4;
        auto& data = store.data();
        for(size_t i = 0; i < alignmentChange; i++)
            store.push((uint8_t)0x00);
    }


    structure.copyToRegister = [=](std::string reg, Code& c){
        return "mov " + reg + ", " + literalEncoded;
    };

    structure.copyToStack = [=](Code& c){
        return Movs::imm2st(store);
    };

    structure.copyToBpOffset = [=](int32_t offset, Code& c){
        return Movs::imm2bp(store, offset);
    };
    */
}
