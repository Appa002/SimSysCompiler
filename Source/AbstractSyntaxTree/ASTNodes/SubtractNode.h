//
// Created by a_mod on 09.01.2019.
//
#pragma once


#include <AbstractSyntaxTree/ASTNode.h>
#include <Assembly/Code.h>


namespace ACC{
    struct SubtractNode : public ASTNode{
        std::shared_ptr<Structure> generate(ACC::Code &code) override;
        SubtractNode(AstOperator op, std::vector<ASTNode *> children);
};
}

