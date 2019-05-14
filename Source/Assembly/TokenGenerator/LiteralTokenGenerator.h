#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once


#include <Assembly/Expr.h>


namespace ACC{
    struct LiteralTokenGenerator : public Expr{
        Structure generate(ACC::Code &code) override;
        explicit LiteralTokenGenerator(ASTNode* node);

        void handleStringLiteral(ACC::Structure &structure, ACC::Code &code, ACC::Fn &fn);
        void handleNumberLiteral(ACC::Structure &structure, ACC::Code &code, ACC::Fn &fn);

    };
}


