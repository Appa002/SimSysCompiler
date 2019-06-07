#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <Assembly/Code.h>
#include <AbstractSyntaxTree/ASTNode.h>


namespace ACC{
    struct ReturnTokenGenerator : public ASTNode{
        Structure* generate(ACC::Code &code) override;

    };
}

