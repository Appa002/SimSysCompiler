#include <utility>

#include <utility>

#include "LiteralNode.h"
#include <Structure/Structures/Number/NumIValueStructure.h>
#include <Assembly/DataStructureMovement.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Structure/Structures/Char/CharIValueStructure.h>
#include <Types/Type.h>
#include <General/utils.h>

std::string ACC::LiteralNode::handleStringLiteral(ACC::Code &code, ACC::Fn &fn) {
    size_t count = 0;
    for(size_t i = 0; i < literal.size(); i++){
        if(count == 4)
            count = 0;
        count++;
    }
    if(count == 3)
        literal.push(0x00);


    fn.curBpOffset += literal.size();
    fn.writeLine(Movs::imm2bp(literal, -(offset_t)fn.curBpOffset));
    return "rbp - " + std::to_string(fn.curBpOffset);
}

std::shared_ptr<ACC::Structure> ACC::LiteralNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    std::shared_ptr<Structure> out;

    if(this->type == Type::createPtr("char")){
        std::string address = handleStringLiteral(code, fn);
        out = std::make_shared<PtrRValueStructure>(address, Type(this->type));
    }
    else if(this->type == Type("num", 8)){
        out = std::make_shared<NumIValueStructure>(literal.createNumber());
    } else if(this->type == Type("char", 1)){
        out = std::make_shared<CharIValueStructure>(literal.createNumber());
    }

    return out;
}

ACC::LiteralNode::LiteralNode(ACC::AstOperator op, ACC::GeneralDataStore literal, ACC::Type type) :
ASTNode(op, {}), literal(std::move(literal)), type(std::move(type)) {

}

std::string ACC::LiteralNode::createRepresentation() const {
    if(type == Type("num", 8) || type == Type("char" , 1))
        return "Lit: " + std::to_string(literal.createNumber());
    else if(type == Type::createPtr("char"))
        return std::string("Lit: ") + "\"" + literal.asT<std::string>() +"\"";
    else{
        std::string data = "[ ";
        for(size_t i = 0; i < this->literal.size(); i++){
            data += " `" + toHex(data.at(i)) + "`";
            if(i + 1 < data.size())
                data += ",";
        }
        data += " ]";

        return "Lit (Complex) " + data;
    }

}
