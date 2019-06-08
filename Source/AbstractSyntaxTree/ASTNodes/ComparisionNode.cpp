#include <utility>

#include <utility>

#include <General/builtinTypes.h>
#include "ComparisionNode.h"


std::shared_ptr<ACC::Structure> ACC::ComparisionNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);
    auto& fn = code.getFnSymbol();

    switch (cmpType){
        case ComparisionType::EQ:
            return lhs->operatorEqual(rhs, code);
        case ComparisionType::LT:
            return lhs->operatorLess(rhs, code);
        case ComparisionType::GT:
            return lhs->operatorGreater(rhs, code);
        case ComparisionType::NEQ:
            return lhs->operatorNotEqual(rhs, code);
        case ComparisionType::LET:
            return lhs->operatorLessEqual(rhs, code);
        case ComparisionType::GET:
            return lhs->operatorGreaterEqual(rhs, code);
    }
    return nullptr;
}

ACC::ComparisionNode::ComparisionNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children,
        ACC::ComparisionType type) : ASTNode(op, std::move(children)), cmpType(type) {
}

