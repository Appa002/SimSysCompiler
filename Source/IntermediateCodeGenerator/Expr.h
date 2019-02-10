//
// Created by a_mod on 10.02.2019.
//

#ifndef SIMSYSCOMPILER_EXPR_H
#define SIMSYSCOMPILER_EXPR_H

#include <IntermediateCodeGenerator/RepresentationTypes.h>
#include <memory>
#include "Code.h"
#include <AbstractSyntaxTree/ASTNode.h>

namespace ACC {
    class Expr {
    public:
        explicit Expr(ASTNode* n) : node(n) {};

        virtual temporary generate(ACC::Code &code) = 0;

        ASTNode* node;
    };
}

#endif //SIMSYSCOMPILER_EXPR_H
