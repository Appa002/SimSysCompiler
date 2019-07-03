//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <Assembly/Code.h>
#include <AbstractSyntaxTree/ASTNode.h>


namespace ACC{
    struct ModuloNode : public ASTNode{
        std::shared_ptr<Structure> generate(ACC::Code &code) override;
        ModuloNode(AstOperator op, std::vector<ASTNode *> children);

    };
}


