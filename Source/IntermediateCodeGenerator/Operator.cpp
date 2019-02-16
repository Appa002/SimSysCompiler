#include <IntermediateCodeGenerator/Operator.h>

#include "Operator.h"

using namespace ACC;

std::string printAsTemporary(ACC::temporary temp) {
    return "t" + std::to_string(temp);
}

std::string ACC::Operator::asString() const {
    switch (id) {
        case OperatorId::ADD:
            return std::string("add, ") + printAsTemporary(result) + ", " + printAsTemporary(lhs) + ", " +
                   printAsTemporary(rhs);
        case OperatorId::SUBTRACT:
            return std::string("subtract, ") + printAsTemporary(result) + ", " + printAsTemporary(lhs) + ", " +
                   printAsTemporary(rhs);

        case OperatorId::COPY:
            return std::string("copy, ") + printAsTemporary(result) + ", " + printAsTemporary(lhs);

        case OperatorId::PRINT:
            return std::string("print, ") + printAsTemporary(lhs);

        case OperatorId::ICOPY:
            return std::string("icopy, ") + printAsTemporary(result) + ", " + std::to_string(lhs);

        case OperatorId::IADD:
            return std::string("iadd, ") + printAsTemporary(result) + ", " + std::to_string(lhs) + ", " +
                   std::to_string(rhs);

        case OperatorId::ISUBTRACT:
            return std::string("isubtract, ") + printAsTemporary(result) + ", " + std::to_string(lhs) + ", " +
                   std::to_string(rhs);

        case OperatorId::IPRINT:
            return std::string("iprint, ") + std::to_string(lhs);
    }
    return std::string("unknown, ") + printAsTemporary(result) + ", " + std::to_string(lhs) + ", " +
           std::to_string(rhs);
}

void ACC::Operator::printDependency(std::string indent, bool isLast) const {
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
    LOG() << colour << "[" << asString() << "]" << std::endl;

    if (opLhs != nullptr)
        opLhs->printDependency(indent, false);
    if (opRhs != nullptr)
        opRhs->printDependency(indent, true);
}



