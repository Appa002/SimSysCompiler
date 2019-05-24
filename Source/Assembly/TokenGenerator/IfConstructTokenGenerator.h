#include <utility>

//
// Created by a_mod on 06.01.2019.
//
#pragma once


#include <Assembly/Expr.h>
#include <Assembly/Code.h>


namespace ACC{
    struct IfConstructTokenGenerator : public Expr{
        Structure generate(ACC::Code &code) override;
        explicit IfConstructTokenGenerator(ASTNode* node);

        void handleElif(ACC::Fn &fn, ACC::Code &code, size_t idx, std::string &next,
                                std::string const &final);

        void handleElse(ACC::Fn &fn, ACC::Code &code, size_t idx, std::string &next);


    };
}
