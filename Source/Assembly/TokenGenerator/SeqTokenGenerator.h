//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Assembly/Expr.h>
#include <Assembly/Code.h>

namespace ACC{
    struct SeqTokenGenerator : public Expr{
        explicit SeqTokenGenerator(ASTNode* node);
        Structure generate(ACC::Code &code) override;
    };
}
