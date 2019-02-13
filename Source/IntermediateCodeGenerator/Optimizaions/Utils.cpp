#include "Utils.h"

/*
std::string ACC::printAsTemporary(ACC::temporary temp) {
    return "t" + std::to_string(temp);
}

std::string ACC::opToString(ACC::Operator op) {
    switch (op.id) {
        case OperatorId::PLUS:
            return std::string("add, ") + printAsTemporary(op.result) + ", " + printAsTemporary(op.lhs) + ", " +
                   printAsTemporary(op.rhs);
        case OperatorId::MINUS:
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

void ACC::DependencyElement::print(std::string indent, bool isLast) const {
    std::string representation = opToString(*op);
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

    if (lhs != nullptr)
        lhs->print(indent, false);
    if (rhs != nullptr)
        rhs->print(indent, true);
}

ACC::DependencyElement::~DependencyElement() {
    delete lhs;
    delete rhs;
}

ACC::DependencyElement::DependencyElement(ACC::Operator *op, size_t idx)
        : op(op), idx(idx) {}


ACC::DependencyElement *
ACC::createDependencyGraph(ACC::Tuple<ACC::Operator *, size_t> start, ACC::Code &input) {

    auto root = new DependencyElement(start.a, start.b);

    size_t idx = start.b - 1;

    for (auto itr = input.getData().rbegin() + (input.getData().size() - start.b);
         itr != input.getData().rend(); (idx--, itr++)) {
        if (itr->result == start.a->lhs) {
            if (root->op->lhs != 0)
                root->lhs = createDependencyGraph({&input.at(idx), idx}, input);
        }
    }

    idx = start.b - 1;

    for (auto itr = input.getData().rbegin() + (input.getData().size() - start.b);
         itr != input.getData().rend(); (idx--, itr++)) {
        if (itr->result == start.a->rhs) {
            if (root->op->rhs != 0)
                root->rhs = createDependencyGraph({&input.at(idx), idx}, input);
        }
    }

    return root;
}

*/