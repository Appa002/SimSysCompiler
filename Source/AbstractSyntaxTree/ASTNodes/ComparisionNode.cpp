#include <utility>

#include <utility>

#include <General/builtinTypes.h>
#include <Error/ASTError.h>
#include "ComparisionNode.h"


std::shared_ptr<ACC::Structure> ACC::ComparisionNode::generate(ACC::Code &code) {
    auto lhs = children[0]->generate(code);
    auto rhs = children[1]->generate(code);
    auto &fn = code.getFnSymbol();

    std::shared_ptr<Structure> out;

    switch (cmpType) {
        case ComparisionType::EQ:
            try {
                out = lhs->operatorEqual(rhs, code);
            } catch (errors::ASTError &err) {
                err.lineNum = this->lineNum;
                err.lineContent = this->lineContent;
                throw;
            }
            break;
        case ComparisionType::LT:
            try {
                out = lhs->operatorLess(rhs, code);
            } catch (errors::ASTError &err) {
                err.lineNum = this->lineNum;
                err.lineContent = this->lineContent;
                throw;
            }
            break;
        case ComparisionType::GT:
            try {
                out = lhs->operatorGreater(rhs, code);
            } catch (errors::ASTError &err) {
                err.lineNum = this->lineNum;
                err.lineContent = this->lineContent;
                throw;
            }
            break;
        case ComparisionType::NEQ:
            try {
                out = lhs->operatorNotEqual(rhs, code);
            } catch (errors::ASTError &err) {
                err.lineNum = this->lineNum;
                err.lineContent = this->lineContent;
                throw;
            }
            break;
        case ComparisionType::LET:
            try {
                out = lhs->operatorLessEqual(rhs, code);
            } catch (errors::ASTError &err) {
                err.lineNum = this->lineNum;
                err.lineContent = this->lineContent;
                throw;
            }
            break;
        case ComparisionType::GET:
            try {
                out = lhs->operatorGreaterEqual(rhs, code);
            } catch (errors::ASTError &err) {
                err.lineNum = this->lineNum;
                err.lineContent = this->lineContent;
                throw;
            }
            break;
    }
    lhs->cleanUp(code);
    rhs->cleanUp(code);
    return out;
}

ACC::ComparisionNode::ComparisionNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children,
                                      ACC::ComparisionType type) : ASTNode(op, std::move(children)), cmpType(type) {
}

