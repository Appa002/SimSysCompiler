#include <utility>

#include <utility>

#include <General/builtinTypes.h>
#include "ComparisionNode.h"


std::shared_ptr<ACC::Structure> ACC::ComparisionNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);
    auto& fn = code.getFnSymbol();

    std::shared_ptr<Structure> out;

    switch (cmpType){
        case ComparisionType::EQ:
             out = lhs->operatorEqual(rhs, code);
            break;
        case ComparisionType::LT:
             out = lhs->operatorLess(rhs, code);
            break;
        case ComparisionType::GT:
             out = lhs->operatorGreater(rhs, code);
            break;
        case ComparisionType::NEQ:
             out = lhs->operatorNotEqual(rhs, code);
            break;
        case ComparisionType::LET:
             out = lhs->operatorLessEqual(rhs, code);
            break;
        case ComparisionType::GET:
             out = lhs->operatorGreaterEqual(rhs, code);
            break;
    }
    lhs->cleanUp(code);
    rhs->cleanUp(code);
    return out;
}

ACC::ComparisionNode::ComparisionNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children,
        ACC::ComparisionType type) : ASTNode(op, std::move(children)), cmpType(type) {
}

