//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_OPERANDHANDLER_H
#define SIMSYSCOMPILER_OPERANDHANDLER_H

#include <Operand.h>
#include "TokenizedInput.h"
#include "DepthParsedInput.h"

namespace ACC {
    class OperandHandler {
    private:
        std::vector<Operand*> data;
        int referenceCount = 0;
    public:
        explicit OperandHandler(DepthParsedInput input);
        OperandHandler( const OperandHandler& other );
        ~OperandHandler();


        Operand* & at(unsigned idx);
        void prettyPrint();

        std::vector<Operand*>::iterator begin();
        std::vector<Operand*>::iterator end();
    };
}

#endif //SIMSYSCOMPILER_OPERANDHANDLER_H
