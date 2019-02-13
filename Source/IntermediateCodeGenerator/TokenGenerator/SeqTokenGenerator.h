//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <IntermediateCodeGenerator/Expr.h>
#include <IntermediateCodeGenerator/Code.h>

namespace ACC{
    struct SeqTokenGenerator : public Expr{
        explicit SeqTokenGenerator(ASTNode* node);
        Dependency generate(ACC::Code &code) override;
    };
}
