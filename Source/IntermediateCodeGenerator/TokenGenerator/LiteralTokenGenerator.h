#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once


#include <IntermediateCodeGenerator/Expr.h>


namespace ACC{
    struct LiteralTokenGenerator : public Expr{
        temporary generate(ACC::Code &code) override;
        LiteralTokenGenerator(ASTNode* node);

    };
}

