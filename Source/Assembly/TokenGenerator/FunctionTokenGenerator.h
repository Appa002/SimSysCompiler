#include <utility>

//
// Created by a_mod on 09.01.2019.
//
#pragma once

#include <AbstractSyntaxTree/ASTNode.h>
#include <Assembly/Code.h>


namespace ACC{
    struct FunctionTokenGenerator : public ASTNode{
        Structure* generate(ACC::Code &code) override;

        std::string copyIntoStackFrame(size_t offset, size_t loc, size_t size, ACC::Code &code);
    };
}

