#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <AbstractSyntaxTree/ASTNode.h>
#include <Assembly/Code.h>


namespace ACC{
    struct SyscallNode : public ASTNode{
        SyscallNode(AstOperator op, std::vector<ASTNode *> children);

        Structure* generate(ACC::Code &code) override;
    };
}

