#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once


#include <AbstractSyntaxTree/ASTNode.h>
#include <Assembly/Code.h>


namespace ACC{
    struct LiteralNode : public ASTNode{
        Structure *generate(ACC::Code &code) override;
        LiteralNode(AstOperator op, std::vector<ASTNode *> children);

        void handleStringLiteral(ACC::Structure &structure, ACC::Code &code, ACC::Fn &fn);
        void handleNumberLiteral(ACC::Structure &structure, ACC::Code &code, ACC::Fn &fn);

    };
}


