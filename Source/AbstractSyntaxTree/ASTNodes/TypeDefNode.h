//
// Created by a_mod on 20.08.2019.
//
#pragma once

#include <AbstractSyntaxTree/ASTNode.h>
#include <Types/UnverifiedType.h>

namespace ACC {
    class TypeDefNode : public ASTNode {
    public:
        TypeDefNode(AstOperator op, Type t);
        TypeDefNode(AstOperator op, UnverifiedType t);


        std::shared_ptr<Structure> generate(ACC::Code &code) override;

        std::string createRepresentation() const override;

        Type getType();

    private:
        UnverifiedType unverifiedType;

        Type type = Type("", 0);
    };
}