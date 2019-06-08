#include <utility>

#include "NotNode.h"

std::shared_ptr<ACC::Structure> ACC::NotNode::generate(ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    auto expr = children[0]->generate(code);
    expr->operatorNot(code);

    /*auto &fn = code.getFnSymbol();
    auto expr = node->children[0]->asExpr()->generate(code);

    Register reg;
    if (expr.registerUsed.empty())
        reg = code.getFreeRegister();
    else
        reg = expr.registerUsed[0];

    std::string regAsStr = registerToString(expr.typeId.getSize(), reg);
    fn.writeLine("xor " + regAsStr + ", 1");

    Structure out(StructureType::elementary);
    out.registerUsed = {reg};
    out.typeId = expr.typeId;
    out.isStored = false;

    out.copyToRegister = [=](std::string dest, Code& c){
        if(dest != regAsStr)
            return "movzx " + dest + ", " + regAsStr;
        return std::string();
    };

    out.copyToStack = [=](Code& c){
        return "mov [rsp], " + regAsStr;
    };

    out.copyToBpOffset = [=](int32_t offset, Code& c){
        std::string sign = offset < 0 ? ("-") : ("+");
        offset = abs(offset);
        return "mov [rbp " + sign+std::to_string(offset)+"], " + regAsStr;
    };

    return out;*/
    return nullptr;
}

ACC::NotNode::NotNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
