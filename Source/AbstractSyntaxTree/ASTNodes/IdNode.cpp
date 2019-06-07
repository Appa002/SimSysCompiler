#include <utility>

#include "IdNode.h"

ACC::Structure* ACC::IdNode::generate(ACC::Code &code) {
     //return code.getVarSymbol(node->data.asT<std::string>());
     return nullptr;
}

ACC::IdNode::IdNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
