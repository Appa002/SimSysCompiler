#include <utility>

#include <utility>

#include "LiteralNode.h"
#include <General/builtinTypes.h>
#include <Structure/Structures/NumIValueStructure.h>
#include <Assembly/DataStructureMovement.h>
#include <Structure/Structures/PtrRValueStructure.h>


std::string ACC::LiteralNode::handleStringLiteral(ACC::Code &code, ACC::Fn &fn) {
    size_t count = 0;
    for(size_t i = 0; i < data.size(); i++){
        if(count == 4)
            count = 0;
        count++;
    }
    if(count == 3)
        data.push(0x00);


    fn.curBpOffset += data.size();
    fn.writeLine(Movs::imm2bp(data, -(offset_t)fn.curBpOffset));
    return "rbp - " + std::to_string(fn.curBpOffset);
}

std::shared_ptr<ACC::Structure> ACC::LiteralNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    std::shared_ptr<Structure> out;

    if(this->type == BuiltIns::ptrCharType){
        std::string address = handleStringLiteral(code, fn);
        out = std::make_shared<PtrRValueStructure>(address);
    }
    else if(this->type == BuiltIns::numType){
        out = std::make_shared<NumIValueStructure>(data.createNumber());
    }

    return out;
}

void ACC::LiteralNode::handleNumberLiteral(std::shared_ptr<Structure> &structure, ACC::Code &code, ACC::Fn &fn) {
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

ACC::LiteralNode::LiteralNode(ACC::AstOperator op, ACC::GeneralDataStore literal, ACC::TypeId type) :
ASTNode(op, std::move(literal), type) {

}