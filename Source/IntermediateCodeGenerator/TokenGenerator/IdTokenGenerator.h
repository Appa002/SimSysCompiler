#include <utility>

//
// Created by a_mod on 06.01.2019.
//
#pragma once


#include <IntermediateCodeGenerator/Expr.h>
#include <IntermediateCodeGenerator/Code.h>


namespace ACC{
    struct IdTokenGenerator : public Expr{
        temporary generate(ACC::Code &code) override;
        IdTokenGenerator(ASTNode* node);

    };
}