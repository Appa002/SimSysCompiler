#include <utility>

#include <utility>

#include "LiteralNode.h"
#include <General/builtinTypes.h>
#include <Structure/Structures/Number/NumIValueStructure.h>
#include <Assembly/DataStructureMovement.h>
#include <Structure/Structures/CharPointer/PtrRValueStructure.h>


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

    if(this->type == BuiltIns::ptrType && this->type.getPointingTo() == BuiltIns::charType){
        std::string address = handleStringLiteral(code, fn);
        out = std::make_shared<PtrRValueStructure>(address, Type(this->type.getPointingTo()));
    }
    else if(this->type == BuiltIns::numType){
        out = std::make_shared<NumIValueStructure>(data.createNumber());
    }

    return out;
}

ACC::LiteralNode::LiteralNode(ACC::AstOperator op, ACC::GeneralDataStore literal, ACC::Type type) :
ASTNode(op, std::move(literal), type) {

}