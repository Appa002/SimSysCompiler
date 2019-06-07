#include <utility>
#include <Structure/Structures/NumLValueStructure.h>

#include "AssignNode.h"
#include <memory>



std::shared_ptr<ACC::Structure> ACC::AssignNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();

    auto id  =  children[0]->data.asT<std::string>();
    auto type = children[1]->data.asT<TypeId>();
    auto expr = children[2]->generate(code);

    fn.curBpOffset += expr->type.getSize();

    std::shared_ptr<NumLValueStructure> address = std::make_shared<NumLValueStructure>("rbp - " + std::to_string(fn.curBpOffset));
    expr->operatorCopy(address, code);

    code.emplaceVarSymbol(id, address);
    return nullptr;

    /*   auto id = node->children[0]->data.asT<std::string>();
       auto type = node->children[1]->data.asT<TypeId>();
       auto expr = node->children[2]->asExpr()->generate(code);

       //TODO: Type Conversions.
       expr.typeId = type;

       if(!expr.isStored){
           auto& fn = code.getFnSymbol();
           fn.curBpOffset += expr.typeId.getSize();
           fn.writeLine(expr.copyToBpOffset(-fn.curBpOffset, code));
           expr.copyToBpOffset = [=](int32_t offset, Code& c){
               Register reg = c.getFreeRegister();
               std::string sign = offset < 0 ? ("-") : ("+");
               offset = offset < 0 ? (offset * -1) : (offset);
               std::string out = "mov " + registerToString(expr.typeId.getSize(), reg) + ", [rbp - " + std::to_string(fn.curBpOffset) + "]";
               out += "\nmov [rbp " + sign + std::to_string(offset) + "], " + registerToString(expr.typeId.getSize(), reg);
               c.freeRegister(reg);
               return out;
           };

           expr.copyToStack = [=](Code& c){
               Register reg = c.getFreeRegister();
               std::string out = "mov " + registerToString(expr.typeId.getSize(), reg) + ", [rbp - " + std::to_string(fn.curBpOffset) + "]";
               out += "\nmov [rsp], " + registerToString(expr.typeId.getSize(), reg);
               c.freeRegister(reg);
               return out;
           };

           expr.copyToRegister = [=](std::string reg, Code& c){
               return "mov " + reg + ", [rbp - " + std::to_string(fn.curBpOffset) + "]";
           };

           expr.copyAddrToRegister = [=](std::string reg, Code& c){
               return "lea " + reg + ", [rbp - " + std::to_string(fn.curBpOffset) + "]";
           };


       }

       code.emplaceVarSymbol(id, expr);

       return {};
       */
    return nullptr;
}

ACC::AssignNode::AssignNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
