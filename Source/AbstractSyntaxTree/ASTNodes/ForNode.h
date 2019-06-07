#include <utility>

//
// Created by a_mod on 06.01.2019.
//
#pragma once


#include <AbstractSyntaxTree/ASTNode.h>
#include <Assembly/Code.h>


namespace ACC{
    struct ForNode : public ASTNode{
        std::shared_ptr<Structure> generate(ACC::Code &code) override;
        ForNode(AstOperator op, std::vector<ASTNode *> children);

        void handleAddition(ACC::Fn& fn, Code& code, Structure index);
    };
}
