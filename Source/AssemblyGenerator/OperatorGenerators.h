//
// Created by a_mod on 02.03.2019.
//

#ifndef SIMSYSCOMPILER_OPERATORGENERATORS_H
#define SIMSYSCOMPILER_OPERATORGENERATORS_H

#include <IntermediateCodeGenerator/Operator.h>
#include <string>
#include "Snippet.h"
#include "Assembly.h"

namespace ACC::OpGenerators{
    void addOp (Operator* op);
    void iAddOp (Operator* op, Assembly& assembly);
    void subtractOp (Operator* op);
    void iSubtractOp (Operator* op);
    void copy (Operator* op);
    void iCopy (Operator* op);
    void print (Operator* op);
    void iPrint (Operator* op, Assembly& assembly);
    void exit (Operator* op, Assembly& assembly);


}

#endif //SIMSYSCOMPILER_OPERATORGENERATORS_H
