#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <AbstractSyntaxTree/ASTNode.h>
#include <Assembly/Code.h>


namespace ACC{
    struct CallTokenGenerator : public ASTNode{
        Structure* generate(ACC::Code &code) override;

    };
}

