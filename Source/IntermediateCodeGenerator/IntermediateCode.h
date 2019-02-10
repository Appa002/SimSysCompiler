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
        std::string operator2String(Operator op);
        std::string printAsTemporary(ACC::temporary temp);
        std::string printAsRRegister(ACC::temporary temp);

    public:
        IntermediateCode(const AbstractSyntaxTree& tree);
        void print();

    };

}

#endif //SIMSYSCOMPILER_INTERMEDIATECODE_H
