//
// Created by a_mod on 10.02.2019.
//

#include <Logger/Logger.h>
#include "IntermediateCode.h"

ACC::IntermediateCode::IntermediateCode(const AbstractSyntaxTree& tree) {
    code = Code();
    tree.getRoot()->asExpr()->generate(code);
}

void ACC::IntermediateCode::print() {
    LOG.createHeading("Generated Intermediate Representation");
    for(const auto& op : code){
        LOG() << operator2String(op) << std::endl;
    }
}

std::string ACC::IntermediateCode::operator2String(Operator op) {
    switch (op.id) {
        case OperatorId::PLUS:
            return std::string("plus, ") + printAsTemporary(op.result) + ", " + printAsTemporary(op.lhs) + ", " +
                   printAsTemporary(op.rhs);
        case OperatorId::MINUS:
            return std::string("minus, ") + printAsTemporary(op.result) + ", " + printAsTemporary(op.lhs) + ", " +
                   printAsTemporary(op.rhs);

        case OperatorId::COPY:
            return std::string("copy, ") + printAsTemporary(op.result) + ", " + printAsTemporary(op.lhs);

        case OperatorId::INTERRUPT:
            return std::string("interrupt, ") + std::to_string(op.lhs);

        case OperatorId::REAL_REGISTER:
            return std::string("rreg, ") + printAsRRegister(op.lhs) + ", " + printAsTemporary(op.rhs);

        case OperatorId::ICOPY:
            return std::string("icopy, ") + printAsTemporary(op.result) + ", " + std::to_string(op.lhs);
    }
}


std::string ACC::IntermediateCode::printAsTemporary(ACC::temporary temp){
    return "t" + std::to_string(temp);
}

std::string ACC::IntermediateCode::printAsRRegister(ACC::temporary temp){
    switch (temp){
        case 0:
            return "eax";
        case 1:
            return "ebx";
        case 2:
            return "ecx";
        case 3:
            return "edx";
        default:
            return std::to_string(temp);
    }
}