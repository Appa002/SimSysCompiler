#include <utility>

//
// Created by a_mod on 06.01.2019.
//
#pragma once


#include <Assembly/Code.h>
#include <AbstractSyntaxTree/ASTNode.h>


namespace ACC{
    struct IfConstructNode : public ASTNode{
        Structure* generate(ACC::Code &code) override;
        IfConstructNode(AstOperator op, std::vector<ASTNode *> children);


        void handleElif(ACC::Fn &fn, ACC::Code &code, size_t idx, std::string &next,
                                std::string const &final);

        void handleElse(ACC::Fn &fn, ACC::Code &code, size_t idx, std::string &next);


    };
}
