//
// Created by a_mod on 20.08.2019.
//
#pragma once

#include <AbstractSyntaxTree/ASTNode.h>
#include <Types/UnverifiedType.h>

namespace ACC {
    class TypeDeclNode : public ASTNode {
    public:
        TypeDeclNode(AstOperator op, std::string sym);


        std::shared_ptr<Structure> generate(ACC::Code &code) override;

        [[nodiscard]] std::string createRepresentation() const override;

    private:
        std::string sym;

    };
}