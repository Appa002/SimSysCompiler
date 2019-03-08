//
// Created by a_mod on 10.02.2019.
//

#ifndef SIMSYSCOMPILER_INTERMEDIATECODE_H
#define SIMSYSCOMPILER_INTERMEDIATECODE_H

#include <IntermediateCodeGenerator/Code.h>
#include <AbstractSyntaxTree/AbstractSyntaxTree.h>
#include <IntermediateCodeGenerator/Expr.h>

namespace ACC {
    class IntermediateCode {
    private:
        Code code;

    public:
        explicit IntermediateCode(const AbstractSyntaxTree& tree);
        void print();
        void optimize();
        const Code& getCode() const;

    };

}

#endif //SIMSYSCOMPILER_INTERMEDIATECODE_H
