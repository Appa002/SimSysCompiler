#include <utility>

//
// Created by a_mod on 06.01.2019.
//
#pragma once


#include <Assembly/Expr.h>
#include <Assembly/Code.h>


namespace ACC{
    struct ForTokenGenerator : public Expr{
        Structure generate(ACC::Code &code) override;
        explicit ForTokenGenerator(ASTNode* node);

        void handleAddition(ACC::Fn& fn, Code& code, Structure index);
    };
}
