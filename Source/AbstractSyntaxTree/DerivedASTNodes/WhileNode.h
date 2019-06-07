#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <Assembly/Code.h>
#include <AbstractSyntaxTree/ASTNode.h>

namespace ACC{
    struct WhileNode : public ASTNode{
        WhileNode(AstOperator op, std::vector<ASTNode *> children);

        Structure* generate(ACC::Code &code) override;
    };
}

