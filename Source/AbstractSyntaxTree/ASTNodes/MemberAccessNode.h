#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <AbstractSyntaxTree/ASTNode.h>
#include <Assembly/Code.h>


namespace ACC{
    struct MemberAccessNode : public ASTNode{
        std::shared_ptr<Structure> generate(ACC::Code &code) override;
        MemberAccessNode(AstOperator op,  std::string member);
        MemberAccessNode(AstOperator op, std::vector<ASTNode*> children, std::string member);

        [[nodiscard]] std::string createRepresentation() const override;


    public:
        std::string member;

    };
}

