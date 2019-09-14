//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <Assembly/Code.h>
#include <AbstractSyntaxTree/ASTNode.h>


namespace ACC{
    struct InitializerListNode : public ASTNode{
        std::shared_ptr<Structure> generate(ACC::Code &code) override;
        InitializerListNode(AstOperator op, std::vector<ASTNode *> children);

        std::vector<std::shared_ptr<Structure>> unpack(ACC::Code & code);

        [[nodiscard]] std::string createRepresentation() const override;


    };
}


