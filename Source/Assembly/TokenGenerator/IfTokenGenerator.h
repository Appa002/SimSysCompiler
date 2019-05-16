#include <utility>

//
// Created by a_mod on 06.01.2019.
//
#pragma once


#include <Assembly/Expr.h>
#include <Assembly/Code.h>


namespace ACC{
    struct IfTokenGenerator : public Expr{
        Structure generate(ACC::Code &code) override;
        explicit IfTokenGenerator(ASTNode* node);

    };
}
