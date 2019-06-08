#include <utility>

#include <utility>

#include "IdNode.h"

std::shared_ptr<ACC::Structure> ACC::IdNode::generate(ACC::Code &code) {
     return code.getVarSymbol(data.asT<std::string>());
}

ACC::IdNode::IdNode(ACC::AstOperator op, std::string str) : ASTNode(op, std::move(str)) {

}
