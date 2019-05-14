#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <Assembly/Expr.h>
#include <Assembly/Code.h>


namespace ACC{
    struct FunctionTokenGenerator : public Expr{
        Structure generate(ACC::Code &code) override;
        explicit FunctionTokenGenerator(ASTNode* node);

        std::string copyIntoStackFrame(size_t offset, size_t loc, size_t size, ACC::Code &code);
    };
}

