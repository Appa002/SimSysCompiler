#include "IdTokenGenerator.h"

ACC::IdTokenGenerator::IdTokenGenerator(ASTNode *node) : Expr(node) {

}

ACC::Structure ACC::IdTokenGenerator::generate(ACC::Code &code) {
     return code.getVarSymbol(node->data.asT<std::string>());
}
