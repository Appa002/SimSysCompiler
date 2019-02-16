//
// Created by a_mod on 16.02.2019.
//

#include "Optimizations.h"

using namespace ACC;

size_t find(ACC::Operator *op, ACC::Code &input, bool &found) {
    found = true;
    size_t idx = 0;
    for (ACC::Operator *elem : input) {
        if (elem == op)
            return idx;
        idx++;
    }
    found = false;
    return 0;
}


bool isDependentOnConstants(ACC::Operator *op) {
    if(op->opRhs != nullptr)
        return
            (op->opLhs->id == OperatorId::ICOPY || op->opLhs->id == OperatorId::IADD ||
             op->opLhs->id == OperatorId::ISUBTRACT)
            &&
            (op->opRhs->id == OperatorId::ICOPY || op->opRhs->id == OperatorId::IADD ||
             op->opRhs->id == OperatorId::ISUBTRACT || op->rhs == 0);
    else
        return  (op->opLhs->id == OperatorId::ICOPY || op->opLhs->id == OperatorId::IADD ||
                 op->opLhs->id == OperatorId::ISUBTRACT);
}

temporary evalConstant(ACC::Operator *op) {
    if (op->id == OperatorId::ICOPY)
        return op->lhs;

    if (op->id == OperatorId::IADD)
        return op->lhs + op->rhs;

    if (op->id == OperatorId::ISUBTRACT)
        return op->lhs - op->rhs;

    return 0;
}

void handleAdd(ACC::Code &input, Operator *op) {
    op->id = OperatorId::IADD;

    op->lhs = evalConstant(op->opLhs);
    op->rhs = evalConstant(op->opRhs);

    bool found;
    size_t lhsIdx = find(op->opLhs, input, found);
    if (found) input.remove(lhsIdx);
    size_t rhsIdx = find(op->opRhs, input, found);
    if (found) input.remove(rhsIdx);

    op->opLhs = nullptr;
    op->opRhs = nullptr;

}

void handleSubtract(ACC::Code &input, Operator *op) {
    op->id = OperatorId::ISUBTRACT;

    op->lhs = evalConstant(op->opLhs);
    op->rhs = evalConstant(op->opRhs);

    bool found;
    size_t lhsIdx = find(op->opLhs, input, found);
    if (found) input.remove(lhsIdx);
    size_t rhsIdx = find(op->opRhs, input, found);
    if (found) input.remove(rhsIdx);

    op->opLhs = nullptr;
    op->opRhs = nullptr;

}


void handlePrint(ACC::Code &input, Operator *op) {
    op->id = OperatorId::IPRINT;

    op->lhs = evalConstant(op->opLhs);

    bool found;
    size_t lhsIdx = find(op->opLhs, input, found);
    if (found) input.remove(lhsIdx);

    op->opLhs = nullptr;
    op->opRhs = nullptr;

}

void ACC::constantElision(ACC::Code &input) {
    bool hasChanged = false;
    do {
        hasChanged = false;
        for (ACC::Operator *op : input) {
            if (op->id == OperatorId::ADD) {
                if (isDependentOnConstants(op)) {
                    LOG() << "Running Elision for ADD Operator ..." << std::endl;
                    LOG() << "lhs: t" << op->lhs << std::endl;
                    LOG() << "rhs: t" << op->rhs << std::endl;

                    hasChanged = true;
                    handleAdd(input, op);

                    LOG() << "constant evaluated lhs: " << op->lhs << std::endl;
                    LOG() << "constant evaluated rhs: " << op->rhs << std::endl;

                    LOG() << "" << std::endl << std::endl;
                }
            } else if (op->id == OperatorId::SUBTRACT) {
                if (isDependentOnConstants(op)) {
                    LOG() << "Running Elision for SUBTRACT Operator ..." << std::endl;
                    LOG() << "lhs: t" << op->lhs << std::endl;
                    LOG() << "rhs: t" << op->rhs << std::endl;

                    hasChanged = true;
                    handleSubtract(input, op);

                    LOG() << "constant evaluated lhs: " << op->lhs << std::endl;
                    LOG() << "constant evaluated rhs: " << op->rhs << std::endl;

                    LOG() << "" << std::endl << std::endl;

                }
            } else if(op->id == OperatorId::PRINT){
                if(isDependentOnConstants(op)){
                    LOG() << "Running Elision for PRINT Operator ..." << std::endl;
                    LOG() << "lhs: t" << op->lhs << std::endl;

                    hasChanged = true;
                    handlePrint(input, op);

                    LOG() << "constant evaluated lhs: " << op->lhs << std::endl;

                    LOG() << "" << std::endl << std::endl;

                }
            }

        }
    } while (hasChanged);
}