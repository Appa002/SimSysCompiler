#include <utility>
#include <Structure/Structures/Number/NumLValueStructure.h>

#include "AssignNode.h"
#include "IdNode.h"
#include "TypeNode.h"
#include <memory>
#include <Structure/Structures/GenericLValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Error/ASTError.h>
#include <Structure/Structures/Bool/BoolLValueStructure.h>
#include <Structure/Structures/User/UserStructure.h>


std::shared_ptr<ACC::Structure> ACC::AssignNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();

    auto id  = dynamic_cast<IdNode*>(children[0])->sym;
    auto type = dynamic_cast<TypeNode*>(children[1])->getType();
    auto expr = children[2]->generate(code);

    fn.curBpOffset += expr->type.size;


    std::shared_ptr<Structure> address;

    if(type == Type("num", 8))
        address = std::make_shared<NumLValueStructure>("rbp - " + std::to_string(fn.curBpOffset));

    else if (type.isPtr)
        address = std::make_shared<PtrLValueStructure>("rbp - " + std::to_string(fn.curBpOffset), type);

    else if (type == Type("char", 1)){
        address = std::make_shared<CharLValueStructure>("rbp - " + std::to_string(fn.curBpOffset));

    } else if (type == Type("bool", 1)){
        address = std::make_shared<BoolLValueStructure>("rbp - " + std::to_string(fn.curBpOffset));
    } else{
        address = std::make_shared<UserStructure>(ValueCategory::lvalue, Type(type));
    }

    try {
        expr->operatorCopy(address, code);
    }catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }

    expr->cleanUp(code);

    code.emplaceVarSymbol(id, address);
    return nullptr;
}

ACC::AssignNode::AssignNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
