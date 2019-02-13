#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once


#include <IntermediateCodeGenerator/Expr.h>


namespace ACC{
    struct LiteralTokenGenerator : public Expr{
        Dependency generate(ACC::Code &code) override;
        explicit LiteralTokenGenerator(ASTNode* node);

    };
}

