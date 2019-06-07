#include <utility>

//
// Created by a_mod on 06.01.2019.
//
#pragma once


#include <AbstractSyntaxTree/ASTNode.h>
#include <Assembly/Code.h>


namespace ACC{
    struct ForTokenGenerator : public ASTNode{
        Structure* generate(ACC::Code &code) override;

        void handleAddition(ACC::Fn& fn, Code& code, Structure index);
    };
}
