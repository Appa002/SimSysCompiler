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
    Snippet addOp (Operator* op);
    Snippet iAddOp (Operator* op);
    Snippet subtractOp (Operator* op);
    Snippet iSubtractOp (Operator* op);
    Snippet copy (Operator* op);
    Snippet iCopy (Operator* op);
    Snippet print (Operator* op);
    Snippet iPrint (Operator* op, Assembly& assembly);
    Snippet exit (Operator* op, Assembly& assembly);


}

#endif //SIMSYSCOMPILER_OPERATORGENERATORS_H
