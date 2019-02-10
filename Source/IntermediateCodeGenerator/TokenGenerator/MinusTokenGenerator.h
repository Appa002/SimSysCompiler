//
// Created by a_mod on 09.01.2019.
//
#pragma once


#include <IntermediateCodeGenerator/Expr.h>
#include <IntermediateCodeGenerator/Code.h>


namespace ACC{
    struct MinusTokenGenerator : public Expr{
        temporary generate(ACC::Code &code) override;
        MinusTokenGenerator(ASTNode* node);
    };
}

