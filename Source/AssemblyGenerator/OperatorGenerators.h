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
    void print (Operator* op, Assembly& assembly);
    void exit (Operator* op, Assembly& assembly);
    void iAdd(Operator *op, Assembly &assembly);
    void iSubtract(Operator *op, Assembly &assembly);
    void imultiply(Operator *op, Assembly &assembly);
    void idivide(Operator *op, Assembly &assembly);
    void function(Operator* op, Assembly& assembly);
    void isattr(Operator *op, Assembly &assembly);
    void lattr(Operator *op, Assembly &assembly);
    void ireturn(Operator* op, Assembly &assembly);
    void ret (Operator* op, Assembly& assembly);
    void icall(Operator* op, Assembly &assembly);
    void add(Operator* op, Assembly &assembly);
    void subtract(Operator* op, Assembly &assembly);
    void multiply(Operator *op, Assembly &assembly);
    void divide(Operator *op, Assembly &assembly);
    void icopy(Operator* op, Assembly &assembly);

}

#endif //SIMSYSCOMPILER_OPERATORGENERATORS_H
