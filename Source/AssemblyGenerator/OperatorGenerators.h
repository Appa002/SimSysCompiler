//
// Created by a_mod on 02.03.2019.
//

#ifndef SIMSYSCOMPILER_OPERATORGENERATORS_H
#define SIMSYSCOMPILER_OPERATORGENERATORS_H

#include <IntermediateCodeGenerator/Operator.h>
#include <string>
#include "Location.h"
#include "Assembly.h"

namespace ACC::OpGenerators{
    void iPrint (Operator* op, Assembly& assembly);
    void exit (Operator* op, Assembly& assembly);
    void iAdd(Operator *op, Assembly &assembly);
    void function(Operator* op, Assembly& assembly);
    void lattr(Operator* op, Assembly& assembly);
    void print(Operator* op, Assembly& assembly);

}

#endif //SIMSYSCOMPILER_OPERATORGENERATORS_H
