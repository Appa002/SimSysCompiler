#include <IntermediateCodeGenerator/Operator.h>

#include "Operator.h"

using namespace ACC;

std::string printAsTemporary(ACC::temporary temp) {
    return "t" + std::to_string(temp);
}

std::string opToString(ACC::Operator op) {
    switch (op.id) {
        case OperatorId::ADD:
            return std::string("add, ") + printAsTemporary(op.result) + ", " + printAsTemporary(op.lhs) + ", " +
                   printAsTemporary(op.rhs);
        case OperatorId::SUBTRACT:
            return std::string("subtract, ") + printAsTemporary(op.result) + ", " + printAsTemporary(op.lhs) + ", " +
                   printAsTemporary(op.rhs);

        case OperatorId::COPY:
            return std::string("copy, ") + printAsTemporary(op.result) + ", " + printAsTemporary(op.lhs);

        case OperatorId::PRINT:
            return std::string("print, ") + printAsTemporary(op.lhs);

        case OperatorId::ICOPY:
            return std::string("icopy, ") + printAsTemporary(op.result) + ", " + std::to_string(op.lhs);
    }
}

void ACC::Operator::printDependency(std::string indent, bool isLast) const {
    std::string representation = opToString(*this);
    auto colour = Log::Colour::Magenta;

    LOG() << indent;
    if (isLast) {
        LOG() << "\\-";
        indent += "     ";
    } else {
        LOG() << "|-";
        indent += "|    ";
    }
    // std::cout
    LOG() << colour << "[" << representation << "]" << std::endl;

    if (opLhs != nullptr)
        opLhs->printDependency(indent, false);
    if (opRhs != nullptr)
        opRhs->printDependency(indent, true);
}


